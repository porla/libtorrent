#ifndef PORLA_LIBTORRENT_TORRENTINFO_H
#define PORLA_LIBTORRENT_TORRENTINFO_H

#include <memory>
#include <string>

#include <node_api.h>

namespace libtorrent
{
    class torrent_info;
}

namespace porla
{
    class TorrentInfo
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);

        libtorrent::torrent_info& Wrapped();

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);
        static napi_value New(napi_env env, napi_callback_info callback_info);

        static napi_ref constructor;

        TorrentInfo(napi_env env, std::string const& filename);

        napi_env env_;
        napi_ref wrapper_;

        std::unique_ptr<libtorrent::torrent_info> ti_;
    };
}

#endif
