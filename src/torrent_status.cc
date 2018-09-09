#include "torrent_status.h"

#include <sstream>

#include <libtorrent/torrent_handle.hpp>

#include "common.h"
#include "torrent_info.h"
#include "torrent_handle.h"

using porla::TorrentStatus;

napi_ref TorrentStatus::constructor;

TorrentStatus::TorrentStatus(napi_env env, libtorrent::torrent_status const& ts)
    : env_(env),
    wrapper_(nullptr)
{
    ts_ = std::make_unique<libtorrent::torrent_status>(ts);
}

void TorrentStatus::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<TorrentStatus*>(native_obj);
}

napi_status TorrentStatus::Init(napi_env env, napi_value exports)
{
    std::vector<napi_property_descriptor> properties
    {
        PORLA_GETTER_DESCRIPTOR("active_time", Get_ActiveTime),
        PORLA_GETTER_DESCRIPTOR("added_time", Get_AddedTime),
        PORLA_GETTER_DESCRIPTOR("all_time_download", Get_AllTimeDownload),
        PORLA_GETTER_DESCRIPTOR("all_time_upload", Get_AllTimeUpload),
        PORLA_GETTER_DESCRIPTOR("announcing_to_dht", Get_AnnouncingToDht),
        PORLA_GETTER_DESCRIPTOR("announcing_to_lsd", Get_AnnouncingToLsd),
        PORLA_GETTER_DESCRIPTOR("announcing_to_trackers", Get_AnnouncingToTrackers),
        PORLA_GETTER_DESCRIPTOR("block_size", Get_BlockSize),
        PORLA_GETTER_DESCRIPTOR("completed_time", Get_CompletedTime),
        PORLA_GETTER_DESCRIPTOR("connect_candidates", Get_ConnectCandidates),
        PORLA_GETTER_DESCRIPTOR("connections_limit", Get_ConnectionsLimit),
        PORLA_GETTER_DESCRIPTOR("current_tracker", Get_CurrentTracker),
        PORLA_GETTER_DESCRIPTOR("distributed_copies", Get_DistributedCopies),
        PORLA_GETTER_DESCRIPTOR("down_bandwidth_queue", Get_DownBandwidthQueue),
        PORLA_GETTER_DESCRIPTOR("download_payload_rate", Get_DownloadPayloadRate),
        PORLA_GETTER_DESCRIPTOR("download_rate", Get_DownloadRate),
        PORLA_GETTER_DESCRIPTOR("errc", Get_Errc),
        PORLA_GETTER_DESCRIPTOR("error_file", Get_ErrorFile),
        PORLA_GETTER_DESCRIPTOR("finished_duration", Get_FinishedDuration),
        PORLA_GETTER_DESCRIPTOR("flags", Get_Flags),
        PORLA_GETTER_DESCRIPTOR("handle", Get_Handle),
        PORLA_GETTER_DESCRIPTOR("has_incoming", Get_HasIncoming),
        PORLA_GETTER_DESCRIPTOR("has_metadata", Get_HasMetadata),
        PORLA_GETTER_DESCRIPTOR("info_hash", Get_InfoHash),
        PORLA_GETTER_DESCRIPTOR("is_finished", Get_IsFinished),
        PORLA_GETTER_DESCRIPTOR("is_seeding", Get_IsSeeding),
        PORLA_GETTER_DESCRIPTOR("last_download", Get_LastDownload),
        PORLA_GETTER_DESCRIPTOR("last_seen_complete", Get_LastSeenComplete),
        PORLA_GETTER_DESCRIPTOR("last_upload", Get_LastUpload),
        PORLA_GETTER_DESCRIPTOR("list_peers", Get_ListPeers),
        PORLA_GETTER_DESCRIPTOR("list_seeds", Get_ListSeeds),
        PORLA_GETTER_DESCRIPTOR("moving_storage", Get_MovingStorage),
        PORLA_GETTER_DESCRIPTOR("name", Get_Name),
        PORLA_GETTER_DESCRIPTOR("need_save_resume", Get_NeedSaveResume),
        PORLA_GETTER_DESCRIPTOR("next_announce", Get_NextAnnounce),
        PORLA_GETTER_DESCRIPTOR("num_complete", Get_NumComplete),
        PORLA_GETTER_DESCRIPTOR("num_connections", Get_NumConnections),
        PORLA_GETTER_DESCRIPTOR("num_incomplete", Get_NumIncomplete),
        PORLA_GETTER_DESCRIPTOR("num_peers", Get_NumPeers),
        PORLA_GETTER_DESCRIPTOR("num_pieces", Get_NumPieces),
        PORLA_GETTER_DESCRIPTOR("num_seeds", Get_NumSeeds),
        PORLA_GETTER_DESCRIPTOR("num_uploads", Get_NumUploads),
        // TODO: pieces
        PORLA_GETTER_DESCRIPTOR("progress", Get_Progress),
        PORLA_GETTER_DESCRIPTOR("queue_position", Get_QueuePosition),
        PORLA_GETTER_DESCRIPTOR("save_path", Get_SavePath),
        PORLA_GETTER_DESCRIPTOR("seed_rank", Get_SeedRank),
        PORLA_GETTER_DESCRIPTOR("seeding_duration", Get_SeedingDuration),
        PORLA_GETTER_DESCRIPTOR("state", Get_State),
        PORLA_GETTER_DESCRIPTOR("storage_mode", Get_StorageMode),
        PORLA_GETTER_DESCRIPTOR("torrent_file", Get_TorrentFile),
        PORLA_GETTER_DESCRIPTOR("total", Get_Total),
        PORLA_GETTER_DESCRIPTOR("total_done", Get_TotalDone),
        PORLA_GETTER_DESCRIPTOR("total_download", Get_TotalDownload),
        PORLA_GETTER_DESCRIPTOR("total_failed_bytes", Get_TotalFailedBytes),
        PORLA_GETTER_DESCRIPTOR("total_payload_download", Get_TotalPayloadDownload),
        PORLA_GETTER_DESCRIPTOR("total_payload_upload", Get_TotalPayloadUpload),
        PORLA_GETTER_DESCRIPTOR("total_redundant_bytes", Get_TotalRedundantBytes),
        PORLA_GETTER_DESCRIPTOR("total_upload", Get_TotalUpload),
        PORLA_GETTER_DESCRIPTOR("total_wanted", Get_TotalWanted),
        PORLA_GETTER_DESCRIPTOR("total_wanted_done", Get_TotalWantedDone),
        PORLA_GETTER_DESCRIPTOR("up_bandwidth_queue", Get_UpBandwidthQueue),
        PORLA_GETTER_DESCRIPTOR("upload_payload_rate", Get_UploadPayloadRate),
        PORLA_GETTER_DESCRIPTOR("upload_rate", Get_UploadRate),
        PORLA_GETTER_DESCRIPTOR("uploads_limit", Get_UploadsLimit),
        // TODO: verified pieces
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "TorrentStatus", NAPI_AUTO_LENGTH, New, nullptr, properties.size(), properties.data(), &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    return napi_ok;
}

napi_value TorrentStatus::New(napi_env env, napi_callback_info callback_info)
{
    napi_value target;
    napi_get_new_target(env, callback_info, &target);

    if (target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
        return nullptr;
    }

    size_t argc = 1;
    napi_value args[1];
    napi_value _this;
    NAPI_CALL(env, napi_get_cb_info(env, callback_info, &argc, args, &_this, nullptr));

    libtorrent::torrent_status* ts;
    napi_get_value_external(env, args[0], reinterpret_cast<void**>(&ts));

    TorrentStatus* obj = new TorrentStatus(env, *ts);
    NAPI_CALL(env, napi_wrap(env, _this, obj, TorrentStatus::Destructor, nullptr, &obj->wrapper_));

    return _this;
}

napi_value TorrentStatus::Get_ActiveTime(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, libtorrent::total_seconds(info.wrap->ts_->active_duration), &val);

    return val;
}

