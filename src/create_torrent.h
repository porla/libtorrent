#ifndef PORLA_LIBTORRENT_CREATETORRENT_H
#define PORLA_LIBTORRENT_CREATETORRENT_H

#include <memory>
#include <string>

#include <libtorrent/create_torrent.hpp>
#include <node_api.h>

namespace porla
{
    class CreateTorrent
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);
        static napi_ref constructor;

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);
        static napi_value New(napi_env env, napi_callback_info callback_info);

        static napi_value Generate(napi_env env, napi_callback_info cbinfo);
        static napi_value GenerateBuf(napi_env env, napi_callback_info cbinfo);

        CreateTorrent();
        CreateTorrent(libtorrent::torrent_info const& ti);

        napi_ref wrapper_;

        std::unique_ptr<libtorrent::create_torrent> ct_;
    };
}

#endif
