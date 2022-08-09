#pragma once

#include <memory>

#include <libtorrent/fwd.hpp>
#include <napi.h>

class TorrentInfo : public Napi::ObjectWrap<TorrentInfo>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);

    explicit TorrentInfo(const Napi::CallbackInfo& info);
    ~TorrentInfo() override;

    explicit operator std::shared_ptr<libtorrent::torrent_info>() { return m_ti; }

private:
    Napi::Value InfoHashes(const Napi::CallbackInfo& info);
    Napi::Value Name(const Napi::CallbackInfo& info);
    Napi::Value V1(const Napi::CallbackInfo& info);

    std::shared_ptr<libtorrent::torrent_info> m_ti;
};
