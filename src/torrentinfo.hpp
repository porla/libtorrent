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

    std::shared_ptr<libtorrent::torrent_info> GetWrapped() { return m_ti; }

private:
    std::shared_ptr<libtorrent::torrent_info> m_ti;
};
