#include "torrentinfo.hpp"

#include <libtorrent/torrent_info.hpp>

#include "infohash.hpp"

namespace lt = libtorrent;

Napi::Object TorrentInfo::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "TorrentInfo", {
        InstanceMethod<&TorrentInfo::InfoHashes>("info_hashes"),
        InstanceMethod<&TorrentInfo::Name>("name"),
        InstanceMethod<&TorrentInfo::V1>("v1"),
    });

    auto* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    exports.Set("TorrentInfo", func);

    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

TorrentInfo::TorrentInfo(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<TorrentInfo>(info)
{
    if (info.Length() < 1)
    {
        throw Napi::Error::New(info.Env(), "Expected 1 argument.");
    }

    if (info[0].IsString())
    {
        lt::error_code ec;
        m_ti = std::make_shared<lt::torrent_info>(info[0].As<Napi::String>(), ec);

        if (ec)
        {
            throw Napi::Error::New(info.Env(), ec.message());
        }
    }
    else
    {
        throw Napi::Error::New(info.Env(), "Unknown constructor argument. Expected string or buffer.");
    }
}

TorrentInfo::~TorrentInfo() = default;

Napi::Value TorrentInfo::InfoHashes(const Napi::CallbackInfo &info)
{
    return InfoHash::New(info.Env(), m_ti->info_hashes());
}

Napi::Value TorrentInfo::Name(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), m_ti->name());
}

Napi::Value TorrentInfo::V1(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_ti->v1());
}
