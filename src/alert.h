#ifndef PORLA_LIBTORRENT_ALERT_H
#define PORLA_LIBTORRENT_ALERT_H

#include <libtorrent/alert.hpp>
#include <libtorrent/alert_types.hpp>
#include <node_api.h>

namespace porla
{
    class Alert
    {
    public:
        static napi_value ToJson(napi_env env, libtorrent::alert* alert);

    private:
        static napi_value AlertBase(napi_env env, libtorrent::alert* alert);
        static napi_value DhtReplyAlert(napi_env env, libtorrent::dht_reply_alert* alert);
        static napi_value FileCompletedAlert(napi_env env, libtorrent::file_completed_alert* alert);
        static napi_value FileRenamedAlert(napi_env env, libtorrent::file_renamed_alert* alert);
        static napi_value FileRenameFailedAlert(napi_env env, libtorrent::file_rename_failed_alert* alert);
        static napi_value HashFailedAlert(napi_env env, libtorrent::hash_failed_alert* alert);
        static napi_value PerformanceAlert(napi_env env, libtorrent::performance_alert* alert);
        static napi_value ReadPieceAlert(napi_env env, libtorrent::read_piece_alert* alert);
        static napi_value ScrapeFailedAlert(napi_env env, libtorrent::scrape_failed_alert* alert);
        static napi_value ScrapeReplyAlert(napi_env env, libtorrent::scrape_reply_alert* alert);
        static napi_value StateChangedAlert(napi_env env, libtorrent::state_changed_alert* alert);
        static napi_value TorrentAlert(napi_env env, libtorrent::torrent_alert* alert);
        static napi_value TorrentRemovedAlert(napi_env env, libtorrent::torrent_removed_alert* alert);
        static napi_value TrackerAlert(napi_env env, libtorrent::tracker_alert* alert);
        static napi_value TrackerAnnounceAlert(napi_env env, libtorrent::tracker_announce_alert* alert);
        static napi_value TrackerErrorAlert(napi_env env, libtorrent::tracker_error_alert* alert);
        static napi_value TrackerReplyAlert(napi_env env, libtorrent::tracker_reply_alert* alert);
        static napi_value TrackerWarningAlert(napi_env env, libtorrent::tracker_warning_alert* alert);
    };
}

#endif
