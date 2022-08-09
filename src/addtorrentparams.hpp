#pragma once

#include <memory>

#include <libtorrent/add_torrent_params.hpp>
#include <napi.h>

class AddTorrentParams : public Napi::ObjectWrap<AddTorrentParams>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Value New(Napi::Env env, const libtorrent::add_torrent_params& params);

    explicit AddTorrentParams(const Napi::CallbackInfo& info);
    ~AddTorrentParams() override;

    explicit operator libtorrent::add_torrent_params() { return *m_params; }

private:
    Napi::Value GetInfoHashes(const Napi::CallbackInfo& info);
    Napi::Value GetName(const Napi::CallbackInfo& info);
    Napi::Value GetSavePath(const Napi::CallbackInfo& info);
    Napi::Value GetTorrentInfo(const Napi::CallbackInfo& info);

    void SetInfoHashes(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetName(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetSavePath(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetTorrentInfo(const Napi::CallbackInfo& info, const Napi::Value& value);

    std::unique_ptr<libtorrent::add_torrent_params> m_params;

    static Napi::FunctionReference* m_ctor;
};
