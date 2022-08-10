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

    explicit operator libtorrent::torrent_handle();

private:
    Napi::Value AddPiece(const Napi::CallbackInfo& info);
    void AddTracker(const Napi::CallbackInfo& info);
    Napi::Value ClearError(const Napi::CallbackInfo& info);
    Napi::Value DownloadLimit(const Napi::CallbackInfo& info);
    void FlushCache(const Napi::CallbackInfo& info);
    void ForceRecheck(const Napi::CallbackInfo& info);
    Napi::Value HavePiece(const Napi::CallbackInfo& info);
    Napi::Value Id(const Napi::CallbackInfo& info);
    Napi::Value InfoHashes(const Napi::CallbackInfo& info);
    Napi::Value InSession(const Napi::CallbackInfo& info);
    Napi::Value IsValid(const Napi::CallbackInfo& info);
    Napi::Value MaxConnections(const Napi::CallbackInfo& info);
    Napi::Value MaxUploads(const Napi::CallbackInfo& info);
    Napi::Value MoveStorage(const Napi::CallbackInfo& info);
    Napi::Value NeedSaveResumeData(const Napi::CallbackInfo& info);
    Napi::Value Pause(const Napi::CallbackInfo& info);
    Napi::Value QueuePosition(const Napi::CallbackInfo& info);
    void QueuePositionBottom(const Napi::CallbackInfo& info);
    void QueuePositionDown(const Napi::CallbackInfo& info);
    void QueuePositionTop(const Napi::CallbackInfo& info);
    void QueuePositionUp(const Napi::CallbackInfo& info);
    Napi::Value ReadPiece(const Napi::CallbackInfo& info);
    void RenameFile(const Napi::CallbackInfo& info);
    Napi::Value Resume(const Napi::CallbackInfo& info);
    Napi::Value SaveResumeData(const Napi::CallbackInfo& info);
    void SetDownloadLimit(const Napi::CallbackInfo& info);
    void SetMaxConnections(const Napi::CallbackInfo& info);
    void SetUploadLimit(const Napi::CallbackInfo& info);
    Napi::Value Status(const Napi::CallbackInfo& info);
    Napi::Value Trackers(const Napi::CallbackInfo& info);
    Napi::Value UploadLimit(const Napi::CallbackInfo& info);

    std::unique_ptr<libtorrent::torrent_handle> m_handle;

    static Napi::FunctionReference* m_ctor;
};
