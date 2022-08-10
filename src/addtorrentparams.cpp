#include "addtorrentparams.hpp"

#include <libtorrent/add_torrent_params.hpp>

#include "infohash.hpp"
#include "torrentinfo.hpp"

namespace lt = libtorrent;

Napi::FunctionReference* AddTorrentParams::m_ctor = nullptr;

Napi::Object AddTorrentParams::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "AddTorrentParams", {
        InstanceAccessor("active_time", &AddTorrentParams::GetActiveTime, &AddTorrentParams::SetActiveTime),
        InstanceAccessor("added_time", &AddTorrentParams::GetAddedTime, &AddTorrentParams::SetAddedTime),
        InstanceAccessor("completed_time", &AddTorrentParams::GetCompletedTime, &AddTorrentParams::SetCompletedTime),
        InstanceAccessor("download_limit", &AddTorrentParams::GetDownloadLimit, &AddTorrentParams::SetDownloadLimit),
        InstanceAccessor("finished_time", &AddTorrentParams::GetFinishedTime, &AddTorrentParams::SetFinishedTime),
        InstanceAccessor("info_hashes", &AddTorrentParams::GetInfoHashes, &AddTorrentParams::SetInfoHashes),
        InstanceAccessor("last_seen_complete", &AddTorrentParams::GetLastSeenComplete, &AddTorrentParams::SetLastSeenComplete),
        InstanceAccessor("max_connections", &AddTorrentParams::GetMaxConnections, &AddTorrentParams::SetMaxConnections),
        InstanceAccessor("max_uploads", &AddTorrentParams::GetMaxUploads, &AddTorrentParams::SetMaxUploads),
        InstanceAccessor("name", &AddTorrentParams::GetName, &AddTorrentParams::SetName),
        InstanceAccessor("num_complete", &AddTorrentParams::GetNumComplete, &AddTorrentParams::SetNumComplete),
        InstanceAccessor("num_downloaded", &AddTorrentParams::GetNumDownloaded, &AddTorrentParams::SetNumDownloaded),
        InstanceAccessor("num_incomplete", &AddTorrentParams::GetNumIncomplete, &AddTorrentParams::SetNumIncomplete),
        InstanceAccessor("save_path", &AddTorrentParams::GetSavePath, &AddTorrentParams::SetSavePath),
        InstanceAccessor("seeding_time", &AddTorrentParams::GetSeedingTime, &AddTorrentParams::SetSeedingTime),
        InstanceAccessor("ti", &AddTorrentParams::GetTorrentInfo, &AddTorrentParams::SetTorrentInfo),
        InstanceAccessor("total_downloaded", &AddTorrentParams::GetTotalDownloaded, &AddTorrentParams::SetTotalDownloaded),
        InstanceAccessor("total_uploaded", &AddTorrentParams::GetTotalUploaded, &AddTorrentParams::SetTotalUploaded),
        InstanceAccessor("upload_limit", &AddTorrentParams::GetUploadLimit, &AddTorrentParams::SetUploadLimit),
    });

    m_ctor = new Napi::FunctionReference();
    *m_ctor = Napi::Persistent(func);

    exports.Set("AddTorrentParams", func);

    env.SetInstanceData<Napi::FunctionReference>(m_ctor);

    return exports;
}

Napi::Value AddTorrentParams::New(Napi::Env env, const libtorrent::add_torrent_params &params)
{
    if (m_ctor == nullptr)
    {
        Napi::TypeError::New(env, "AddTorrentParams::m_ctor not initialized").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    return m_ctor->New({
        Napi::External<lt::add_torrent_params>::New(env, new lt::add_torrent_params(params))
    });
}

AddTorrentParams::AddTorrentParams(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<AddTorrentParams>(info)
{
    if (info.Length() > 0 && info[0].IsExternal())
    {
        m_params = std::unique_ptr<lt::add_torrent_params>(
            info[0].As<Napi::External<lt::add_torrent_params>>().Data());
    }
    else
    {
        m_params = std::make_unique<lt::add_torrent_params>();
    }
}

AddTorrentParams::~AddTorrentParams() = default;

Napi::Value AddTorrentParams::GetActiveTime(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->active_time);
}

Napi::Value AddTorrentParams::GetAddedTime(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<double>(m_params->added_time));
}

