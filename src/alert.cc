#include "alert.h"

#include "add_torrent_params.h"
#include "torrent_handle.h"
#include "torrent_status.h"

#include <libtorrent/torrent_handle.hpp>

using porla::Alert;
namespace lt = libtorrent;

Napi::Value Alert::ToJson(Napi::Env env, libtorrent::alert* alert)
{
    switch (alert->type())
    {
        case libtorrent::torrent_removed_alert::alert_type:
            return TorrentRemovedAlert(env, libtorrent::alert_cast<libtorrent::torrent_removed_alert>(alert));
        case libtorrent::read_piece_alert::alert_type:
            return ReadPieceAlert(env, lt::alert_cast<lt::read_piece_alert>(alert));
        case lt::file_completed_alert::alert_type:
            return FileCompletedAlert(env, lt::alert_cast<lt::file_completed_alert>(alert));
        case lt::file_renamed_alert::alert_type:
            return FileRenamedAlert(env, lt::alert_cast<lt::file_renamed_alert>(alert));
        case lt::file_rename_failed_alert::alert_type:
            return FileRenameFailedAlert(env, lt::alert_cast<lt::file_rename_failed_alert>(alert));
        case lt::performance_alert::alert_type:
            return PerformanceAlert(env, lt::alert_cast<lt::performance_alert>(alert));
        case lt::state_changed_alert::alert_type:
            return StateChangedAlert(env, lt::alert_cast<lt::state_changed_alert>(alert));
        case lt::tracker_error_alert::alert_type:
            return TrackerErrorAlert(env, lt::alert_cast<lt::tracker_error_alert>(alert));
        case lt::tracker_warning_alert::alert_type:
            return TrackerWarningAlert(env, lt::alert_cast<lt::tracker_warning_alert>(alert));
        case lt::scrape_reply_alert::alert_type:
            return ScrapeReplyAlert(env, lt::alert_cast<lt::scrape_reply_alert>(alert));
        case lt::scrape_failed_alert::alert_type:
            return ScrapeFailedAlert(env, lt::alert_cast<lt::scrape_failed_alert>(alert));
        case lt::tracker_reply_alert::alert_type:
            return TrackerReplyAlert(env, lt::alert_cast<lt::tracker_reply_alert>(alert));
        case lt::dht_reply_alert::alert_type:
            return DhtReplyAlert(env, lt::alert_cast<lt::dht_reply_alert>(alert));
        case lt::tracker_announce_alert::alert_type:
            return TrackerAnnounceAlert(env, lt::alert_cast<lt::tracker_announce_alert>(alert));
        case lt::hash_failed_alert::alert_type:
            return HashFailedAlert(env, lt::alert_cast<lt::hash_failed_alert>(alert));
        case lt::peer_ban_alert::alert_type:
            return PeerBanAlert(env, lt::alert_cast<lt::peer_ban_alert>(alert));
        case lt::peer_unsnubbed_alert::alert_type:
            return PeerAlert(env, lt::alert_cast<lt::peer_unsnubbed_alert>(alert));
        case lt::peer_snubbed_alert::alert_type:
            return PeerAlert(env, lt::alert_cast<lt::peer_snubbed_alert>(alert));
        case lt::peer_error_alert::alert_type:
            return PeerErrorAlert(env, lt::alert_cast<lt::peer_error_alert>(alert));
        case lt::peer_connect_alert::alert_type:
            return PeerConnectAlert(env, lt::alert_cast<lt::peer_connect_alert>(alert));
        case lt::peer_disconnected_alert::alert_type:
            return PeerDisconnectedAlert(env, lt::alert_cast<lt::peer_disconnected_alert>(alert));
        case lt::invalid_request_alert::alert_type:
            return InvalidRequestAlert(env, lt::alert_cast<lt::invalid_request_alert>(alert));
        case lt::torrent_finished_alert::alert_type:
            return TorrentAlert(env, lt::alert_cast<lt::torrent_finished_alert>(alert));
        case lt::piece_finished_alert::alert_type:
            return PieceFinishedAlert(env, lt::alert_cast<lt::piece_finished_alert>(alert));
        case lt::request_dropped_alert::alert_type:
            return RequestDroppedAlert(env, lt::alert_cast<lt::request_dropped_alert>(alert));
        case lt::block_timeout_alert::alert_type:
            return BlockTimeoutAlert(env, lt::alert_cast<lt::block_timeout_alert>(alert));
        case lt::block_finished_alert::alert_type:
            return BlockFinishedAlert(env, lt::alert_cast<lt::block_finished_alert>(alert));
        case lt::block_downloading_alert::alert_type:
            return BlockDownloadingAlert(env, lt::alert_cast<lt::block_downloading_alert>(alert));
        case lt::unwanted_block_alert::alert_type:
            return UnwantedBlockAlert(env, lt::alert_cast<lt::unwanted_block_alert>(alert));
        case lt::storage_moved_alert::alert_type:
            return StorageMovedAlert(env, lt::alert_cast<lt::storage_moved_alert>(alert));
        case lt::storage_moved_failed_alert::alert_type:
            return StorageMovedFailedAlert(env, lt::alert_cast<lt::storage_moved_failed_alert>(alert));
        case lt::torrent_deleted_alert::alert_type:
            return TorrentDeletedAlert(env, lt::alert_cast<lt::torrent_deleted_alert>(alert));
        case lt::torrent_delete_failed_alert::alert_type:
            return TorrentDeleteFailedAlert(env, lt::alert_cast<lt::torrent_delete_failed_alert>(alert));
        case lt::save_resume_data_alert::alert_type:
            return SaveResumeDataAlert(env, lt::alert_cast<lt::save_resume_data_alert>(alert));
        case lt::save_resume_data_failed_alert::alert_type:
            return SaveResumeDataFailedAlert(env, lt::alert_cast<lt::save_resume_data_failed_alert>(alert));
        case lt::torrent_paused_alert::alert_type:
            return TorrentAlert(env, lt::alert_cast<lt::torrent_paused_alert>(alert));
        case lt::torrent_resumed_alert::alert_type:
            return TorrentAlert(env, lt::alert_cast<lt::torrent_resumed_alert>(alert));
        case lt::torrent_checked_alert::alert_type:
            return TorrentAlert(env, lt::alert_cast<lt::torrent_checked_alert>(alert));
        case lt::url_seed_alert::alert_type:
            return UrlSeedAlert(env, lt::alert_cast<lt::url_seed_alert>(alert));
        case lt::file_error_alert::alert_type:
            return FileErrorAlert(env, lt::alert_cast<lt::file_error_alert>(alert));
        case lt::metadata_failed_alert::alert_type:
            return MetadataFailedAlert(env, lt::alert_cast<lt::metadata_failed_alert>(alert));
        case lt::metadata_received_alert::alert_type:
            return TorrentAlert(env, lt::alert_cast<lt::metadata_received_alert>(alert));
        case lt::add_torrent_alert::alert_type:
            return AddTorrentAlert(env, lt::alert_cast<lt::add_torrent_alert>(alert));
        case lt::state_update_alert::alert_type:
            return StateUpdateAlert(env, lt::alert_cast<lt::state_update_alert>(alert));
        case lt::session_stats_alert::alert_type:
            return SessionStatsAlert(env, lt::alert_cast<lt::session_stats_alert>(alert));
        default:
            return AlertBase(env, alert);
    }
}

