#include "alert.h"

#include "add_torrent_params.h"
#include "common.h"
#include "torrent_handle.h"

#include <libtorrent/torrent_handle.hpp>

using porla::Alert;
namespace lt = libtorrent;

napi_value Alert::ToJson(napi_env env, libtorrent::alert* alert)
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
        default:
            return AlertBase(env, alert);
    }
}

napi_value Alert::AlertBase(napi_env env, libtorrent::alert* alert)
{
    napi_value value;
    napi_create_object(env, &value);

    Value tmp(env, value);
    tmp.SetNamedProperty("category", static_cast<uint32_t>(alert->category()));
    tmp.SetNamedProperty("message", alert->message());
    tmp.SetNamedProperty("timestamp", alert->timestamp().time_since_epoch().count());
    tmp.SetNamedProperty("type", alert->type());
    tmp.SetNamedProperty("what", std::string(alert->what()));

    return value;
}

napi_value Alert::PeerAlert(napi_env env, libtorrent::peer_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    napi_value obj;
    napi_create_object(env, &obj);
    napi_value addr;
    napi_create_string_utf8(env, alert->endpoint.address().to_string().c_str(), NAPI_AUTO_LENGTH, &addr);
    napi_value port;
    napi_create_uint32(env, alert->endpoint.port(), &port);
    napi_set_named_property(env, obj, "address", addr);
    napi_set_named_property(env, obj, "port", port);

    napi_set_named_property(env, value, "endpoint", obj);

    std::stringstream ss;
    ss << alert->pid;

    napi_value pid;
    napi_create_string_utf8(env, ss.str().c_str(), NAPI_AUTO_LENGTH, &pid);
    napi_set_named_property(env, value, "pid", pid);

    return value;
}

napi_value Alert::TorrentAlert(napi_env env, libtorrent::torrent_alert* alert)
{
    napi_value value = AlertBase(env, alert);

    napi_value handle = WrapExternal<TorrentHandle, libtorrent::torrent_handle>(env, &alert->handle);
    napi_set_named_property(env, value, "handle", handle);

    napi_value torrentName;
    napi_create_string_utf8(env, alert->torrent_name(), NAPI_AUTO_LENGTH, &torrentName);
    napi_set_named_property(env, value, "torrent_name", torrentName);

    return value;
}

napi_value Alert::TrackerAlert(napi_env env, libtorrent::tracker_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("tracker_url", std::string(alert->tracker_url()));

    return value;
}

napi_value Alert::TorrentRemovedAlert(napi_env env, libtorrent::torrent_removed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    std::stringstream ss;
    ss << alert->info_hash;

    napi_value hash;
    napi_create_string_utf8(env, ss.str().c_str(), NAPI_AUTO_LENGTH, &hash);
    napi_set_named_property(env, value, "info_hash", hash);

    return value;
}

napi_value Alert::ReadPieceAlert(napi_env env, lt::read_piece_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    if (alert->error)
    {
        napi_value err;
        napi_create_object(env, &err);

        Value errTmp(env, err);
        errTmp.SetNamedProperty("message", alert->error.message());
        errTmp.SetNamedProperty("value", alert->error.value());

        napi_set_named_property(env, value, "error", err);
    }

    Value tmp(env, value);
    tmp.SetNamedProperty("piece", static_cast<int32_t>(alert->piece));
    tmp.SetNamedProperty("size", alert->size);

    if (alert->buffer)
    {
        char* buffer = alert->buffer.get();

        char* data;
        napi_value buf;
        napi_create_buffer(env, alert->size, reinterpret_cast<void**>(&data), &buf);
        napi_set_named_property(env, value, "buffer", buf);

        std::copy(buffer, buffer + alert->size, data);
    }

    return value;
}

napi_value Alert::FileCompletedAlert(napi_env env, lt::file_completed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    napi_value idx;
    napi_create_int32(env, static_cast<int32_t>(alert->index), &idx);
    napi_set_named_property(env, value, "index", idx);

    return value;
}

napi_value Alert::FileRenamedAlert(napi_env env, lt::file_renamed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("index", static_cast<int32_t>(alert->index));
    v.SetNamedProperty("new_name", std::string(alert->new_name()));

    return value;
}

