#pragma once

#include <map>
#include <memory>
#include <vector>

#include <libtorrent/fwd.hpp>
#include <libtorrent/torrent_status.hpp>
#include <napi.h>

namespace libtorrent { class session; }

class Session : public Napi::ObjectWrap<Session>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);

    explicit Session(const Napi::CallbackInfo& info);
    ~Session() override;

private:
    Napi::Value AddDhtNode(const Napi::CallbackInfo& info);
    Napi::Value AddTorrent(const Napi::CallbackInfo& info);
    Napi::Value IsDhtRunning(const Napi::CallbackInfo& info);
    Napi::Value IsListening(const Napi::CallbackInfo& info);
    Napi::Value IsPaused(const Napi::CallbackInfo& info);
    Napi::Value IsValid(const Napi::CallbackInfo& info);
    Napi::Value LoadTorrent(const Napi::CallbackInfo& info);
    Napi::Value ListenPort(const Napi::CallbackInfo& info);
    Napi::Value Pause(const Napi::CallbackInfo& info);
    Napi::Value PostDhtStats(const Napi::CallbackInfo& info);
    Napi::Value PostSessionStats(const Napi::CallbackInfo& info);
    Napi::Value PostTorrentUpdates(const Napi::CallbackInfo& info);
    Napi::Value Resume(const Napi::CallbackInfo& info);
    Napi::Value SslListenPort(const Napi::CallbackInfo& info);

    Napi::Value AlertNotify(const Napi::CallbackInfo& info);

    std::unique_ptr<libtorrent::session> m_session;
    std::map<libtorrent::info_hash_t, libtorrent::torrent_status> m_torrents;

    std::map<std::string, std::vector<Napi::FunctionReference>> m_callbacks;
    Napi::ObjectReference m_opts;
    Napi::ThreadSafeFunction m_tsfn;
};
