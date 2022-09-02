#include "torrentstatus.hpp"

#include <libtorrent/torrent_status.hpp>

#include "errorcode.hpp"
#include "infohash.hpp"
#include "torrenthandle.hpp"

namespace lt = libtorrent;

Napi::FunctionReference* TorrentStatus::m_ctor = nullptr;

Napi::Object TorrentStatus::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "TorrentStatus", {
        InstanceAccessor<&TorrentStatus::GetBlockSize>("block_size"),
        InstanceAccessor<&TorrentStatus::GetCurrentTracker>("current_tracker"),
        InstanceAccessor<&TorrentStatus::GetDownloadPayloadRate>("download_payload_rate"),
        InstanceAccessor<&TorrentStatus::GetDownloadRate>("download_rate"),
        InstanceAccessor<&TorrentStatus::GetErrorCode>("errc"),
        InstanceAccessor<&TorrentStatus::GetFlags>("flags"),
        InstanceAccessor<&TorrentStatus::GetHandle>("handle"),
        InstanceAccessor<&TorrentStatus::GetHasIncoming>("has_incoming"),
        InstanceAccessor<&TorrentStatus::GetHasMetadata>("has_metadata"),
        InstanceAccessor<&TorrentStatus::GetInfoHashes>("info_hashes"),
        InstanceAccessor<&TorrentStatus::GetIsSeeding>("is_seeding"),
        InstanceAccessor<&TorrentStatus::GetMovingStorage>("moving_storage"),
        InstanceAccessor<&TorrentStatus::GetName>("name"),
        InstanceAccessor<&TorrentStatus::GetNeedSaveResume>("need_save_resume"),
        InstanceAccessor<&TorrentStatus::GetNextAnnounce>("next_announce"),
        InstanceAccessor<&TorrentStatus::GetNumPeers>("num_peers"),
        InstanceAccessor<&TorrentStatus::GetNumSeeds>("num_seeds"),
        InstanceAccessor<&TorrentStatus::GetProgress>("progress"),
        InstanceAccessor<&TorrentStatus::GetQueuePosition>("queue_position"),
        InstanceAccessor<&TorrentStatus::GetSavePath>("save_path"),
        InstanceAccessor<&TorrentStatus::GetState>("state"),
        InstanceAccessor<&TorrentStatus::GetTotal>("total"),
        InstanceAccessor<&TorrentStatus::GetTotalDone>("total_done"),
        InstanceAccessor<&TorrentStatus::GetTotalDownload>("total_download"),
        InstanceAccessor<&TorrentStatus::GetTotalFailedBytes>("total_failed_bytes"),
        InstanceAccessor<&TorrentStatus::GetTotalPayloadDownload>("total_payload_download"),
        InstanceAccessor<&TorrentStatus::GetTotalPayloadUpload>("total_payload_upload"),
        InstanceAccessor<&TorrentStatus::GetTotalRedundantBytes>("total_redundant_bytes"),
        InstanceAccessor<&TorrentStatus::GetTotalUpload>("total_upload"),
        InstanceAccessor<&TorrentStatus::GetTotalWanted>("total_wanted"),
        InstanceAccessor<&TorrentStatus::GetTotalWantedDone>("total_wanted_done"),
        InstanceAccessor<&TorrentStatus::GetUploadPayloadRate>("upload_payload_rate"),
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

Napi::Value TorrentStatus::GetErrorCode(const Napi::CallbackInfo &info)
{
    return m_status->errc
        ? ErrorCode::Wrap(info.Env(), m_status->errc)
        : info.Env().Null();
}

Napi::Value TorrentStatus::GetFlags(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<std::uint64_t>(m_status->flags));
}

Napi::Value TorrentStatus::GetHandle(const Napi::CallbackInfo &info)
{
    return TorrentHandle::New(info.Env(), m_status->handle);
}

Napi::Value TorrentStatus::GetHasIncoming(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_status->has_incoming);
}

Napi::Value TorrentStatus::GetHasMetadata(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_status->has_metadata);
}

Napi::Value TorrentStatus::GetInfoHashes(const Napi::CallbackInfo &info)
{
    return InfoHash::New(info.Env(), m_status->info_hashes);
}

Napi::Value TorrentStatus::GetIsSeeding(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_status->is_seeding);
}

Napi::Value TorrentStatus::GetMovingStorage(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_status->moving_storage);
}

Napi::Value TorrentStatus::GetName(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_status->name);
}

Napi::Value TorrentStatus::GetNeedSaveResume(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_status->need_save_resume);
}

Napi::Value TorrentStatus::GetNextAnnounce(const Napi::CallbackInfo &info)
{
    napi_value result;
    napi_create_int64(info.Env(), lt::total_seconds(m_status->next_announce), &result);
    return {info.Env(), result};
}

Napi::Value TorrentStatus::GetNumPeers(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_status->num_peers);
}

Napi::Value TorrentStatus::GetNumSeeds(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_status->num_seeds);
}

Napi::Value TorrentStatus::GetProgress(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_status->progress);
}

Napi::Value TorrentStatus::GetQueuePosition(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<int>(m_status->queue_position));
}

Napi::Value TorrentStatus::GetSavePath(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_status->save_path);
}

Napi::Value TorrentStatus::GetState(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_status->state);
}

Napi::Value TorrentStatus::GetTotal(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalDone(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_done, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalDownload(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_download, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalFailedBytes(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_failed_bytes, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalPayloadDownload(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_payload_download, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalPayloadUpload(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_payload_upload, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalRedundantBytes(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_redundant_bytes, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalUpload(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_upload, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalWanted(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_wanted, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetTotalWantedDone(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->total_wanted_done, &v);
    return {info.Env(), v};
}

Napi::Value TorrentStatus::GetUploadPayloadRate(const Napi::CallbackInfo &info)
{
    napi_value v;
    napi_create_int64(info.Env(), m_status->upload_payload_rate, &v);
    return {info.Env(), v};
}
