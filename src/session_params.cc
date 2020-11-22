#include "session_params.h"

#include <libtorrent/session_params.hpp>

#include "common.h"
#include "info_hash.h"
#include "settings_pack.h"

using porla::SessionParams;

Napi::FunctionReference SessionParams::constructor;

Napi::Object SessionParams::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "SessionParams",
    {
        InstanceAccessor("settings", &SessionParams::Get_Settings, &SessionParams::Set_Settings),

        /*InstanceAccessor("info_hash", &AddTorrentParams::Get_InfoHash, &AddTorrentParams::Set_InfoHash),
        InstanceAccessor("name", &AddTorrentParams::Get_Name, &AddTorrentParams::Set_Name),
        InstanceAccessor("save_path", &AddTorrentParams::Get_SavePath, &AddTorrentParams::Set_SavePath),
        InstanceAccessor("ti", &AddTorrentParams::Get_TorrentInfo, &AddTorrentParams::Set_TorrentInfo),
        InstanceAccessor("trackers", &AddTorrentParams::Get_Trackers, &AddTorrentParams::Set_Trackers),*/
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("session_params", func);

    return exports;
}

Napi::Object SessionParams::NewInstance(Napi::Value arg)
{
    return constructor.New({ arg });
}

SessionParams::SessionParams(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<SessionParams>(info)
{
    if (info.Length() > 0)
    {
        auto val = info[0].As<Napi::External<lt::session_params>>();
        p_ = std::make_unique<lt::session_params>(*val.Data());
    }
    else
    {
        p_ = std::make_unique<lt::session_params>();
    }
}

libtorrent::session_params& SessionParams::Wrapped()
{
    return *p_.get();
}

Napi::Value SessionParams::Get_Settings(const Napi::CallbackInfo& info)
{
    SettingsPackData data;
    data.owned = true;
    data.pack = &p_->settings;

    auto arg = Napi::External<SettingsPackData>::New(info.Env(), &data);
    return SettingsPack::NewInstance(info.Env(), arg);
}

void SessionParams::Set_Settings(const Napi::CallbackInfo& info, const Napi::Value& value)
{
    SettingsPack* sp = Napi::ObjectWrap<SettingsPack>::Unwrap(value.As<Napi::Object>());
    p_->settings = sp->Wrapped();
}
