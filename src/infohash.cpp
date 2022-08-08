#include "infohash.hpp"

#include <sstream>

namespace lt = libtorrent;

Napi::FunctionReference* InfoHash::m_ctor = nullptr;

Napi::Object InfoHash::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "InfoHash", {
        InstanceAccessor<&InfoHash::GetV1>("v1"),
        InstanceAccessor<&InfoHash::GetV2>("v2"),
        InstanceMethod<&InfoHash::HasV1>("has_v1"),
        InstanceMethod<&InfoHash::HasV2>("has_v2")
    });

    m_ctor = new Napi::FunctionReference();
    *m_ctor = Napi::Persistent(func);

    env.SetInstanceData<Napi::FunctionReference>(m_ctor);

    return exports;
}

Napi::Value InfoHash::New(Napi::Env env, const lt::info_hash_t& hash)
{
    if (m_ctor == nullptr)
    {
        Napi::TypeError::New(env, "InfoHash::m_ctor not initialized").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    return m_ctor->New({
        Napi::External<lt::info_hash_t>::New(env, new lt::info_hash_t(hash))
    });
}

InfoHash::InfoHash(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<InfoHash>(info)
{
    m_hash = std::unique_ptr<lt::info_hash_t>(
        info[0].As<Napi::External<lt::info_hash_t>>().Data());
}

InfoHash::~InfoHash() = default;

Napi::Value InfoHash::GetV1(const Napi::CallbackInfo &info)
{
    if (m_hash->has_v1())
    {
        std::stringstream ss;
        ss << m_hash->v1;
        return Napi::String::New(info.Env(), ss.str());
    }

    return info.Env().Null();
}

Napi::Value InfoHash::GetV2(const Napi::CallbackInfo &info)
{
    if (m_hash->has_v2())
    {
        std::stringstream ss;
        ss << m_hash->v2;
        return Napi::String::New(info.Env(), ss.str());
    }

    return info.Env().Null();
}

Napi::Value InfoHash::HasV1(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_hash->has_v1());
}

Napi::Value InfoHash::HasV2(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_hash->has_v2());
}
