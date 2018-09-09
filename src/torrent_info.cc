#include "torrent_info.h"

#include <libtorrent/torrent_info.hpp>

#include "common.h"

namespace lt = libtorrent;
using porla::TorrentInfo;

Napi::FunctionReference TorrentInfo::constructor;

Napi::Object TorrentInfo::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "TorrentInfo", {});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("torrent_info", func);

    return exports;
}

Napi::Object TorrentInfo::NewInstance(Napi::Value arg)
{
    return constructor.New({ arg });
}

TorrentInfo::TorrentInfo(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<TorrentInfo>(info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
    }

    lt::error_code ec;

    if (info[0].IsString())
    {
        auto str = info[0].As<Napi::String>();
        ti_ = std::make_shared<lt::torrent_info>(str, ec);
    }
    else if (info[0].IsExternal())
    {
        auto ext = info[0].As<Napi::External<std::shared_ptr<lt::torrent_info>>>();
        ti_ = *ext.Data();
    }
    else if (info[0].IsBuffer())
    {
        auto buf = info[0].As<Napi::Buffer<char>>();
        ti_ = std::make_shared<lt::torrent_info>(buf.Data(), buf.Length(), ec);
    }

    if (ec)
    {
        Napi::Error::New(info.Env(), ec.message()).ThrowAsJavaScriptException();
    }
}

std::shared_ptr<lt::torrent_info> TorrentInfo::Wrapped()
{
    return ti_;
}
