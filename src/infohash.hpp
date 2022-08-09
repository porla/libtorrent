#pragma once

#include <memory>

#include <libtorrent/info_hash.hpp>
#include <napi.h>

class InfoHash : public Napi::ObjectWrap<InfoHash>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Value New(Napi::Env env, const libtorrent::info_hash_t& ih);

    explicit InfoHash(const Napi::CallbackInfo& info);
    ~InfoHash() override;

    explicit operator libtorrent::info_hash_t() { return *m_hash; }

private:
    Napi::Value GetV1(const Napi::CallbackInfo& info);
    Napi::Value GetV2(const Napi::CallbackInfo& info);
    Napi::Value HasV1(const Napi::CallbackInfo& info);
    Napi::Value HasV2(const Napi::CallbackInfo& info);

    std::unique_ptr<libtorrent::info_hash_t> m_hash;

    static Napi::FunctionReference* m_ctor;
};
