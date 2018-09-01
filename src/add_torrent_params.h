#ifndef PORLA_LIBTORRENT_ADDTORRENTPARAMS_H
#define PORLA_LIBTORRENT_ADDTORRENTPARAMS_H

#include <libtorrent/add_torrent_params.hpp>
#include <node_api.h>

namespace porla
{
    class AddTorrentParams
    {
    public:
        static libtorrent::add_torrent_params Parse(napi_env env, napi_value value);
    };
}

#endif
