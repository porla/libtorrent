#ifndef PORLA_LIBTORRENT_ADDTORRENTPARAMS_H
#define PORLA_LIBTORRENT_ADDTORRENTPARAMS_H

#include <libtorrent/add_torrent_params.hpp>
#include <node_api.h>

namespace porla
{
    class AddTorrentParams
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);
        static napi_ref constructor;

        libtorrent::add_torrent_params& Wrapped();

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);
        static napi_value New(napi_env env, napi_callback_info cbinfo);

        static napi_value Get_SavePath(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TorrentInfo(napi_env env, napi_callback_info cbinfo);
        static napi_value Set_SavePath(napi_env env, napi_callback_info cbinfo);
        static napi_value Set_TorrentInfo(napi_env env, napi_callback_info cbinfo);

        AddTorrentParams();
        AddTorrentParams(libtorrent::add_torrent_params const& params);

        napi_ref wrapper_;

        std::unique_ptr<libtorrent::add_torrent_params> p_;
    };
}

#endif
