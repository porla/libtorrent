#include "torrentstatus.hpp"

#include <libtorrent/torrent_status.hpp>

namespace lt = libtorrent;

Napi::FunctionReference* TorrentStatus::m_ctor = nullptr;

Napi::Object TorrentStatus::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "TorrentStatus", {
        InstanceMethod<&TorrentStatus::InfoHash>("info_hash", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        InstanceMethod<&TorrentStatus::Name>("name", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
    });

    m_ctor = new Napi::FunctionReference();
    *m_ctor = Napi::Persistent(func);

    env.SetInstanceData<Napi::FunctionReference>(m_ctor);

    return exports;
}

Napi::Value TorrentStatus::New(Napi::Env env, const lt::torrent_status& ts)
{
    if (m_ctor == nullptr)
    {
        Napi::TypeError::New(env, "TorrentStatus::m_ctor not initialized").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    return m_ctor->New({
        Napi::External<lt::torrent_status>::New(env, new lt::torrent_status(ts))
    });
}

TorrentStatus::TorrentStatus(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<TorrentStatus>(info)
{
    m_status = std::unique_ptr<lt::torrent_status>(
        info[0].As<Napi::External<lt::torrent_status>>().Data());
}

TorrentStatus::~TorrentStatus() = default;

Napi::Value TorrentStatus::InfoHash(const Napi::CallbackInfo &info)
{
    auto hash = Napi::Array::New(info.Env(), 2);
    hash.Set(uint32_t(0), info.Env().Null());
    hash.Set(uint32_t(1), info.Env().Null());

    if (m_status->info_hashes.has_v1())
    {
        std::stringstream ss;
        ss << m_status->info_hashes.v1;
        hash.Set(uint32_t(0), Napi::String::New(info.Env(), ss.str()));
    }

    if (m_status->info_hashes.has_v2())
    {
        std::stringstream ss;
        ss << m_status->info_hashes.v2;
        hash.Set(uint32_t(1), Napi::String::New(info.Env(), ss.str()));
    }

    return hash;
}

Napi::Value TorrentStatus::Name(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_status->name);
}