Napi::Object Alert::AlertBase(Napi::Env env, libtorrent::alert* alert)
{
    auto value = Napi::Object::New(env);
    value.Set("category", Napi::Number::New(env, static_cast<uint32_t>(alert->category())));
    value.Set("message", Napi::String::New(env, alert->message()));
    value.Set("timestamp", Napi::Number::New(env, alert->timestamp().time_since_epoch().count()));
    value.Set("type", Napi::Number::New(env, alert->type()));
    value.Set("what", Napi::String::New(env, alert->what()));

    return value;
}

Napi::Object Alert::PeerAlert(Napi::Env env, libtorrent::peer_alert* alert)
{
    Napi::Object value = TorrentAlert(env, alert);

    auto obj = Napi::Object::New(env);
    obj.Set("address", Napi::String::New(env, alert->endpoint.address().to_string()));
    obj.Set("port", Napi::Number::New(env, alert->endpoint.port()));

    std::stringstream ss;
    ss << alert->pid;

    value.Set("endpoint", obj);
    value.Set("pid", Napi::String::New(env, ss.str()));

    return value;
}

Napi::Object Alert::TorrentAlert(Napi::Env env, libtorrent::torrent_alert* alert)
{
    Napi::Object value = AlertBase(env, alert);

    value.Set("torrent_name", Napi::String::New(env, alert->torrent_name()));

    auto arg = Napi::External<lt::torrent_handle>::New(env, &alert->handle);
    value.Set("handle", TorrentHandle::NewInstance(arg));

    return value;
}

