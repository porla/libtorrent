#ifndef PORLA_LIBTORRENT_SETTINGSPACK_H
#define PORLA_LIBTORRENT_SETTINGSPACK_H

#include <libtorrent/settings_pack.hpp>
#include <node_api.h>

namespace porla
{
    class SettingsPack
    {
    public:
        static napi_value Objectify(napi_env env, libtorrent::settings_pack const& settings);
        static libtorrent::settings_pack Parse(napi_env env, napi_value value);
    };
}

#endif