napi_value TorrentStatus::Get_AddedTime(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, info.wrap->ts_->added_time, &val);

    return val;
}

napi_value TorrentStatus::Get_AllTimeDownload(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, info.wrap->ts_->all_time_download, &val);

    return val;
}

napi_value TorrentStatus::Get_AllTimeUpload(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, info.wrap->ts_->all_time_upload, &val);

    return val;
}

napi_value TorrentStatus::Get_AnnouncingToDht(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->announcing_to_dht, &val);

    return val;
}

napi_value TorrentStatus::Get_AnnouncingToLsd(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->announcing_to_lsd, &val);

    return val;
}

napi_value TorrentStatus::Get_AnnouncingToTrackers(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->announcing_to_trackers, &val);

    return val;
}

napi_value TorrentStatus::Get_BlockSize(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->block_size, &val);

    return val;
}

napi_value TorrentStatus::Get_CompletedTime(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, info.wrap->ts_->completed_time, &val);

    return val;
}

napi_value TorrentStatus::Get_ConnectCandidates(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->connect_candidates, &val);

    return val;
}

napi_value TorrentStatus::Get_ConnectionsLimit(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->connections_limit, &val);

    return val;
}

napi_value TorrentStatus::Get_CurrentTracker(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_string_utf8(env, info.wrap->ts_->current_tracker.c_str(), NAPI_AUTO_LENGTH, &val);

    return val;
}

