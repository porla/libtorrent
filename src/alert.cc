#include "alert.h"

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