Napi::Value AddTorrentParams::GetCompletedTime(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<double>(m_params->completed_time));
}

Napi::Value AddTorrentParams::GetDownloadLimit(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->download_limit);
}

Napi::Value AddTorrentParams::GetFinishedTime(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->finished_time);
}

Napi::Value AddTorrentParams::GetInfoHashes(const Napi::CallbackInfo &info)
{
    return InfoHash::New(info.Env(), m_params->info_hashes);
}

Napi::Value AddTorrentParams::GetLastSeenComplete(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<double>(m_params->last_seen_complete));
}

Napi::Value AddTorrentParams::GetMaxConnections(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->max_connections);
}

Napi::Value AddTorrentParams::GetMaxUploads(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->max_uploads);
}

Napi::Value AddTorrentParams::GetName(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_params->name);
}

Napi::Value AddTorrentParams::GetNumComplete(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->num_complete);
}

Napi::Value AddTorrentParams::GetNumDownloaded(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->num_downloaded);
}

Napi::Value AddTorrentParams::GetNumIncomplete(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->num_incomplete);
}

Napi::Value AddTorrentParams::GetSavePath(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_params->save_path);
}

Napi::Value AddTorrentParams::GetSeedingTime(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<int>(m_params->seeding_time));
}

Napi::Value AddTorrentParams::GetTorrentInfo(const Napi::CallbackInfo &info)
{
    if (!m_params->ti)
    {
        return info.Env().Null();
    }

    throw Napi::Error::New(info.Env(), "Not implemented");
}

Napi::Value AddTorrentParams::GetTotalDownloaded(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<double>(m_params->total_downloaded));
}

Napi::Value AddTorrentParams::GetTotalUploaded(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<double>(m_params->total_uploaded));
}

Napi::Value AddTorrentParams::GetUploadLimit(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_params->upload_limit);
}

void AddTorrentParams::SetActiveTime(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->active_time = value.ToNumber();
}

void AddTorrentParams::SetAddedTime(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->added_time = value.ToNumber().Int64Value();
}

void AddTorrentParams::SetCompletedTime(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->completed_time = value.ToNumber().Int64Value();
}

void AddTorrentParams::SetDownloadLimit(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->download_limit = value.ToNumber();
}

void AddTorrentParams::SetFinishedTime(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->finished_time = value.ToNumber();
}

void AddTorrentParams::SetInfoHashes(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    auto hash = InfoHash::Unwrap(value.ToObject());
    m_params->info_hashes = static_cast<lt::info_hash_t>(*hash);
}

void AddTorrentParams::SetLastSeenComplete(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->last_seen_complete = value.ToNumber().Int64Value();
}

void AddTorrentParams::SetMaxConnections(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->max_connections = value.ToNumber();
}

void AddTorrentParams::SetMaxUploads(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->max_uploads = value.ToNumber();
}

void AddTorrentParams::SetName(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->name = value.ToString();
}

void AddTorrentParams::SetNumComplete(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->num_complete = value.ToNumber();
}

void AddTorrentParams::SetNumDownloaded(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->num_downloaded = value.ToNumber();
}

void AddTorrentParams::SetNumIncomplete(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->num_incomplete = value.ToNumber();
}

void AddTorrentParams::SetSavePath(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->save_path = value.ToString();
}

void AddTorrentParams::SetSeedingTime(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->seeding_time = value.ToNumber();
}

void AddTorrentParams::SetTorrentInfo(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    auto ti = TorrentInfo::Unwrap(value.ToObject());
    m_params->ti = static_cast<std::shared_ptr<lt::torrent_info>>(*ti);
}

void AddTorrentParams::SetTotalDownloaded(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->total_downloaded = value.ToNumber();
}

void AddTorrentParams::SetTotalUploaded(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->total_uploaded = value.ToNumber();
}

void AddTorrentParams::SetUploadLimit(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->upload_limit = value.ToNumber();
}
