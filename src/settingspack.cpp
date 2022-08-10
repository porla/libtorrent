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
        std::string key = Napi::Value(property).ToString().Utf8Value();
        int setting = lt::setting_by_name(key);

        if (setting < 0)
        {
            throw Napi::Error::New(obj.Env(), "Unknown setting: " + key);
        }

        try
        {
            Napi::Value value = obj[property];

            switch (setting & lt::settings_pack::type_mask)
            {
            case lt::settings_pack::string_type_base:
                sp.set_str(setting, value.ToString().Utf8Value());
                break;
            case lt::settings_pack::int_type_base:
                sp.set_int(setting, static_cast<int>(value.ToNumber().Int64Value()));
                break;
            case lt::settings_pack::bool_type_base:
                sp.set_bool(setting, value.ToBoolean().Value());
                break;
            }
        }
        catch (const std::exception&) {}
    }

    return sp;
}
