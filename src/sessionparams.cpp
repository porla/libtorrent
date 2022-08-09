#include "sessionparams.hpp"

Napi::FunctionReference* SessionParams::m_ctor = nullptr;

Napi::Object SessionParams::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "SessionParams", {
    });

    m_ctor = new Napi::FunctionReference();
    *m_ctor = Napi::Persistent(func);

    exports.Set("SessionParams", func);

    env.SetInstanceData<Napi::FunctionReference>(m_ctor);

    return exports;
}

Napi::Value SessionParams::New(Napi::Env env, const lt::session_params& ts)
{
    if (m_ctor == nullptr)
    {
        Napi::TypeError::New(env, "SessionParams::m_ctor not initialized").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    return m_ctor->New({
        Napi::External<lt::session_params>::New(env, new lt::session_params(ts))
    });
}

SessionParams::SessionParams(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<SessionParams>(info)
{
    m_sp = std::unique_ptr<lt::session_params>(
        info[0].As<Napi::External<lt::session_params>>().Data());
}

SessionParams::~SessionParams() = default;
