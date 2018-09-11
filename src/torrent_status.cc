#include "torrent_status.h"

#include <sstream>

#include <libtorrent/torrent_handle.hpp>

#include "torrent_info.h"
#include "torrent_handle.h"

using porla::TorrentStatus;

Napi::FunctionReference TorrentStatus::constructor;

Napi::Object TorrentStatus::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "TorrentStatus",
    {
        InstanceAccessor("added_time", &TorrentStatus::Get_AddedTime, nullptr),
        InstanceAccessor("all_time_download", &TorrentStatus::Get_AllTimeDownload, nullptr),
        InstanceAccessor("all_time_upload", &TorrentStatus::Get_AllTimeUpload, nullptr),
        InstanceAccessor("announcing_to_dht", &TorrentStatus::Get_AnnouncingToDht, nullptr),
        InstanceAccessor("announcing_to_lsd", &TorrentStatus::Get_AnnouncingToLsd, nullptr),
        InstanceAccessor("announcing_to_trackers", &TorrentStatus::Get_AnnouncingToTrackers, nullptr),
        InstanceAccessor("block_size", &TorrentStatus::Get_BlockSize, nullptr),
        InstanceAccessor("completed_time", &TorrentStatus::Get_CompletedTime, nullptr),
        InstanceAccessor("connect_candidates", &TorrentStatus::Get_ConnectCandidates, nullptr),
        InstanceAccessor("connections_limit", &TorrentStatus::Get_ConnectionsLimit, nullptr),
        InstanceAccessor("current_tracker", &TorrentStatus::Get_CurrentTracker, nullptr),
        InstanceAccessor("distributed_copies", &TorrentStatus::Get_DistributedCopies, nullptr),
        InstanceAccessor("down_bandwidth_queue", &TorrentStatus::Get_DownBandwidthQueue, nullptr),
        InstanceAccessor("download_payload_rate", &TorrentStatus::Get_DownloadPayloadRate, nullptr),
        InstanceAccessor("download_rate", &TorrentStatus::Get_DownloadRate, nullptr),
        InstanceAccessor("errc", &TorrentStatus::Get_Errc, nullptr),
        InstanceAccessor("error_file", &TorrentStatus::Get_ErrorFile, nullptr),
        InstanceAccessor("finished_duration", &TorrentStatus::Get_FinishedDuration, nullptr),
        InstanceAccessor("flags", &TorrentStatus::Get_Flags, nullptr),
        InstanceAccessor("handle", &TorrentStatus::Get_Handle, nullptr),
        InstanceAccessor("has_incoming", &TorrentStatus::Get_HasIncoming, nullptr),
        InstanceAccessor("has_metadata", &TorrentStatus::Get_HasMetadata, nullptr),
        InstanceAccessor("info_hash", &TorrentStatus::Get_InfoHash, nullptr),
        InstanceAccessor("is_finished", &TorrentStatus::Get_IsFinished, nullptr),
        InstanceAccessor("is_seeding", &TorrentStatus::Get_IsSeeding, nullptr),
        InstanceAccessor("last_download", &TorrentStatus::Get_LastDownload, nullptr),
        InstanceAccessor("last_seen_complete", &TorrentStatus::Get_LastSeenComplete, nullptr),
        InstanceAccessor("last_upload", &TorrentStatus::Get_LastUpload, nullptr),
        InstanceAccessor("list_peers", &TorrentStatus::Get_ListPeers, nullptr),
        InstanceAccessor("list_seeds", &TorrentStatus::Get_ListSeeds, nullptr),
        InstanceAccessor("moving_storage", &TorrentStatus::Get_MovingStorage, nullptr),
        InstanceAccessor("name", &TorrentStatus::Get_Name, nullptr),
        InstanceAccessor("need_save_resume", &TorrentStatus::Get_NeedSaveResume, nullptr),
        InstanceAccessor("next_announce", &TorrentStatus::Get_NextAnnounce, nullptr),
        InstanceAccessor("num_complete", &TorrentStatus::Get_NumComplete, nullptr),
        InstanceAccessor("num_connections", &TorrentStatus::Get_NumConnections, nullptr),
        InstanceAccessor("num_incomplete", &TorrentStatus::Get_NumIncomplete, nullptr),
        InstanceAccessor("num_peers", &TorrentStatus::Get_NumPeers, nullptr),
        InstanceAccessor("num_pieces", &TorrentStatus::Get_NumPieces, nullptr),
        InstanceAccessor("num_seeds", &TorrentStatus::Get_NumSeeds, nullptr),
        InstanceAccessor("num_uploads", &TorrentStatus::Get_NumUploads, nullptr),
        // TODO piecesInstanceAccessor("num_uploads", &TorrentStatus::Get_NumUploads, nullptr),
        InstanceAccessor("progress", &TorrentStatus::Get_Progress, nullptr),
        InstanceAccessor("queue_position", &TorrentStatus::Get_QueuePosition, nullptr),
        InstanceAccessor("save_path", &TorrentStatus::Get_SavePath, nullptr),
        InstanceAccessor("seed_rank", &TorrentStatus::Get_SeedRank, nullptr),
        InstanceAccessor("seeding_duration", &TorrentStatus::Get_SeedingDuration, nullptr),
        InstanceAccessor("state", &TorrentStatus::Get_State, nullptr),
        InstanceAccessor("storage_mode", &TorrentStatus::Get_StorageMode, nullptr),
        InstanceAccessor("torrent_file", &TorrentStatus::Get_TorrentFile, nullptr),
        InstanceAccessor("total", &TorrentStatus::Get_Total, nullptr),
        InstanceAccessor("total_done", &TorrentStatus::Get_TotalDone, nullptr),
        InstanceAccessor("total_download", &TorrentStatus::Get_TotalDownload, nullptr),
        InstanceAccessor("total_failed_bytes", &TorrentStatus::Get_TotalFailedBytes, nullptr),
        InstanceAccessor("total_payload_download", &TorrentStatus::Get_TotalPayloadDownload, nullptr),
        InstanceAccessor("total_payload_upload", &TorrentStatus::Get_TotalPayloadUpload, nullptr),
        InstanceAccessor("total_redundant_bytes", &TorrentStatus::Get_TotalRedundantBytes, nullptr),
        InstanceAccessor("total_upload", &TorrentStatus::Get_TotalUpload, nullptr),
        InstanceAccessor("total_wanted", &TorrentStatus::Get_TotalWanted, nullptr),
        InstanceAccessor("total_wanted_done", &TorrentStatus::Get_TotalWantedDone, nullptr),
        InstanceAccessor("up_bandwidth_queue", &TorrentStatus::Get_UpBandwidthQueue, nullptr),
        InstanceAccessor("upload_payload_rate", &TorrentStatus::Get_UploadPayloadRate, nullptr),
        InstanceAccessor("upload_rate", &TorrentStatus::Get_UploadRate, nullptr),
        InstanceAccessor("uploads_limit", &TorrentStatus::Get_UploadsLimit, nullptr),
        // TODO verified pieces
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return exports;
}

