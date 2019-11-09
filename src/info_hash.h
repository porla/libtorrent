#ifndef PORLA_LIBTORRENT_INFO_HASH_H
#define PORLA_LIBTORRENT_INFO_HASH_H

#include <libtorrent/info_hash.hpp>
#include <napi.h>

namespace porla
{
    class InfoHash
    {
    public:
        static Napi::Value ToString(Napi::Env env, libtorrent::info_hash_t const& hash);
    };
}

#endif