Napi::Object Alert::TrackerAlert(Napi::Env env, libtorrent::tracker_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("tracker_url", Napi::String::New(env, alert->tracker_url()));
    return value;
}

Napi::Object Alert::TorrentRemovedAlert(Napi::Env env, libtorrent::torrent_removed_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    std::stringstream ss;
    ss << alert->info_hash;

    value.Set("info_hash", Napi::String::New(env, ss.str()));

    return value;
}

Napi::Object Alert::ReadPieceAlert(Napi::Env env, lt::read_piece_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));
        
        value.Set("error", err);
    }

    if (alert->buffer)
    {
        char* data = alert->buffer.get();
        auto buf = Napi::Buffer<char>::Copy(env, data, alert->size);

        value.Set("buffer", buf);
    }

    value.Set("piece", Napi::Number::New(env, static_cast<int32_t>(alert->piece)));
    value.Set("size", Napi::Number::New(env, alert->size));

    return value;
}

Napi::Object Alert::FileCompletedAlert(Napi::Env env, lt::file_completed_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("index", Napi::Number::New(env, static_cast<int32_t>(alert->index)));
    return value;
}

Napi::Object Alert::FileRenamedAlert(Napi::Env env, lt::file_renamed_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("index", Napi::Number::New(env, static_cast<int32_t>(alert->index)));
    value.Set("new_name", Napi::String::New(env, alert->new_name()));
    return value;
}

Napi::Object Alert::FileRenameFailedAlert(Napi::Env env, lt::file_rename_failed_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));
        
        value.Set("error", err);
    }

    return value;
}

Napi::Object Alert::PerformanceAlert(Napi::Env env, lt::performance_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("warning_code", Napi::Number::New(env, alert->warning_code));
    return value;
}

Napi::Object Alert::StateChangedAlert(Napi::Env env, lt::state_changed_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("prev_state", Napi::Number::New(env, alert->prev_state));
    value.Set("state", Napi::Number::New(env, alert->state));
    return value;
}

Napi::Object Alert::TrackerErrorAlert(Napi::Env env, lt::tracker_error_alert* alert)
{
    auto value = TrackerAlert(env, alert);

    value.Set("error_message", Napi::String::New(env, alert->error_message()));
    value.Set("times_in_row", Napi::Number::New(env, alert->times_in_row));

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));
        
        value.Set("error", err);
    }

    return value;
}

Napi::Object Alert::TrackerWarningAlert(Napi::Env env, lt::tracker_warning_alert* alert)
{
    auto value = TrackerAlert(env, alert);
    value.Set("warning_message", Napi::String::New(env, alert->warning_message()));
    return value;
}

Napi::Object Alert::ScrapeReplyAlert(Napi::Env env, lt::scrape_reply_alert* alert)
{
    auto value = TrackerAlert(env, alert);
    value.Set("complete", Napi::Number::New(env, alert->complete));
    value.Set("incomplete", Napi::Number::New(env, alert->incomplete));
    return value;
}

Napi::Object Alert::ScrapeFailedAlert(Napi::Env env, lt::scrape_failed_alert* alert)
{
    auto value = TrackerAlert(env, alert);
    value.Set("error_message", Napi::String::New(env, alert->error_message()));

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));
        
        value.Set("error", err);
    }

    return value;
}

Napi::Object Alert::TrackerReplyAlert(Napi::Env env, lt::tracker_reply_alert* alert)
{
    auto value = TrackerAlert(env, alert);
    value.Set("num_peers", Napi::Number::New(env, alert->num_peers));
    return value;
}

