#include "add_torrent_params.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_info.hpp>

#include "common.h"
#include "info_hash.h"
#include "torrent_info.h"

using porla::AddTorrentParams;

Napi::FunctionReference AddTorrentParams::constructor;

Napi::Object AddTorrentParams::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "AddTorrentParams",
    {
        InstanceAccessor("info_hash", &AddTorrentParams::Get_InfoHash, &AddTorrentParams::Set_InfoHash),
        InstanceAccessor("name", &AddTorrentParams::Get_Name, &AddTorrentParams::Set_Name),
        InstanceAccessor("save_path", &AddTorrentParams::Get_SavePath, &AddTorrentParams::Set_SavePath),
        InstanceAccessor("ti", &AddTorrentParams::Get_TorrentInfo, &AddTorrentParams::Set_TorrentInfo),
        InstanceAccessor("trackers", &AddTorrentParams::Get_Trackers, &AddTorrentParams::Set_Trackers),
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

Napi::Value AddTorrentParams::Get_InfoHash(const Napi::CallbackInfo& info)
{
    return InfoHash::ToString(info.Env(), p_->info_hashes);
}

Napi::Value AddTorrentParams::Get_Name(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), p_->name);
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

Napi::Value AddTorrentParams::Get_Trackers(const Napi::CallbackInfo& info)
{
    auto& trackers = p_->trackers;
    auto result = Napi::Array::New(info.Env(), trackers.size());

    for (size_t i = 0; i < trackers.size(); i++)
    {
        result.Set(static_cast<uint32_t>(i), Napi::String::New(info.Env(), trackers.at(i)));
    }

    return result;
}

void AddTorrentParams::Set_InfoHash(const Napi::CallbackInfo& info, const Napi::Value& value)
{
    std::stringstream ss(value.ToString().Utf8Value());
    lt::sha1_hash hash;
    ss >> hash;
    p_->info_hashes = lt::info_hash_t(hash);
}

void AddTorrentParams::Set_Name(const Napi::CallbackInfo& info, const Napi::Value& value)
{
    p_->name = value.As<Napi::String>();
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

void AddTorrentParams::Set_Trackers(const Napi::CallbackInfo& info, const Napi::Value& value)
{
    auto trackers = value.As<Napi::Array>();
    std::vector<std::string> t;

    for (uint32_t i = 0; i < trackers.Length(); i++)
    {
        t.push_back(trackers.Get(i).ToString().Utf8Value());
    }

    p_->trackers = t;
}