Napi::Object TorrentStatus::NewInstance(Napi::Value arg)
{
    return constructor.New({ arg });
}

TorrentStatus::TorrentStatus(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<TorrentStatus>(info)
{
    auto val = info[0].As<Napi::External<lt::torrent_status>>();
    ts_ = std::make_unique<libtorrent::torrent_status>(*val.Data());
}

Napi::Value TorrentStatus::Get_AddedTime(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->added_time);
}

Napi::Value TorrentStatus::Get_AllTimeDownload(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->all_time_download);
}

Napi::Value TorrentStatus::Get_AllTimeUpload(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->all_time_upload);
}

Napi::Value TorrentStatus::Get_AnnouncingToDht(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->announcing_to_dht);
}

Napi::Value TorrentStatus::Get_AnnouncingToLsd(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->announcing_to_lsd);
}

Napi::Value TorrentStatus::Get_AnnouncingToTrackers(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->announcing_to_trackers);
}

Napi::Value TorrentStatus::Get_BlockSize(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->block_size);
}

Napi::Value TorrentStatus::Get_CompletedTime(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->completed_time);
}

Napi::Value TorrentStatus::Get_ConnectCandidates(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->connect_candidates);
}

Napi::Value TorrentStatus::Get_ConnectionsLimit(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->connections_limit);
}

Napi::Value TorrentStatus::Get_CurrentTracker(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), ts_->current_tracker);
}

Napi::Value TorrentStatus::Get_DistributedCopies(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->distributed_copies);
}

Napi::Value TorrentStatus::Get_DownBandwidthQueue(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->down_bandwidth_queue);
}

Napi::Value TorrentStatus::Get_DownloadPayloadRate(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->download_payload_rate);
}

Napi::Value TorrentStatus::Get_DownloadRate(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->download_rate);
}

Napi::Value TorrentStatus::Get_Errc(const Napi::CallbackInfo& info)
{
    if (ts_->errc)
    {
        auto err = Napi::Object::New(info.Env());
        err.Set("message", Napi::String::New(info.Env(), ts_->errc.message()));
        err.Set("value", Napi::Number::New(info.Env(), ts_->errc.value()));
        return err;
    }

    return info.Env().Null();
}

Napi::Value TorrentStatus::Get_ErrorFile(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), static_cast<int32_t>(ts_->error_file));
}

Napi::Value TorrentStatus::Get_FinishedDuration(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->finished_duration.count());
}

