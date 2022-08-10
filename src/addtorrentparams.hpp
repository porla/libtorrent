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
    Napi::Value GetActiveTime(const Napi::CallbackInfo& info);
    Napi::Value GetAddedTime(const Napi::CallbackInfo& info);
    Napi::Value GetCompletedTime(const Napi::CallbackInfo& info);
    Napi::Value GetDownloadLimit(const Napi::CallbackInfo& info);
    Napi::Value GetFinishedTime(const Napi::CallbackInfo& info);
    Napi::Value GetInfoHashes(const Napi::CallbackInfo& info);
    Napi::Value GetLastSeenComplete(const Napi::CallbackInfo& info);
    Napi::Value GetMaxConnections(const Napi::CallbackInfo& info);
    Napi::Value GetMaxUploads(const Napi::CallbackInfo& info);
    Napi::Value GetName(const Napi::CallbackInfo& info);
    Napi::Value GetNumComplete(const Napi::CallbackInfo& info);
    Napi::Value GetNumDownloaded(const Napi::CallbackInfo& info);
    Napi::Value GetNumIncomplete(const Napi::CallbackInfo& info);
    Napi::Value GetSavePath(const Napi::CallbackInfo& info);
    Napi::Value GetSeedingTime(const Napi::CallbackInfo& info);
    Napi::Value GetTorrentInfo(const Napi::CallbackInfo& info);
    Napi::Value GetTotalDownloaded(const Napi::CallbackInfo& info);
    Napi::Value GetTotalUploaded(const Napi::CallbackInfo& info);
    Napi::Value GetUploadLimit(const Napi::CallbackInfo& info);

    void SetActiveTime(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetAddedTime(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetCompletedTime(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetDownloadLimit(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetFinishedTime(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetInfoHashes(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetLastSeenComplete(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetMaxConnections(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetMaxUploads(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetName(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetNumComplete(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetNumDownloaded(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetNumIncomplete(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetSavePath(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetSeedingTime(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetTorrentInfo(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetTotalDownloaded(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetTotalUploaded(const Napi::CallbackInfo& info, const Napi::Value& value);
    void SetUploadLimit(const Napi::CallbackInfo& info, const Napi::Value& value);

    std::unique_ptr<libtorrent::add_torrent_params> m_params;

    static Napi::FunctionReference* m_ctor;
};
