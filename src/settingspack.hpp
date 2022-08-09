#pragma once

#include <libtorrent/settings_pack.hpp>
#include <napi.h>

class SettingsPack
{
public:
    static Napi::Object Wrap(Napi::Env env, const libtorrent::settings_pack& sp);
    static libtorrent::settings_pack Unwrap(const Napi::Object obj);
};
