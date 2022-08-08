#include "session.hpp"

#include <libtorrent/session.hpp>
#include <libtorrent/read_resume_data.hpp>

#include "addtorrentparams.hpp"
#include "alert.hpp"
#include "sessionparams.hpp"

namespace lt = libtorrent;

Napi::Object Session::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "Session", {
        InstanceMethod<&Session::AddDhtNode>("add_dht_node"),
        InstanceMethod<&Session::AddTorrent>("add_torrent"),
        InstanceMethod<&Session::IsDhtRunning>("is_dht_running"),
        InstanceMethod<&Session::IsListening>("is_listening"),
        InstanceMethod<&Session::IsPaused>("is_paused"),
        InstanceMethod<&Session::IsValid>("is_valid"),
        InstanceMethod<&Session::ListenPort>("listen_port"),
        InstanceMethod<&Session::Pause>("pause"),
        InstanceMethod<&Session::PostDhtStats>("post_dht_stats"),
        InstanceMethod<&Session::PostSessionStats>("post_session_stats"),
        InstanceMethod<&Session::PostTorrentUpdates>("post_torrent_updates"),
        InstanceMethod<&Session::Resume>("resume"),
        InstanceMethod<&Session::SessionState>("session_state"),
        InstanceMethod<&Session::SslListenPort>("ssl_listen_port"),
    });

    auto* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    exports.Set("Session", func);

    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

Session::Session(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Session>(info)
{
    m_opts = Napi::ObjectReference::New(info[0].As<Napi::Object>());
    m_tsfn = Napi::ThreadSafeFunction::New(
        info.Env(),
        Napi::Function::New(
            info.Env(),
            [&](const Napi::CallbackInfo& info)
            {
                return AlertNotify(info);
            },
            "alert_notify"),
        "Session",
        0,
        1,
        [](Napi::Env env) {});

    lt::settings_pack settings;
    settings.set_int(lt::settings_pack::alert_mask, lt::alert::all_categories);

    m_session = std::make_unique<lt::session>(settings);
    m_session->set_alert_notify(
        [&]()
        {
            m_tsfn.BlockingCall(
                [&](Napi::Env env, Napi::Function cb)
                {
                    if (this->Value().Type() == napi_undefined)
                    {
                        printf("Session is undefined - did GC collect?\n");
                        return;
                    }

                    cb.Call(this->Value(), {});
                });
        });
}

Session::~Session()
{
    m_session->set_alert_notify([]{});
    m_tsfn.Release();
}

Napi::Value Session::AddDhtNode(const Napi::CallbackInfo &info)
{
    m_session->add_dht_node({ info[0].ToString(), info[0].ToNumber() });
    return info.Env().Undefined();
}

Napi::Value Session::AddTorrent(const Napi::CallbackInfo &info)
{
    m_session->async_add_torrent(
        AddTorrentParams::Unwrap(
            info.Env(),
            info[0].ToObject()));

    return info.Env().Undefined();
}

Napi::Value Session::IsDhtRunning(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_session->is_dht_running());
}

Napi::Value Session::IsListening(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_session->is_listening());
}

Napi::Value Session::IsPaused(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_session->is_paused());
}

Napi::Value Session::IsValid(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_session->is_valid());
}

Napi::Value Session::ListenPort(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), m_session->listen_port());
}

Napi::Value Session::LoadTorrent(const Napi::CallbackInfo& info)
{
    auto buf = info[0].As<Napi::Uint8Array>();
    auto* data = reinterpret_cast<const char*>(buf.Data());

    lt::error_code ec;
    lt::add_torrent_params p = lt::read_resume_data(
        lt::span(data, static_cast<long>(buf.ByteLength())),
        ec);

    if (ec)
    {
        Napi::TypeError::New(info.Env(), ec.message());
        return info.Env().Undefined();
    }

    m_session->async_add_torrent(p);

    return info.Env().Undefined();
}

Napi::Value Session::Pause(const Napi::CallbackInfo& info)
{
    m_session->pause();
    return info.Env().Undefined();
}

Napi::Value Session::PostDhtStats(const Napi::CallbackInfo &info)
{
    m_session->post_dht_stats();
    return info.Env().Undefined();
}

Napi::Value Session::PostSessionStats(const Napi::CallbackInfo &info)
{
    m_session->post_session_stats();
    return info.Env().Undefined();
}

Napi::Value Session::PostTorrentUpdates(const Napi::CallbackInfo& info)
{
    m_session->post_torrent_updates();
    return info.Env().Undefined();
}

Napi::Value Session::Resume(const Napi::CallbackInfo& info)
{
    m_session->resume();
    return info.Env().Undefined();
}

Napi::Value Session::SessionState(const Napi::CallbackInfo& info)
{
    // TODO: flags
    return SessionParams::New(info.Env(), m_session->session_state());
}

Napi::Value Session::SslListenPort(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_session->ssl_listen_port());
}

Napi::Value Session::AlertNotify(const Napi::CallbackInfo& info)
{
    std::vector<lt::alert*> alerts;
    m_session->pop_alerts(&alerts);

    for (const auto alert : alerts)
    {
        auto self = info.This().As<Napi::Object>();
        auto emit = self.Get("emit").As<Napi::Function>();

        emit.Call(
            info.This(),
            {
                Napi::String::New(info.Env(), alert->what()),
                AlertWrap::Wrap(info.Env(), alert)
            });
    }

    return info.Env().Undefined();
}
