#pragma once

#include <libtorrent/fwd.hpp>
#include <napi.h>

class TorrentHandle : public Napi::ObjectWrap<TorrentHandle>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Value New(Napi::Env env, const libtorrent::torrent_handle& ts);

    explicit TorrentHandle(const Napi::CallbackInfo& info);
    ~TorrentHandle() override;

private:
    Napi::Value Id(const Napi::CallbackInfo& info);
    Napi::Value InfoHashes(const Napi::CallbackInfo& info);
    Napi::Value MaxConnections(const Napi::CallbackInfo& info);
    Napi::Value MaxUploads(const Napi::CallbackInfo& info);
    Napi::Value MoveStorage(const Napi::CallbackInfo& info);
    Napi::Value NeedSaveResumeData(const Napi::CallbackInfo& info);
    Napi::Value Pause(const Napi::CallbackInfo& info);
    Napi::Value QueuePosition(const Napi::CallbackInfo& info);
    Napi::Value Resume(const Napi::CallbackInfo& info);
    Napi::Value SaveResumeData(const Napi::CallbackInfo& info);
    Napi::Value Status(const Napi::CallbackInfo& info);

    std::unique_ptr<libtorrent::torrent_handle> m_handle;

    static Napi::FunctionReference* m_ctor;
};
