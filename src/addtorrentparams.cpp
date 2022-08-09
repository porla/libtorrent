#include "addtorrentparams.hpp"

#include <libtorrent/add_torrent_params.hpp>

#include "infohash.hpp"
#include "torrentinfo.hpp"

namespace lt = libtorrent;

Napi::FunctionReference* AddTorrentParams::m_ctor = nullptr;

Napi::Object AddTorrentParams::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "AddTorrentParams", {
        InstanceAccessor("info_hashes", &AddTorrentParams::GetInfoHashes, &AddTorrentParams::SetInfoHashes),
        InstanceAccessor("name", &AddTorrentParams::GetName, &AddTorrentParams::SetName),
        InstanceAccessor("save_path", &AddTorrentParams::GetSavePath, &AddTorrentParams::SetSavePath),
        InstanceAccessor("ti", &AddTorrentParams::GetTorrentInfo, &AddTorrentParams::SetTorrentInfo),
    });

    m_ctor = new Napi::FunctionReference();
    *m_ctor = Napi::Persistent(func);

    exports.Set("AddTorrentParams", func);

    env.SetInstanceData<Napi::FunctionReference>(m_ctor);

    return exports;
}

Napi::Value AddTorrentParams::New(Napi::Env env, const libtorrent::add_torrent_params &params)
{
    if (m_ctor == nullptr)
    {
        Napi::TypeError::New(env, "AddTorrentParams::m_ctor not initialized").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    return m_ctor->New({
        Napi::External<lt::add_torrent_params>::New(env, new lt::add_torrent_params(params))
    });
}

AddTorrentParams::AddTorrentParams(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<AddTorrentParams>(info)
{
    m_params = std::make_unique<lt::add_torrent_params>();
}

AddTorrentParams::~AddTorrentParams() = default;

Napi::Value AddTorrentParams::GetInfoHashes(const Napi::CallbackInfo &info)
{
    return InfoHash::New(info.Env(), m_params->info_hashes);
}

Napi::Value AddTorrentParams::GetName(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_params->name);
}

Napi::Value AddTorrentParams::GetSavePath(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_params->save_path);
}

Napi::Value AddTorrentParams::GetTorrentInfo(const Napi::CallbackInfo &info)
{
    if (!m_params->ti)
    {
        return info.Env().Null();
    }

    throw Napi::Error::New(info.Env(), "Not implemented");
}

void AddTorrentParams::SetInfoHashes(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    auto hash = InfoHash::Unwrap(value.ToObject());
    m_params->info_hashes = static_cast<lt::info_hash_t>(*hash);
}

void AddTorrentParams::SetName(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->name = value.ToString();
}

void AddTorrentParams::SetSavePath(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    m_params->save_path = value.ToString();
}

void AddTorrentParams::SetTorrentInfo(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    auto ti = TorrentInfo::Unwrap(value.ToObject());
    m_params->ti = static_cast<std::shared_ptr<lt::torrent_info>>(*ti);
}
