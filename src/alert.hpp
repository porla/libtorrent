#pragma once

#include <libtorrent/alert_types.hpp>
#include <napi.h>

class AlertWrap
{
public:
    static Napi::Value Wrap(Napi::Env env, const libtorrent::alert* alert);

private:
    static Napi::Object Alert(Napi::Env env, const libtorrent::alert* alert);
    static Napi::Object TorrentAlert(Napi::Env env, const libtorrent::torrent_alert* alert);

    static Napi::Object AddTorrentAlert(Napi::Env env, const libtorrent::add_torrent_alert* alert);
    static Napi::Object SaveResumeDataAlert(Napi::Env env, const libtorrent::save_resume_data_alert* alert);
    static Napi::Object SaveResumeDataFailedAlert(Napi::Env env, const libtorrent::save_resume_data_failed_alert* alert);
    static Napi::Object StateUpdateAlert(Napi::Env env, const libtorrent::state_update_alert* alert);
};
