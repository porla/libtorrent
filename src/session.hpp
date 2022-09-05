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
    void AddDhtNode(const Napi::CallbackInfo& info);
    void AddTorrent(const Napi::CallbackInfo& info);
    void ApplySettings(const Napi::CallbackInfo& info);
    Napi::Value IsDhtRunning(const Napi::CallbackInfo& info);
    Napi::Value IsListening(const Napi::CallbackInfo& info);
    Napi::Value IsPaused(const Napi::CallbackInfo& info);
    Napi::Value IsValid(const Napi::CallbackInfo& info);
    Napi::Value ListenPort(const Napi::CallbackInfo& info);
    void Pause(const Napi::CallbackInfo& info);
    void PostDhtStats(const Napi::CallbackInfo& info);
    void PostSessionStats(const Napi::CallbackInfo& info);
    void PostTorrentUpdates(const Napi::CallbackInfo& info);
    void RemoveTorrent(const Napi::CallbackInfo& info);
    void Resume(const Napi::CallbackInfo& info);
    Napi::Value SessionState(const Napi::CallbackInfo& info);
    Napi::Value SslListenPort(const Napi::CallbackInfo& info);

    void AlertNotify(const Napi::CallbackInfo& info);

    std::unique_ptr<libtorrent::session> m_session;

    Napi::ThreadSafeFunction m_tsfn;
};