napi_value TorrentStatus::Get_DistributedCopies(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_double(env, info.wrap->ts_->distributed_copies, &val);

    return val;
}

napi_value TorrentStatus::Get_DownBandwidthQueue(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->down_bandwidth_queue, &val);

    return val;
}

napi_value TorrentStatus::Get_DownloadPayloadRate(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->download_payload_rate, &val);

    return val;
}

napi_value TorrentStatus::Get_DownloadRate(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->download_rate, &val);

    return val;
}

napi_value TorrentStatus::Get_Errc(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    if (info.wrap->ts_->errc)
    {
        napi_value obj;
        napi_create_object(env, &obj);

        Value v(env, obj);
        v.SetNamedProperty("message", std::string(info.wrap->ts_->errc.message().c_str()));
        v.SetNamedProperty("value", info.wrap->ts_->errc.value());

        return obj;
    }

    return nullptr;
}

napi_value TorrentStatus::Get_ErrorFile(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, static_cast<int32_t>(info.wrap->ts_->error_file), &val);

    return val;
}

napi_value TorrentStatus::Get_FinishedDuration(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, info.wrap->ts_->finished_duration.count(), &val);

    return val;
}

napi_value TorrentStatus::Get_Flags(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_double(env, static_cast<uint64_t>(info.wrap->ts_->flags), &val);

    return val;
}

napi_value TorrentStatus::Get_Handle(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    return WrapExternal<TorrentHandle, lt::torrent_handle>(env, &info.wrap->ts_->handle);
}

napi_value TorrentStatus::Get_HasIncoming(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->has_incoming, &val);

    return val;
}

napi_value TorrentStatus::Get_HasMetadata(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->has_metadata, &val);

    return val;
}

napi_value TorrentStatus::Get_InfoHash(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    std::stringstream ss;
    ss << info.wrap->ts_->info_hash;

    napi_value val;
    napi_create_string_utf8(env, ss.str().c_str(), NAPI_AUTO_LENGTH, &val);

    return val;
}

napi_value TorrentStatus::Get_IsFinished(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->is_finished, &val);

    return val;
}

napi_value TorrentStatus::Get_IsSeeding(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->is_seeding, &val);

    return val;
}

napi_value TorrentStatus::Get_LastDownload(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, libtorrent::time_point_cast<libtorrent::seconds>(info.wrap->ts_->last_download).time_since_epoch().count(), &val);

    return val;
}

napi_value TorrentStatus::Get_LastSeenComplete(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, info.wrap->ts_->last_seen_complete, &val);

    return val;
}

napi_value TorrentStatus::Get_LastUpload(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, libtorrent::time_point_cast<libtorrent::seconds>(info.wrap->ts_->last_upload).time_since_epoch().count(), &val);

    return val;
}