napi_value Alert::FileRenameFailedAlert(napi_env env, lt::file_rename_failed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("index", static_cast<int32_t>(alert->index));

    if (alert->error)
    {
        napi_value err;
        napi_create_object(env, &err);

        Value errTmp(env, err);
        errTmp.SetNamedProperty("message", alert->error.message());
        errTmp.SetNamedProperty("value", alert->error.value());

        napi_set_named_property(env, value, "error", err);
    }

    return value;
}

napi_value Alert::PerformanceAlert(napi_env env, lt::performance_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("warning_code", static_cast<int32_t>(alert->warning_code));

    return value;
}

napi_value Alert::StateChangedAlert(napi_env env, lt::state_changed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("prev_state", static_cast<int32_t>(alert->prev_state));
    v.SetNamedProperty("state", static_cast<int32_t>(alert->state));

    return value;
}

napi_value Alert::TrackerErrorAlert(napi_env env, lt::tracker_error_alert* alert)
{
    napi_value value = TrackerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("error_message", std::string(alert->error_message()));
    v.SetNamedProperty("times_in_row", static_cast<int32_t>(alert->times_in_row));

    if (alert->error)
    {
        napi_value err;
        napi_create_object(env, &err);

        Value errTmp(env, err);
        errTmp.SetNamedProperty("message", alert->error.message());
        errTmp.SetNamedProperty("value", alert->error.value());

        napi_set_named_property(env, value, "error", err);
    }

    return value;
}

napi_value Alert::TrackerWarningAlert(napi_env env, lt::tracker_warning_alert* alert)
{
    napi_value value = TrackerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("warning_message", std::string(alert->warning_message()));

    return value;
}

napi_value Alert::ScrapeReplyAlert(napi_env env, lt::scrape_reply_alert* alert)
{
    napi_value value = TrackerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("complete", alert->complete);
    v.SetNamedProperty("incomplete", alert->incomplete);

    return value;
}

napi_value Alert::ScrapeFailedAlert(napi_env env, lt::scrape_failed_alert* alert)
{
    napi_value value = TrackerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("error_message", std::string(alert->error_message()));

    if (alert->error)
    {
        napi_value err;
        napi_create_object(env, &err);

        Value errTmp(env, err);
        errTmp.SetNamedProperty("message", alert->error.message());
        errTmp.SetNamedProperty("value", alert->error.value());

        napi_set_named_property(env, value, "error", err);
    }

    return value;
}

napi_value Alert::TrackerReplyAlert(napi_env env, lt::tracker_reply_alert* alert)
{
    napi_value value = TrackerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("num_peers", alert->num_peers);

    return value;
}

napi_value Alert::DhtReplyAlert(napi_env env, lt::dht_reply_alert* alert)
{
    napi_value value = TrackerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("num_peers", alert->num_peers);

    return value;
}

napi_value Alert::TrackerAnnounceAlert(napi_env env, lt::tracker_announce_alert* alert)
{
    napi_value value = TrackerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("event", alert->event);

    return value;
}

napi_value Alert::HashFailedAlert(napi_env env, lt::hash_failed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("piece_index", static_cast<int32_t>(alert->piece_index));

    return value;
}

napi_value Alert::PeerBanAlert(napi_env env, lt::peer_ban_alert* alert)
{
    return PeerAlert(env, alert);
}

napi_value Alert::PeerErrorAlert(napi_env env, lt::peer_error_alert* alert)
{
    napi_value value = PeerAlert(env, alert);

    napi_value op;
    napi_create_string_utf8(env, reinterpret_cast<char*>(alert->op), NAPI_AUTO_LENGTH, &op);
    napi_set_named_property(env, value, "op", op);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    return value;
}

napi_value Alert::PeerConnectAlert(napi_env env, lt::peer_connect_alert* alert)
{
    napi_value value = PeerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("socket_type", alert->socket_type);

    return value;
}

napi_value Alert::PeerDisconnectedAlert(napi_env env, lt::peer_disconnected_alert* alert)
{
    napi_value value = PeerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("op", static_cast<uint8_t>(alert->op));
    v.SetNamedProperty("reason", static_cast<uint32_t>(alert->reason));
    v.SetNamedProperty("socket_type", alert->socket_type);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    return value;
}

