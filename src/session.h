#ifndef PORLA_LIBTORRENT_SESSION_H
#define PORLA_LIBTORRENT_SESSION_H

#include <memory>
#include <node_api.h>

namespace libtorrent
{
    class session;
    struct settings_pack;
}

namespace porla
{
    class Session
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);
        static napi_value New(napi_env env, napi_callback_info callback_info);

        static napi_value AddDhtNode(napi_env, napi_callback_info callback_info);
        static napi_value AddPortMapping(napi_env, napi_callback_info callback_info);
        static napi_value AddTorrent(napi_env env, napi_callback_info callback_info);
        static napi_value ApplySettings(napi_env env, napi_callback_info callback_info);
        static napi_value AsyncAddTorrent(napi_env env, napi_callback_info callback_info);
        static napi_value CreatePeerClass(napi_env env, napi_callback_info callback_info);
        static napi_value DeletePeerClass(napi_env env, napi_callback_info callback_info);
        static napi_value DeletePortMapping(napi_env env, napi_callback_info callback_info);
        static napi_value DhtAnnounce(napi_env env, napi_callback_info callback_info);
        static napi_value DhtDirectRequest(napi_env env, napi_callback_info callback_info);
        static napi_value DhtGetItem(napi_env env, napi_callback_info callback_info);
        static napi_value DhtGetPeers(napi_env env, napi_callback_info callback_info);
        static napi_value DhtLiveNodes(napi_env env, napi_callback_info callback_info);
        static napi_value DhtPutItem(napi_env env, napi_callback_info callback_info);
        static napi_value DhtSampleInfohashes(napi_env env, napi_callback_info callback_info);
        static napi_value FindTorrent(napi_env env, napi_callback_info callback_info);
        static napi_value GetCacheInfo(napi_env env, napi_callback_info callback_info);
        static napi_value GetDhtSettings(napi_env env, napi_callback_info callback_info);
        static napi_value GetIpFilter(napi_env env, napi_callback_info callback_info);
        static napi_value GetPeerClass(napi_env env, napi_callback_info callback_info);
        static napi_value GetPeerClassFilter(napi_env env, napi_callback_info callback_info);
        static napi_value GetPeerClassTypeFilter(napi_env env, napi_callback_info callback_info);
        static napi_value GetSettings(napi_env env, napi_callback_info callback_info);
        static napi_value GetTorrentStatus(napi_env env, napi_callback_info callback_info);
        static napi_value GetTorrents(napi_env env, napi_callback_info callback_info);
        static napi_value IsDhtRunning(napi_env env, napi_callback_info callback_info);
        static napi_value IsListening(napi_env env, napi_callback_info callback_info);
        static napi_value IsPaused(napi_env env, napi_callback_info callback_info);
        static napi_value IsValid(napi_env env, napi_callback_info callback_info);
        static napi_value ListenPort(napi_env env, napi_callback_info callback_info);
        static napi_value LoadState(napi_env env, napi_callback_info callback_info);
        static napi_value Pause(napi_env env, napi_callback_info callback_info);
        static napi_value PopAlerts(napi_env env, napi_callback_info callback_info);
        static napi_value PostDhtStats(napi_env env, napi_callback_info callback_info);
        static napi_value PostSessionStats(napi_env env, napi_callback_info callback_info);
        static napi_value PostTorrentUpdates(napi_env env, napi_callback_info callback_info);
        static napi_value RefreshTorrentStatus(napi_env env, napi_callback_info callback_info);
        static napi_value RemoveTorrent(napi_env env, napi_callback_info callback_info);
        static napi_value ReopenNetworkSockets(napi_env env, napi_callback_info callback_info);
        static napi_value Resume(napi_env env, napi_callback_info callback_info);
        static napi_value SaveState(napi_env env, napi_callback_info callback_info);
        static napi_value SetDhtSettings(napi_env env, napi_callback_info callback_info);
        static napi_value SetIpFilter(napi_env env, napi_callback_info callback_info);
        static napi_value SetPeerClass(napi_env env, napi_callback_info callback_info);
        static napi_value SetPeerClassFilter(napi_env env, napi_callback_info callback_info);
        static napi_value SetPeerClassTypeFilter(napi_env env, napi_callback_info callback_info);
        static napi_value SetPortFilter(napi_env env, napi_callback_info callback_info);
        static napi_value SslListenPort(napi_env env, napi_callback_info callback_info);
        static napi_value WaitForAlert(napi_env env, napi_callback_info callback_info);

        static void WaitForAlertComplete(napi_env env, napi_status status, void* data);
        static void WaitForAlertExecute(napi_env env, void* data);

        static napi_ref constructor;

        Session(napi_env env, libtorrent::settings_pack& settings);

        napi_env env_;
        napi_ref wrapper_;

        std::unique_ptr<libtorrent::session> session_;
    };
}

#endif
