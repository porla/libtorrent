#include "alert.hpp"

#include "addtorrentparams.hpp"
#include "errorcode.hpp"
#include "infohash.hpp"
#include "torrenthandle.hpp"
#include "torrentstatus.hpp"

Napi::Value AlertWrap::Wrap(Napi::Env env, const libtorrent::alert* alert)
{
    switch (alert->type())
    {
    case lt::add_torrent_alert::alert_type:
        return AddTorrentAlert(env, lt::alert_cast<lt::add_torrent_alert>(alert));
    case lt::metadata_received_alert::alert_type:
        return TorrentAlert(env, lt::alert_cast<lt::metadata_received_alert>(alert));
    case lt::save_resume_data_alert::alert_type:
        return SaveResumeDataAlert(env, lt::alert_cast<lt::save_resume_data_alert>(alert));
    case lt::save_resume_data_failed_alert::alert_type:
        return SaveResumeDataFailedAlert(env, lt::alert_cast<lt::save_resume_data_failed_alert>(alert));
    case lt::state_update_alert::alert_type:
        return StateUpdateAlert(env, lt::alert_cast<lt::state_update_alert>(alert));
    case lt::storage_moved_alert::alert_type:
        return StorageMovedAlert(env, lt::alert_cast<lt::storage_moved_alert>(alert));
    case lt::storage_moved_failed_alert::alert_type:
        return StorageMovedFailedAlert(env, lt::alert_cast<lt::storage_moved_failed_alert>(alert));
    case lt::torrent_error_alert::alert_type:
        return TorrentErrorAlert(env, lt::alert_cast<lt::torrent_error_alert>(alert));
    case lt::torrent_finished_alert::alert_type:
        return TorrentAlert(env, lt::alert_cast<lt::torrent_finished_alert>(alert));
    case lt::torrent_paused_alert::alert_type:
        return TorrentAlert(env, lt::alert_cast<lt::torrent_paused_alert>(alert));
    case lt::torrent_removed_alert::alert_type:
        return TorrentRemovedAlert(env, lt::alert_cast<lt::torrent_removed_alert>(alert));
    case lt::torrent_resumed_alert::alert_type:
        return TorrentAlert(env, lt::alert_cast<lt::torrent_resumed_alert>(alert));
    }

    return Alert(env, alert);
}

Napi::Object AlertWrap::Alert(Napi::Env env, const libtorrent::alert *alert)
{
    Napi::Object a = Napi::Object::New(env);
    a.Set("message", Napi::String::New(env, alert->message()));
    return a;
}

Napi::Object AlertWrap::TorrentAlert(Napi::Env env, const libtorrent::torrent_alert *alert)
{
    Napi::Object a = Alert(env, alert);
    a.Set("handle", TorrentHandle::New(env, alert->handle));
    a.Set("torrent_name", Napi::String::New(env, alert->torrent_name()));
    return a;
}

Napi::Object AlertWrap::AddTorrentAlert(Napi::Env env, const libtorrent::add_torrent_alert *alert)
{
    Napi::Object a = TorrentAlert(env, alert);
    a.Set("error", ErrorCode::Wrap(env, alert->error));
    a.Set("params", AddTorrentParams::New(env, alert->params));
    return a;
}

Napi::Object AlertWrap::SaveResumeDataAlert(Napi::Env env, const libtorrent::save_resume_data_alert *alert)
{
    auto a = TorrentAlert(env, alert);
    a.Set("params", AddTorrentParams::New(env, alert->params));
    return a;
}

Napi::Object AlertWrap::SaveResumeDataFailedAlert(Napi::Env env, const libtorrent::save_resume_data_failed_alert *alert)
{
    auto a = TorrentAlert(env, alert);
    a.Set("error", ErrorCode::Wrap(env, alert->error));
    return a;
}

Napi::Object AlertWrap::StateUpdateAlert(Napi::Env env, const libtorrent::state_update_alert* alert)
{
    Napi::Object a = Alert(env, alert);

    Napi::Array status = Napi::Array::New(env, alert->status.size());

    for (size_t idx = 0; idx < alert->status.size(); idx++)
    {
        status[idx] = TorrentStatus::New(env, alert->status.at(idx));
    }

    a.Set("status", status);

    return a;
}

Napi::Object AlertWrap::StorageMovedAlert(Napi::Env env, const libtorrent::storage_moved_alert *alert)
{
    auto a = TorrentAlert(env, alert);
    a.Set("old_path", Napi::String::New(env, alert->old_path()));
    a.Set("storage_path", Napi::String::New(env, alert->storage_path()));
    return a;
}

Napi::Object AlertWrap::StorageMovedFailedAlert(Napi::Env env, const libtorrent::storage_moved_failed_alert *alert)
{
    auto a = TorrentAlert(env, alert);
    a.Set("error", ErrorCode::Wrap(env, alert->error));
    a.Set("file_path", Napi::String::New(env, alert->file_path()));
    return a;
}

Napi::Object AlertWrap::TorrentErrorAlert(Napi::Env env, const libtorrent::torrent_error_alert *alert)
{
    auto a = TorrentAlert(env, alert);
    a.Set("error", ErrorCode::Wrap(env, alert->error));
    a.Set("filename", Napi::String::New(env, alert->filename()));
    return a;
}

Napi::Object AlertWrap::TorrentRemovedAlert(Napi::Env env, const libtorrent::torrent_removed_alert *alert)
{
    auto a = TorrentAlert(env, alert);
    a.Set("info_hashes", InfoHash::New(env, alert->info_hashes));
    return a;
}
