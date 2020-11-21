#include "settings_pack.h"

#include <map>

#include "common.h"

using porla::SettingsPack;

static const std::map<std::string, int> BoolTypes =
{
    { "enable_dht",                 lt::settings_pack::bool_types::enable_dht }
};

static const std::map<std::string, int> IntTypes =
{
    { "alert_mask",                 lt::settings_pack::int_types::alert_mask },
    { "tracker_completion_timeout", lt::settings_pack::int_types::tracker_completion_timeout }
};

static const std::map<std::string, int> StringTypes =
{
    { "peer_fingerprint",                 lt::settings_pack::string_types::peer_fingerprint }
};

Napi::FunctionReference SettingsPack::constructor;

Napi::Object SettingsPack::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "SettingsPack",
    {
        InstanceMethod("get_bool", &SettingsPack::GetBool),
        InstanceMethod("get_int", &SettingsPack::GetInt),
        InstanceMethod("get_str", &SettingsPack::GetString),
        InstanceMethod("set_bool", &SettingsPack::SetBool),
        InstanceMethod("set_int", &SettingsPack::SetInt),
        InstanceMethod("set_str", &SettingsPack::SetString)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("settings_pack", func);

    return exports;
}

Napi::Object SettingsPack::NewInstance(Napi::Value arg)
{
    return constructor.New({ arg });
}

SettingsPack::SettingsPack(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<SettingsPack>(info)
{
    if (info.Length() > 0)
    {
        auto val = info[0].As<Napi::External<lt::settings_pack>>();
        sp_ = std::make_unique<lt::settings_pack>(*val.Data());
    }
    else
    {
        sp_ = std::make_unique<lt::settings_pack>();
    }
}

libtorrent::settings_pack& SettingsPack::Wrapped()
{
    return *sp_.get();
}

Napi::Value SettingsPack::GetBool(const Napi::CallbackInfo& info)
{
    auto spb = BoolTypes.find(info[0].ToString().Utf8Value());
    if (spb != BoolTypes.end())
    {
        return Napi::Boolean::New(info.Env(), sp_->get_bool(spb->second));
    }
    return info.Env().Undefined();
}

Napi::Value SettingsPack::GetInt(const Napi::CallbackInfo& info)
{
    auto spi = IntTypes.find(info[0].ToString().Utf8Value());
    if (spi != IntTypes.end())
    {
        return Napi::Number::New(info.Env(), sp_->get_int(spi->second));
    }
    return info.Env().Undefined();
}

Napi::Value SettingsPack::GetString(const Napi::CallbackInfo& info)
{
    auto sps = StringTypes.find(info[0].ToString().Utf8Value());
    if (sps != StringTypes.end())
    {
        return Napi::String::New(info.Env(), sp_->get_str(sps->second));
    }
    return info.Env().Undefined();
}

Napi::Value SettingsPack::SetBool(const Napi::CallbackInfo& info)
{
    auto spb = BoolTypes.find(info[0].ToString().Utf8Value());
    if (spb != BoolTypes.end())
    {
        sp_->set_bool(spb->second, info[1].ToBoolean().Value());
    }
    return info.Env().Undefined();
}

Napi::Value SettingsPack::SetInt(const Napi::CallbackInfo& info)
{
    auto spi = IntTypes.find(info[0].ToString().Utf8Value());
    if (spi != IntTypes.end())
    {
        sp_->set_int(spi->second, info[1].ToNumber().Int32Value());
    }
    return info.Env().Undefined();
}

Napi::Value SettingsPack::SetString(const Napi::CallbackInfo& info)
{
    auto sps = StringTypes.find(info[0].ToString().Utf8Value());
    if (sps != StringTypes.end())
    {
        sp_->set_str(sps->second, info[1].ToString().Utf8Value());
    }
    return info.Env().Undefined();
}
