#ifndef PORLA_LIBTORRENT_ENTRY_H
#define PORLA_LIBTORRENT_ENTRY_H

#include <libtorrent/entry.hpp>
#include <node_api.h>

namespace porla
{
    class Entry
    {
    public:
        static libtorrent::entry FromJson(napi_env env, napi_value value);
        static napi_value ToJson(napi_env env, libtorrent::entry const& entry);
    };
}

#endif