Napi::Value TorrentStatus::Get_Flags(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), static_cast<uint64_t>(ts_->flags));
}

Napi::Value TorrentStatus::Get_Handle(const Napi::CallbackInfo& info)
{
    auto arg = Napi::External<lt::torrent_handle>::New(info.Env(), &ts_->handle);
    return TorrentHandle::NewInstance(arg);
}

Napi::Value TorrentStatus::Get_HasIncoming(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->has_incoming);
}

Napi::Value TorrentStatus::Get_HasMetadata(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->has_metadata);
}

Napi::Value TorrentStatus::Get_InfoHash(const Napi::CallbackInfo& info)
{
    std::stringstream ss;
    ss << ts_->info_hash;
    return Napi::String::New(info.Env(), ss.str());
}

Napi::Value TorrentStatus::Get_IsFinished(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->is_finished);
}

Napi::Value TorrentStatus::Get_IsSeeding(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->is_seeding);
}

Napi::Value TorrentStatus::Get_LastDownload(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), lt::time_point_cast<lt::seconds>(ts_->last_download).time_since_epoch().count());
}

Napi::Value TorrentStatus::Get_LastSeenComplete(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->last_seen_complete);
}

Napi::Value TorrentStatus::Get_LastUpload(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), lt::time_point_cast<lt::seconds>(ts_->last_upload).time_since_epoch().count());
}

Napi::Value TorrentStatus::Get_ListPeers(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->list_peers);
}

Napi::Value TorrentStatus::Get_ListSeeds(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->list_seeds);
}

Napi::Value TorrentStatus::Get_MovingStorage(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->moving_storage);
}

Napi::Value TorrentStatus::Get_Name(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), ts_->name);
}

Napi::Value TorrentStatus::Get_NeedSaveResume(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ts_->need_save_resume);
}

Napi::Value TorrentStatus::Get_NextAnnounce(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), lt::total_seconds(ts_->next_announce));
}

Napi::Value TorrentStatus::Get_NumComplete(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->num_complete);
}

Napi::Value TorrentStatus::Get_NumConnections(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->num_connections);
}

Napi::Value TorrentStatus::Get_NumIncomplete(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->num_incomplete);
}

Napi::Value TorrentStatus::Get_NumPeers(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->num_peers);
}

Napi::Value TorrentStatus::Get_NumPieces(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->num_pieces);
}

Napi::Value TorrentStatus::Get_NumSeeds(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->num_seeds);
}

Napi::Value TorrentStatus::Get_NumUploads(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->num_uploads);
}

Napi::Value TorrentStatus::Get_Progress(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->progress);
}

Napi::Value TorrentStatus::Get_QueuePosition(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), static_cast<int32_t>(ts_->queue_position));
}

Napi::Value TorrentStatus::Get_SavePath(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), ts_->save_path);
}

Napi::Value TorrentStatus::Get_SeedRank(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->seed_rank);
}

Napi::Value TorrentStatus::Get_SeedingDuration(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->seeding_duration.count());
}

Napi::Value TorrentStatus::Get_State(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->state);
}

Napi::Value TorrentStatus::Get_StorageMode(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->storage_mode);
}

Napi::Value TorrentStatus::Get_TorrentFile(const Napi::CallbackInfo& info)
{
    if (auto ti = ts_->torrent_file.lock())
    {
        auto arg = Napi::External<std::shared_ptr<const lt::torrent_info>>::New(info.Env(), &ti);
        return TorrentInfo::NewInstance(arg);
    }

    return info.Env().Null();
}

Napi::Value TorrentStatus::Get_Total(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total);
}

Napi::Value TorrentStatus::Get_TotalDone(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_done);
}

Napi::Value TorrentStatus::Get_TotalDownload(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_download);
}

Napi::Value TorrentStatus::Get_TotalFailedBytes(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_failed_bytes);
}

Napi::Value TorrentStatus::Get_TotalPayloadDownload(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_payload_download);
}

Napi::Value TorrentStatus::Get_TotalPayloadUpload(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_payload_upload);
}

Napi::Value TorrentStatus::Get_TotalRedundantBytes(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_redundant_bytes);
}

Napi::Value TorrentStatus::Get_TotalUpload(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_upload);
}

Napi::Value TorrentStatus::Get_TotalWanted(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_wanted);
}

Napi::Value TorrentStatus::Get_TotalWantedDone(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->total_wanted_done);
}

Napi::Value TorrentStatus::Get_UpBandwidthQueue(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->up_bandwidth_queue);
}

Napi::Value TorrentStatus::Get_UploadPayloadRate(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->upload_payload_rate);
}

Napi::Value TorrentStatus::Get_UploadRate(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->upload_rate);
}

Napi::Value TorrentStatus::Get_UploadsLimit(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ts_->uploads_limit);
}
