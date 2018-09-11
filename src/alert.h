#ifndef PORLA_LIBTORRENT_ALERT_H
#define PORLA_LIBTORRENT_ALERT_H

#include <libtorrent/alert.hpp>
#include <libtorrent/alert_types.hpp>
#include <napi.h>

namespace porla
{
    class Alert
    {
    public:
        static Napi::Value ToJson(Napi::Env env, libtorrent::alert* alert);

    private:
        static Napi::Object AddTorrentAlert(Napi::Env env, libtorrent::add_torrent_alert* alert);
        static Napi::Object AlertBase(Napi::Env env, libtorrent::alert* alert);
        static Napi::Object BlockDownloadingAlert(Napi::Env env, libtorrent::block_downloading_alert* alert);
        static Napi::Object BlockFinishedAlert(Napi::Env env, libtorrent::block_finished_alert* alert);
        static Napi::Object BlockTimeoutAlert(Napi::Env env, libtorrent::block_timeout_alert* alert);
        static Napi::Object DhtReplyAlert(Napi::Env env, libtorrent::dht_reply_alert* alert);
        static Napi::Object FileCompletedAlert(Napi::Env env, libtorrent::file_completed_alert* alert);
        static Napi::Object FileErrorAlert(Napi::Env env, libtorrent::file_error_alert* alert);
        static Napi::Object FileRenamedAlert(Napi::Env env, libtorrent::file_renamed_alert* alert);
        static Napi::Object FileRenameFailedAlert(Napi::Env env, libtorrent::file_rename_failed_alert* alert);
        static Napi::Object HashFailedAlert(Napi::Env env, libtorrent::hash_failed_alert* alert);
        static Napi::Object InvalidRequestAlert(Napi::Env env, libtorrent::invalid_request_alert* alert);
        static Napi::Object MetadataFailedAlert(Napi::Env env, libtorrent::metadata_failed_alert* alert);
        static Napi::Object PeerAlert(Napi::Env env, libtorrent::peer_alert* alert);
        static Napi::Object PeerBanAlert(Napi::Env env, libtorrent::peer_ban_alert* alert);
        static Napi::Object PeerConnectAlert(Napi::Env env, libtorrent::peer_connect_alert* alert);
        static Napi::Object PeerDisconnectedAlert(Napi::Env env, libtorrent::peer_disconnected_alert* alert);
        static Napi::Object PeerErrorAlert(Napi::Env env, libtorrent::peer_error_alert* alert);
        static Napi::Object PerformanceAlert(Napi::Env env, libtorrent::performance_alert* alert);
        static Napi::Object PieceFinishedAlert(Napi::Env env, libtorrent::piece_finished_alert* alert);
        static Napi::Object ReadPieceAlert(Napi::Env env, libtorrent::read_piece_alert* alert);
        static Napi::Object RequestDroppedAlert(Napi::Env env, libtorrent::request_dropped_alert* alert);
        static Napi::Object SaveResumeDataAlert(Napi::Env env, libtorrent::save_resume_data_alert* alert);
        static Napi::Object SaveResumeDataFailedAlert(Napi::Env env, libtorrent::save_resume_data_failed_alert* alert);
        static Napi::Object ScrapeFailedAlert(Napi::Env env, libtorrent::scrape_failed_alert* alert);
        static Napi::Object ScrapeReplyAlert(Napi::Env env, libtorrent::scrape_reply_alert* alert);
        static Napi::Object SessionStatsAlert(Napi::Env env, libtorrent::session_stats_alert* alert);
        static Napi::Object StateChangedAlert(Napi::Env env, libtorrent::state_changed_alert* alert);
        static Napi::Object StateUpdateAlert(Napi::Env env, libtorrent::state_update_alert* alert);
        static Napi::Object StorageMovedAlert(Napi::Env env, libtorrent::storage_moved_alert* alert);
        static Napi::Object StorageMovedFailedAlert(Napi::Env env, libtorrent::storage_moved_failed_alert* alert);
        static Napi::Object TorrentAlert(Napi::Env env, libtorrent::torrent_alert* alert);
        static Napi::Object TorrentDeletedAlert(Napi::Env env, libtorrent::torrent_deleted_alert* alert);
        static Napi::Object TorrentDeleteFailedAlert(Napi::Env env, libtorrent::torrent_delete_failed_alert* alert);
        static Napi::Object TorrentRemovedAlert(Napi::Env env, libtorrent::torrent_removed_alert* alert);
        static Napi::Object TrackerAlert(Napi::Env env, libtorrent::tracker_alert* alert);
        static Napi::Object TrackerAnnounceAlert(Napi::Env env, libtorrent::tracker_announce_alert* alert);
        static Napi::Object TrackerErrorAlert(Napi::Env env, libtorrent::tracker_error_alert* alert);
        static Napi::Object TrackerReplyAlert(Napi::Env env, libtorrent::tracker_reply_alert* alert);
        static Napi::Object TrackerWarningAlert(Napi::Env env, libtorrent::tracker_warning_alert* alert);
        static Napi::Object UnwantedBlockAlert(Napi::Env env, libtorrent::unwanted_block_alert* alert);
        static Napi::Object UrlSeedAlert(Napi::Env env, libtorrent::url_seed_alert* alert);
    };
}

#endif
