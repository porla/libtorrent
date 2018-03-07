#ifndef PORLA_LIBTORRENT_TORRENTHANDLE_H
#define PORLA_LIBTORRENT_TORRENTHANDLE_H

#include <memory>
#include <node_api.h>

namespace libtorrent
{
    struct torrent_handle;
}

namespace porla
{
    class TorrentHandle
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);
        static napi_value New(napi_env env, napi_callback_info callback_info);

        static napi_ref constructor;

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);

        static napi_value Status(napi_env env, napi_callback_info callback_info);

        TorrentHandle(napi_env env, libtorrent::torrent_handle const& th);

        napi_env env_;
        napi_ref wrapper_;

        std::unique_ptr<libtorrent::torrent_handle> th_;
    };
}

#endif
