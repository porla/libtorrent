#include "torrentstatus.hpp"

#include <libtorrent/torrent_status.hpp>

#include "infohash.hpp"

namespace lt = libtorrent;

Napi::FunctionReference* TorrentStatus::m_ctor = nullptr;

Napi::Object TorrentStatus::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "TorrentStatus", {
        InstanceAccessor<&TorrentStatus::GetBlockSize>("block_size"),
        InstanceAccessor<&TorrentStatus::GetCurrentTracker>("current_tracker"),
        InstanceAccessor<&TorrentStatus::GetDownloadPayloadRate>("download_payload_rate"),
        InstanceAccessor<&TorrentStatus::GetDownloadRate>("download_rate"),
        InstanceAccessor<&TorrentStatus::GetInfoHashes>("info_hashes"),
        InstanceAccessor<&TorrentStatus::GetName>("name"),
        InstanceAccessor<&TorrentStatus::GetProgress>("progress"),
        InstanceAccessor<&TorrentStatus::GetSavePath>("save_path"),
    });

    m_ctor = new Napi::FunctionReference();
    *m_ctor = Napi::Persistent(func);

    env.SetInstanceData<Napi::FunctionReference>(m_ctor);

    return exports;
}

Napi::Value TorrentStatus::New(Napi::Env env, const lt::torrent_status& ts)
{
    if (m_ctor == nullptr)
    {
        Napi::TypeError::New(env, "TorrentStatus::m_ctor not initialized").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    return m_ctor->New({
        Napi::External<lt::torrent_status>::New(env, new lt::torrent_status(ts))
    });
}

TorrentStatus::TorrentStatus(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<TorrentStatus>(info)
{
    m_status = std::unique_ptr<lt::torrent_status>(
        info[0].As<Napi::External<lt::torrent_status>>().Data());
}

TorrentStatus::~TorrentStatus() = default;

Napi::Value TorrentStatus::GetBlockSize(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_status->block_size);
}

Napi::Value TorrentStatus::GetCurrentTracker(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_status->current_tracker);
}

Napi::Value TorrentStatus::GetDownloadPayloadRate(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_status->download_payload_rate);
}

Napi::Value TorrentStatus::GetDownloadRate(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_status->download_rate);
}

Napi::Value TorrentStatus::GetInfoHashes(const Napi::CallbackInfo &info)
{
    return InfoHash::New(info.Env(), m_status->info_hashes);
}

Napi::Value TorrentStatus::GetName(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_status->name);
}

Napi::Value TorrentStatus::GetProgress(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_status->progress);
}

Napi::Value TorrentStatus::GetSavePath(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_status->save_path);
}
