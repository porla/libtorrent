#include "settingspack.hpp"

namespace lt = libtorrent;

Napi::Object SettingsPack::Wrap(Napi::Env env, const lt::settings_pack &sp)
{
    auto obj = Napi::Object::New(env);

    for (int i = lt::settings_pack::string_type_base; i < lt::settings_pack::max_string_setting_internal; i++)
    {
        auto name = lt::name_for_setting(i);
        if (name[0] != '\0' && sp.has_val(i)) { obj.Set(name, sp.get_str(i)); }
    }

    for (int i = lt::settings_pack::int_type_base; i < lt::settings_pack::max_int_setting_internal; i++)
    {
        auto name = lt::name_for_setting(i);
        if (name[0] != '\0' && sp.has_val(i)) { obj.Set(name, sp.get_int(i)); }
    }

    for (int i = lt::settings_pack::bool_type_base; i < lt::settings_pack::max_bool_setting_internal; i++)
    {
        auto name = lt::name_for_setting(i);
        if (name[0] != '\0' && sp.has_val(i)) { obj.Set(name, sp.get_bool(i)); }
    }

    return obj;
}

lt::settings_pack SettingsPack::Unwrap(const Napi::Object obj)
{
    lt::settings_pack sp;

    for (const auto&& [index,property] : obj.GetPropertyNames())
    {
    }

    return sp;
}
