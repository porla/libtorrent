#ifndef PORLA_LIBTORRENT_SETTINGSPACK_H
#define PORLA_LIBTORRENT_SETTINGSPACK_H

#include <libtorrent/settings_pack.hpp>
#include <napi.h>

namespace porla
{
    struct SettingsPackData
    {
        bool owned;
        libtorrent::settings_pack* pack;
    };

    class SettingsPack : public Napi::ObjectWrap<SettingsPack>
    {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);

        SettingsPack(const Napi::CallbackInfo& info);

        void Finalize(Napi::Env env);

        libtorrent::settings_pack& Wrapped();

    private:
        Napi::Value GetBool(const Napi::CallbackInfo& info);
        Napi::Value GetInt(const Napi::CallbackInfo& info);
        Napi::Value GetString(const Napi::CallbackInfo& info);
        Napi::Value SetBool(const Napi::CallbackInfo& info);
        Napi::Value SetInt(const Napi::CallbackInfo& info);
        Napi::Value SetString(const Napi::CallbackInfo& info);

        bool owned_;
        libtorrent::settings_pack* sp_;
    };
}

#endif
