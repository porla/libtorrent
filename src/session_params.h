#ifndef PORLA_LIBTORRENT_SESSIONPARAMS_H
#define PORLA_LIBTORRENT_SESSIONPARAMS_H

#include <libtorrent/session_params.hpp>
#include <napi.h>

namespace porla
{
    class SessionParams : public Napi::ObjectWrap<SessionParams>
    {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Value arg);

        SessionParams(const Napi::CallbackInfo& info);
        libtorrent::session_params& Wrapped();

    private:
        static Napi::FunctionReference constructor;

        Napi::Value Get_Settings(const Napi::CallbackInfo& info);
        void Set_Settings(const Napi::CallbackInfo& info, const Napi::Value& value);

        std::unique_ptr<libtorrent::session_params> p_;
    };
}

#endif
