#include "torrentinfo.hpp"

#include <libtorrent/torrent_info.hpp>

namespace lt = libtorrent;

Napi::Object TorrentInfo::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "TorrentInfo", {
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
