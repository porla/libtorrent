#include "add_torrent_params.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_info.hpp>

#include "common.h"
#include "torrent_info.h"

#if !defined(WIN32) && __cplusplus <= 201103
    #include "_aux/std_make_unique.h"
#endif

using porla::AddTorrentParams;

Napi::FunctionReference AddTorrentParams::constructor;

Napi::Object AddTorrentParams::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "AddTorrentParams",
    {
        InstanceAccessor("save_path", &AddTorrentParams::Get_SavePath, &AddTorrentParams::Set_SavePath),
        InstanceAccessor("ti", &AddTorrentParams::Get_TorrentInfo, &AddTorrentParams::Set_TorrentInfo),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("add_torrent_params", func);

    return exports;
}

Napi::Object AddTorrentParams::NewInstance(Napi::Value arg)
{
    return constructor.New({ arg });
}

AddTorrentParams::AddTorrentParams(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<AddTorrentParams>(info)
{
    if (info.Length() > 0)
    {
        auto val = info[0].As<Napi::External<lt::add_torrent_params>>();
        p_ = std::make_unique<lt::add_torrent_params>(*val.Data());
    }
    else
    {
        p_ = std::make_unique<lt::add_torrent_params>();
    }
}

libtorrent::add_torrent_params& AddTorrentParams::Wrapped()
{
    return *p_.get();
}

Napi::Value AddTorrentParams::Get_SavePath(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), p_->save_path);
}

Napi::Value AddTorrentParams::Get_TorrentInfo(const Napi::CallbackInfo& info)
{
    auto arg = Napi::External<std::shared_ptr<lt::torrent_info>>::New(info.Env(), &p_->ti);
    return TorrentInfo::NewInstance(arg);
}

void AddTorrentParams::Set_SavePath(const Napi::CallbackInfo& info, const Napi::Value& value)
{
    p_->save_path = value.As<Napi::String>();
}

void AddTorrentParams::Set_TorrentInfo(const Napi::CallbackInfo& info, const Napi::Value& value)
{
    TorrentInfo* ti = Napi::ObjectWrap<TorrentInfo>::Unwrap(value.As<Napi::Object>());
    p_->ti = ti->Wrapped();
}