napi_value TorrentStatus::Get_ListPeers(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->list_peers, &val);

    return val;
}

napi_value TorrentStatus::Get_ListSeeds(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->list_seeds, &val);

    return val;
}

napi_value TorrentStatus::Get_MovingStorage(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->moving_storage, &val);

    return val;
}

napi_value TorrentStatus::Get_Name(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_string_utf8(env, info.wrap->ts_->name.c_str(), NAPI_AUTO_LENGTH, &val);

    return val;
}

napi_value TorrentStatus::Get_NeedSaveResume(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_get_boolean(env, info.wrap->ts_->need_save_resume, &val);

    return val;
}

napi_value TorrentStatus::Get_NextAnnounce(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int64(env, libtorrent::total_seconds(info.wrap->ts_->next_announce), &val);

    return val;
}

napi_value TorrentStatus::Get_NumComplete(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->num_complete, &val);

    return val;
}

napi_value TorrentStatus::Get_NumConnections(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->num_connections, &val);

    return val;
}

napi_value TorrentStatus::Get_NumIncomplete(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->num_incomplete, &val);

    return val;
}

napi_value TorrentStatus::Get_NumPeers(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->num_peers, &val);

    return val;
}

napi_value TorrentStatus::Get_NumPieces(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->num_pieces, &val);

    return val;
}

napi_value TorrentStatus::Get_NumSeeds(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->num_seeds, &val);

    return val;
}

napi_value TorrentStatus::Get_NumUploads(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_int32(env, info.wrap->ts_->num_uploads, &val);

    return val;
}

napi_value TorrentStatus::Get_Progress(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    napi_value val;
    napi_create_double(env, info.wrap->ts_->progress, &val);

    return val;
}

napi_value TorrentStatus::Get_QueuePosition(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, static_cast<int32_t>(info.wrap->ts_->queue_position), &val);

    return val;
}

napi_value TorrentStatus::Get_SavePath(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_string_utf8(env, info.wrap->ts_->save_path.c_str(), NAPI_AUTO_LENGTH, &val);

    return val;
}

napi_value TorrentStatus::Get_SeedRank(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, info.wrap->ts_->seed_rank, &val);

    return val;
}

napi_value TorrentStatus::Get_SeedingDuration(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->seeding_duration.count(), &val);

    return val;
}

napi_value TorrentStatus::Get_State(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, info.wrap->ts_->state, &val);

    return val;
}

napi_value TorrentStatus::Get_StorageMode(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, info.wrap->ts_->storage_mode, &val);

    return val;
}

napi_value TorrentStatus::Get_TorrentFile(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);
    
    if (auto ti = info.wrap->ts_->torrent_file.lock())
    {
        auto arg = Napi::External<std::shared_ptr<const lt::torrent_info>>::New(env, &ti);
        return TorrentInfo::NewInstance(arg);
    }

    napi_value null;
    napi_get_null(env, &null);

    return null;
}

napi_value TorrentStatus::Get_Total(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalDone(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_done, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalDownload(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_download, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalFailedBytes(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_failed_bytes, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalPayloadDownload(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_payload_download, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalPayloadUpload(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_payload_upload, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalRedundantBytes(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_redundant_bytes, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalUpload(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_upload, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalWanted(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_wanted, &val);

    return val;
}

napi_value TorrentStatus::Get_TotalWantedDone(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int64(env, info.wrap->ts_->total_wanted_done, &val);

    return val;
}

napi_value TorrentStatus::Get_UpBandwidthQueue(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, info.wrap->ts_->up_bandwidth_queue, &val);

    return val;
}

napi_value TorrentStatus::Get_UploadPayloadRate(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, info.wrap->ts_->upload_payload_rate, &val);

    return val;
}

napi_value TorrentStatus::Get_UploadRate(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, info.wrap->ts_->upload_rate, &val);

    return val;
}

napi_value TorrentStatus::Get_UploadsLimit(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentStatus>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, info.wrap->ts_->uploads_limit, &val);

    return val;
}
