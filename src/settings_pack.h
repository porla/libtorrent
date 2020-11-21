#ifndef PORLA_LIBTORRENT_SETTINGSPACK_H
#define PORLA_LIBTORRENT_SETTINGSPACK_H

#include <libtorrent/settings_pack.hpp>
#include <napi.h>

namespace porla
{
    class SettingsPack : public Napi::ObjectWrap<SettingsPack>
    {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Value arg);

        SettingsPack(const Napi::CallbackInfo& info);
        libtorrent::settings_pack& Wrapped();

    private:
        static Napi::FunctionReference constructor;

        Napi::Value GetBool(const Napi::CallbackInfo& info);
        Napi::Value GetInt(const Napi::CallbackInfo& info);
        Napi::Value GetString(const Napi::CallbackInfo& info);
        Napi::Value SetBool(const Napi::CallbackInfo& info);
        Napi::Value SetInt(const Napi::CallbackInfo& info);
        Napi::Value SetString(const Napi::CallbackInfo& info);

        std::unique_ptr<libtorrent::settings_pack> sp_;
    };
}

#endif