napi_value Alert::InvalidRequestAlert(napi_env env, lt::invalid_request_alert* alert)
{
    napi_value value = PeerAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("peer_interested", alert->peer_interested);
    v.SetNamedProperty("we_have", alert->we_have);
    v.SetNamedProperty("withheld", alert->withheld);

    napi_value req;
    napi_create_object(env, &req);

    Value r(env, value);
    r.SetNamedProperty("length", alert->request.length);
    r.SetNamedProperty("piece", static_cast<int32_t>(alert->request.piece));
    r.SetNamedProperty("start", alert->request.start);

    napi_set_named_property(env, value, "request", req);

    return value;
}

napi_value Alert::PieceFinishedAlert(napi_env env, lt::piece_finished_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("piece_index", static_cast<int32_t>(alert->piece_index));

    return value;
}

napi_value Alert::RequestDroppedAlert(napi_env env, lt::request_dropped_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("block_index", alert->block_index);
    v.SetNamedProperty("piece_index", static_cast<int32_t>(alert->piece_index));

    return value;
}

napi_value Alert::BlockTimeoutAlert(napi_env env, lt::block_timeout_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("block_index", alert->block_index);
    v.SetNamedProperty("piece_index", static_cast<int32_t>(alert->piece_index));

    return value;
}

napi_value Alert::BlockFinishedAlert(napi_env env, lt::block_finished_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("block_index", alert->block_index);
    v.SetNamedProperty("piece_index", static_cast<int32_t>(alert->piece_index));

    return value;
}

napi_value Alert::BlockDownloadingAlert(napi_env env, lt::block_downloading_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("block_index", alert->block_index);
    v.SetNamedProperty("piece_index", static_cast<int32_t>(alert->piece_index));

    return value;
}

napi_value Alert::UnwantedBlockAlert(napi_env env, lt::unwanted_block_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("block_index", alert->block_index);
    v.SetNamedProperty("piece_index", static_cast<int32_t>(alert->piece_index));

    return value;
}

napi_value Alert::StorageMovedAlert(napi_env env, lt::storage_moved_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    Value v(env, value);
    v.SetNamedProperty("storage_path", std::string(alert->storage_path()));

    return value;
}

napi_value Alert::StorageMovedFailedAlert(napi_env env, lt::storage_moved_failed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    Value v(env, value);
    v.SetNamedProperty("file_path", std::string(alert->file_path()));
    v.SetNamedProperty("operation", static_cast<uint8_t>(alert->op));

    return value;
}

napi_value Alert::TorrentDeletedAlert(napi_env env, lt::torrent_deleted_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    std::stringstream ss;
    ss << alert->info_hash;

    Value v(env, value);
    v.SetNamedProperty("info_hash", ss.str());

    return value;
}

napi_value Alert::TorrentDeleteFailedAlert(napi_env env, lt::torrent_delete_failed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    std::stringstream ss;
    ss << alert->info_hash;

    Value v(env, value);
    v.SetNamedProperty("info_hash", ss.str());

    return value;
}

napi_value Alert::SaveResumeDataAlert(napi_env env, lt::save_resume_data_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    napi_value params = WrapExternal<AddTorrentParams, lt::add_torrent_params>(env, &alert->params);
    napi_set_named_property(env, value, "params", params);

    return value;
}

napi_value Alert::SaveResumeDataFailedAlert(napi_env env, lt::save_resume_data_failed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    return value;
}

napi_value Alert::UrlSeedAlert(napi_env env, lt::url_seed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    Value v(env, value);
    v.SetNamedProperty("error_message", std::string(alert->error_message()));
    v.SetNamedProperty("server_url", std::string(alert->server_url()));

    return value;
}

napi_value Alert::FileErrorAlert(napi_env env, lt::file_error_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    Value v(env, value);
    v.SetNamedProperty("filename", std::string(alert->filename()));
    v.SetNamedProperty("op", static_cast<uint32_t>(alert->op));

    return value;
}

napi_value Alert::MetadataFailedAlert(napi_env env, lt::metadata_failed_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    return value;
}

napi_value Alert::AddTorrentAlert(napi_env env, lt::add_torrent_alert* alert)
{
    napi_value value = TorrentAlert(env, alert);

    if (alert->error)
    {
        napi_value message;
        napi_create_string_utf8(env, alert->error.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value val;
        napi_create_int32(env, alert->error.value(), &val);

        napi_value err;
        napi_create_object(env, &err);
        napi_set_named_property(env, err, "message", message);
        napi_set_named_property(env, err, "value", val);

        napi_set_named_property(env, value, "error", err);
    }

    // TODO: params

    return value;
}
