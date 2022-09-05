#include "session.hpp"

#include <libtorrent/session.hpp>
#include <libtorrent/read_resume_data.hpp>

#include "addtorrentparams.hpp"
#include "alert.hpp"
#include "sessionparams.hpp"
#include "settingspack.hpp"
#include "torrenthandle.hpp"

namespace lt = libtorrent;

Napi::Object Session::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "Session", {
        InstanceMethod<&Session::AddDhtNode>("add_dht_node"),
        InstanceMethod<&Session::AddTorrent>("add_torrent"),
        InstanceMethod<&Session::ApplySettings>("apply_settings"),
        InstanceMethod<&Session::IsDhtRunning>("is_dht_running"),
        InstanceMethod<&Session::IsListening>("is_listening"),
        InstanceMethod<&Session::IsPaused>("is_paused"),
        InstanceMethod<&Session::IsValid>("is_valid"),
        InstanceMethod<&Session::ListenPort>("listen_port"),
        InstanceMethod<&Session::Pause>("pause"),
        InstanceMethod<&Session::PostDhtStats>("post_dht_stats"),
        InstanceMethod<&Session::PostSessionStats>("post_session_stats"),
        InstanceMethod<&Session::PostTorrentUpdates>("post_torrent_updates"),
        InstanceMethod<&Session::RemoveTorrent>("remove_torrent"),
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

void Session::AddDhtNode(const Napi::CallbackInfo &info)
{
    m_session->add_dht_node({ info[0].ToString(), info[1].ToNumber() });
}

void Session::AddTorrent(const Napi::CallbackInfo &info)
{
    auto obj = info[0].ToObject();
    auto params = AddTorrentParams::Unwrap(obj);

    m_session->async_add_torrent(
        static_cast<lt::add_torrent_params>(*params));
}

void Session::ApplySettings(const Napi::CallbackInfo &info)
{
    m_session->apply_settings(
        SettingsPack::Unwrap(info[0].ToObject()));
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

void Session::Pause(const Napi::CallbackInfo& info)
{
    m_session->pause();
}

void Session::PostDhtStats(const Napi::CallbackInfo &info)
{
    m_session->post_dht_stats();
}

void Session::PostSessionStats(const Napi::CallbackInfo &info)
{
    m_session->post_session_stats();
}

void Session::PostTorrentUpdates(const Napi::CallbackInfo& info)
{
    m_session->post_torrent_updates();
}

void Session::RemoveTorrent(const Napi::CallbackInfo &info)
{
    auto handle = TorrentHandle::Unwrap(info[0].ToObject());
    auto flags = lt::remove_flags_t{};

    if (info.Length() > 1 && info[1].IsNumber())
    {
        flags = static_cast<lt::remove_flags_t>(
            info[1].ToNumber().Int64Value());
    }

    m_session->remove_torrent(
        static_cast<lt::torrent_handle>(*handle),
        flags);
}

void Session::Resume(const Napi::CallbackInfo& info)
{
    m_session->resume();
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

void Session::AlertNotify(const Napi::CallbackInfo& info)
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
}