Napi::Object Alert::DhtReplyAlert(Napi::Env env, lt::dht_reply_alert* alert)
{
    auto value = TrackerAlert(env, alert);
    value.Set("num_peers", Napi::Number::New(env, alert->num_peers));
    return value;
}

Napi::Object Alert::TrackerAnnounceAlert(Napi::Env env, lt::tracker_announce_alert* alert)
{
    auto value = TrackerAlert(env, alert);
    value.Set("event", Napi::Number::New(env, alert->event));
    return value;
}

Napi::Object Alert::HashFailedAlert(Napi::Env env, lt::hash_failed_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("piece_index", Napi::Number::New(env, static_cast<int32_t>(alert->piece_index)));
    return value;
}

Napi::Object Alert::PeerBanAlert(Napi::Env env, lt::peer_ban_alert* alert)
{
    return PeerAlert(env, alert);
}

Napi::Object Alert::PeerErrorAlert(Napi::Env env, lt::peer_error_alert* alert)
{
    auto value = PeerAlert(env, alert);
    value.Set("op", Napi::Number::New(env, static_cast<uint32_t>(alert->op)));

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));
        
        value.Set("error", err);
    }

    return value;
}

Napi::Object Alert::PeerConnectAlert(Napi::Env env, lt::peer_connect_alert* alert)
{
    auto value = PeerAlert(env, alert);
    value.Set("socket_type", Napi::Number::New(env, alert->socket_type));
    return value;
}

Napi::Object Alert::PeerDisconnectedAlert(Napi::Env env, lt::peer_disconnected_alert* alert)
{
    auto value = PeerAlert(env, alert);
    value.Set("op", Napi::Number::New(env, static_cast<uint8_t>(alert->op)));
    value.Set("reason", Napi::Number::New(env, static_cast<uint32_t>(alert->reason)));
    value.Set("socket_type", Napi::Number::New(env, alert->socket_type));

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));

        value.Set("error", err);
    }

    return value;
}

Napi::Object Alert::InvalidRequestAlert(Napi::Env env, lt::invalid_request_alert* alert)
{
    auto value = PeerAlert(env, alert);
    value.Set("peer_interested", Napi::Boolean::New(env, alert->peer_interested));
    value.Set("we_have", Napi::Boolean::New(env, alert->we_have));
    value.Set("withheld", Napi::Boolean::New(env, alert->withheld));

    auto req = Napi::Object::New(env);
    req.Set("length", Napi::Number::New(env, alert->request.length));
    req.Set("piece", Napi::Number::New(env, static_cast<int32_t>(alert->request.piece)));
    req.Set("start", Napi::Number::New(env, alert->request.start));

    value.Set("request", req);

    return value;
}

Napi::Object Alert::PieceFinishedAlert(Napi::Env env, lt::piece_finished_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("piece_index", Napi::Number::New(env, static_cast<int32_t>(alert->piece_index)));
    return value;
}

Napi::Object Alert::RequestDroppedAlert(Napi::Env env, lt::request_dropped_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("block_index", Napi::Number::New(env, static_cast<int64_t>(alert->block_index)));
    value.Set("piece_index", Napi::Number::New(env, static_cast<int32_t>(alert->piece_index)));
    return value;
}

Napi::Object Alert::BlockTimeoutAlert(Napi::Env env, lt::block_timeout_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("block_index", Napi::Number::New(env, static_cast<int64_t>(alert->block_index)));
    value.Set("piece_index", Napi::Number::New(env, static_cast<int32_t>(alert->piece_index)));
    return value;
}

Napi::Object Alert::BlockFinishedAlert(Napi::Env env, lt::block_finished_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("block_index", Napi::Number::New(env, static_cast<int64_t>(alert->block_index)));
    value.Set("piece_index", Napi::Number::New(env, static_cast<int32_t>(alert->piece_index)));
    return value;
}

Napi::Object Alert::BlockDownloadingAlert(Napi::Env env, lt::block_downloading_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("block_index", Napi::Number::New(env, static_cast<int64_t>(alert->block_index)));
    value.Set("piece_index", Napi::Number::New(env, static_cast<int32_t>(alert->piece_index)));
    return value;
}

