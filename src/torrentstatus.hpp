#pragma once

#include <memory>

#include <libtorrent/fwd.hpp>
#include <napi.h>

class TorrentStatus : public Napi::ObjectWrap<TorrentStatus>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Value New(Napi::Env env, const libtorrent::torrent_status& ts);

    explicit TorrentStatus(const Napi::CallbackInfo& info);
    ~TorrentStatus() override;

private:
    Napi::Value GetBlockSize(const Napi::CallbackInfo& info);
    Napi::Value GetCurrentTracker(const Napi::CallbackInfo& info);
    Napi::Value GetDownloadPayloadRate(const Napi::CallbackInfo& info);
    Napi::Value GetDownloadRate(const Napi::CallbackInfo& info);
    Napi::Value GetErrorCode(const Napi::CallbackInfo& info);
    Napi::Value GetFlags(const Napi::CallbackInfo& info);
    Napi::Value GetHandle(const Napi::CallbackInfo& info);
    Napi::Value GetHasIncoming(const Napi::CallbackInfo& info);
    Napi::Value GetHasMetadata(const Napi::CallbackInfo& info);
    Napi::Value GetInfoHashes(const Napi::CallbackInfo& info);
    Napi::Value GetIsSeeding(const Napi::CallbackInfo& info);
    Napi::Value GetMovingStorage(const Napi::CallbackInfo& info);
    Napi::Value GetName(const Napi::CallbackInfo& info);
    Napi::Value GetNeedSaveResume(const Napi::CallbackInfo& info);
    Napi::Value GetNextAnnounce(const Napi::CallbackInfo& info);
    Napi::Value GetProgress(const Napi::CallbackInfo& info);
    Napi::Value GetQueuePosition(const Napi::CallbackInfo& info);
    Napi::Value GetSavePath(const Napi::CallbackInfo& info);
    Napi::Value GetState(const Napi::CallbackInfo& info);
    Napi::Value GetTotal(const Napi::CallbackInfo& info);
    Napi::Value GetTotalDone(const Napi::CallbackInfo& info);
    Napi::Value GetTotalDownload(const Napi::CallbackInfo& info);
    Napi::Value GetTotalFailedBytes(const Napi::CallbackInfo& info);
    Napi::Value GetTotalPayloadDownload(const Napi::CallbackInfo& info);
    Napi::Value GetTotalPayloadUpload(const Napi::CallbackInfo& info);
    Napi::Value GetTotalRedundantBytes(const Napi::CallbackInfo& info);
    Napi::Value GetTotalUpload(const Napi::CallbackInfo& info);
    Napi::Value GetTotalWanted(const Napi::CallbackInfo& info);
    Napi::Value GetTotalWantedDone(const Napi::CallbackInfo& info);
    Napi::Value GetUploadPayloadRate(const Napi::CallbackInfo& info);

    std::unique_ptr<libtorrent::torrent_status> m_status;

    static Napi::FunctionReference* m_ctor;
};
