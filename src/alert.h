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
        static napi_value BlockDownloadingAlert(napi_env env, libtorrent::block_downloading_alert* alert);
        static napi_value BlockFinishedAlert(napi_env env, libtorrent::block_finished_alert* alert);
        static napi_value BlockTimeoutAlert(napi_env env, libtorrent::block_timeout_alert* alert);
        static napi_value DhtReplyAlert(napi_env env, libtorrent::dht_reply_alert* alert);
        static napi_value FileCompletedAlert(napi_env env, libtorrent::file_completed_alert* alert);
        static napi_value FileRenamedAlert(napi_env env, libtorrent::file_renamed_alert* alert);
        static napi_value FileRenameFailedAlert(napi_env env, libtorrent::file_rename_failed_alert* alert);
        static napi_value HashFailedAlert(napi_env env, libtorrent::hash_failed_alert* alert);
        static napi_value InvalidRequestAlert(napi_env env, libtorrent::invalid_request_alert* alert);
        static napi_value PeerAlert(napi_env env, libtorrent::peer_alert* alert);
        static napi_value PeerBanAlert(napi_env env, libtorrent::peer_ban_alert* alert);
        static napi_value PeerConnectAlert(napi_env env, libtorrent::peer_connect_alert* alert);
        static napi_value PeerDisconnectedAlert(napi_env env, libtorrent::peer_disconnected_alert* alert);
        static napi_value PeerErrorAlert(napi_env env, libtorrent::peer_error_alert* alert);
        static napi_value PerformanceAlert(napi_env env, libtorrent::performance_alert* alert);
        static napi_value PieceFinishedAlert(napi_env env, libtorrent::piece_finished_alert* alert);
        static napi_value ReadPieceAlert(napi_env env, libtorrent::read_piece_alert* alert);
        static napi_value RequestDroppedAlert(napi_env env, libtorrent::request_dropped_alert* alert);
        static napi_value SaveResumeDataAlert(napi_env env, libtorrent::save_resume_data_alert* alert);
        static napi_value SaveResumeDataFailedAlert(napi_env env, libtorrent::save_resume_data_failed_alert* alert);
        static napi_value ScrapeFailedAlert(napi_env env, libtorrent::scrape_failed_alert* alert);
        static napi_value ScrapeReplyAlert(napi_env env, libtorrent::scrape_reply_alert* alert);
        static napi_value StateChangedAlert(napi_env env, libtorrent::state_changed_alert* alert);
        static napi_value StorageMovedAlert(napi_env env, libtorrent::storage_moved_alert* alert);
        static napi_value StorageMovedFailedAlert(napi_env env, libtorrent::storage_moved_failed_alert* alert);
        static napi_value TorrentAlert(napi_env env, libtorrent::torrent_alert* alert);
        static napi_value TorrentDeletedAlert(napi_env env, libtorrent::torrent_deleted_alert* alert);
        static napi_value TorrentDeleteFailedAlert(napi_env env, libtorrent::torrent_delete_failed_alert* alert);
        static napi_value TorrentRemovedAlert(napi_env env, libtorrent::torrent_removed_alert* alert);
        static napi_value TrackerAlert(napi_env env, libtorrent::tracker_alert* alert);
        static napi_value TrackerAnnounceAlert(napi_env env, libtorrent::tracker_announce_alert* alert);
        static napi_value TrackerErrorAlert(napi_env env, libtorrent::tracker_error_alert* alert);
        static napi_value TrackerReplyAlert(napi_env env, libtorrent::tracker_reply_alert* alert);
        static napi_value TrackerWarningAlert(napi_env env, libtorrent::tracker_warning_alert* alert);
        static napi_value UnwantedBlockAlert(napi_env env, libtorrent::unwanted_block_alert* alert);
        static napi_value UrlSeedAlert(napi_env env, libtorrent::url_seed_alert* alert);
    };
}

#endif