Napi::Object Alert::UnwantedBlockAlert(Napi::Env env, lt::unwanted_block_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("block_index", Napi::Number::New(env, static_cast<int64_t>(alert->block_index)));
    value.Set("piece_index", Napi::Number::New(env, static_cast<int32_t>(alert->piece_index)));
    return value;
}

Napi::Object Alert::StorageMovedAlert(Napi::Env env, lt::storage_moved_alert* alert)
{
    auto value = TorrentAlert(env, alert);
    value.Set("storage_path", Napi::String::New(env, alert->storage_path()));
    return value;
}

Napi::Object Alert::StorageMovedFailedAlert(Napi::Env env, lt::storage_moved_failed_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));

        value.Set("error", err);
    }

    value.Set("file_path", Napi::String::New(env, alert->file_path()));
    value.Set("operation", Napi::Number::New(env, static_cast<uint8_t>(alert->op)));

    return value;
}

Napi::Object Alert::TorrentDeletedAlert(Napi::Env env, lt::torrent_deleted_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    std::stringstream ss;
    ss << alert->info_hash;

    value.Set("info_hash", Napi::String::New(env, ss.str()));

    return value;
}

Napi::Object Alert::TorrentDeleteFailedAlert(Napi::Env env, lt::torrent_delete_failed_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));
        
        value.Set("error", err);
    }

    std::stringstream ss;
    ss << alert->info_hash;

    value.Set("info_hash", Napi::String::New(env, ss.str()));

    return value;
}

Napi::Object Alert::SaveResumeDataAlert(Napi::Env env, lt::save_resume_data_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    Napi::Value arg = Napi::External<lt::add_torrent_params>::New(env, &alert->params);
    Napi::Object inst = AddTorrentParams::NewInstance(arg);

    value.Set("params", inst);

    return value;
}

Napi::Object Alert::SaveResumeDataFailedAlert(Napi::Env env, lt::save_resume_data_failed_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));

        value.Set("error", err);
    }

    return value;
}

Napi::Object Alert::UrlSeedAlert(Napi::Env env, lt::url_seed_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));

        value.Set("error", err);
    }

    value.Set("error_message", Napi::String::New(env, alert->error_message()));
    value.Set("server_url", Napi::String::New(env, alert->server_url()));

    return value;
}

Napi::Object Alert::FileErrorAlert(Napi::Env env, lt::file_error_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));

        value.Set("error", err);
    }

    value.Set("filename", Napi::String::New(env, alert->filename()));
    value.Set("op", Napi::Number::New(env, static_cast<uint32_t>(alert->op)));

    return value;
}

Napi::Object Alert::MetadataFailedAlert(Napi::Env env, lt::metadata_failed_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));

        value.Set("error", err);
    }

    return value;
}

Napi::Object Alert::AddTorrentAlert(Napi::Env env, lt::add_torrent_alert* alert)
{
    auto value = TorrentAlert(env, alert);

    if (alert->error)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", Napi::String::New(env, alert->error.message()));
        err.Set("value", Napi::Number::New(env, alert->error.value()));

        value.Set("error", err);
    }

    Napi::Value arg = Napi::External<lt::add_torrent_params>::New(env, &alert->params);
    Napi::Object inst = AddTorrentParams::NewInstance(arg);

    value.Set("params", inst);

    return value;
}

Napi::Object Alert::StateUpdateAlert(Napi::Env env, lt::state_update_alert* alert)
{
    auto val = AlertBase(env, alert);
    auto arr = Napi::Array::New(env, alert->status.size());

    for (size_t i = 0; i < alert->status.size(); i++)
    {
        auto arg = Napi::External<lt::torrent_status>::New(env, &alert->status.at(i));
        arr.Set(i, TorrentStatus::NewInstance(arg));
    }

    val.Set("status", arr);

    return val;
}

Napi::Object Alert::SessionStatsAlert(Napi::Env env, lt::session_stats_alert* alert)
{
    auto val = AlertBase(env, alert);
    auto cnt = alert->counters();
    auto arr = Napi::Array::New(env, cnt.size());

    for (size_t i = 0; i < cnt.size(); i++)
    {
        arr.Set(i, Napi::Number::New(env, cnt[i]));
    }

    val.Set("counters", arr);

    return val;
}
