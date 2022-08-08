#pragma once

#include <libtorrent/fwd.hpp>
#include <napi.h>

class AddTorrentParams
{
public:
    static libtorrent::add_torrent_params Unwrap(Napi::Env env, const Napi::Object& obj);
    static Napi::Value Wrap(Napi::Env env, const libtorrent::add_torrent_params& params);
};
