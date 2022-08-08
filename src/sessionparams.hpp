#pragma once

#include <memory>

#include <libtorrent/session_params.hpp>
#include <napi.h>

class SessionParams : public Napi::ObjectWrap<SessionParams>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Value New(Napi::Env env, const libtorrent::session_params &sp);

    explicit SessionParams(const Napi::CallbackInfo &info);
    ~SessionParams() override;

    libtorrent::session_params& GetWrapped() { return *m_sp; }

private:
    std::unique_ptr<libtorrent::session_params> m_sp;

    static Napi::FunctionReference* m_ctor;
};
