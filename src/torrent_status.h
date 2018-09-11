#ifndef PORLA_LIBTORRENT_TORRENTSTATUS_H
#define PORLA_LIBTORRENT_TORRENTSTATUS_H

#include <libtorrent/torrent_status.hpp>
#include <memory>
#include <napi.h>

namespace porla
{
    class TorrentStatus : public Napi::ObjectWrap<TorrentStatus>
    {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Value arg);

        TorrentStatus(const Napi::CallbackInfo& info);

    private:
        static Napi::FunctionReference constructor;

        Napi::Value Get_ActiveTime(const Napi::CallbackInfo& info);
        Napi::Value Get_AddedTime(const Napi::CallbackInfo& info);
        Napi::Value Get_AllTimeDownload(const Napi::CallbackInfo& info);
        Napi::Value Get_AllTimeUpload(const Napi::CallbackInfo& info);
        Napi::Value Get_AnnouncingToDht(const Napi::CallbackInfo& info);
        Napi::Value Get_AnnouncingToLsd(const Napi::CallbackInfo& info);
        Napi::Value Get_AnnouncingToTrackers(const Napi::CallbackInfo& info);
        Napi::Value Get_BlockSize(const Napi::CallbackInfo& info);
        Napi::Value Get_CompletedTime(const Napi::CallbackInfo& info);
        Napi::Value Get_ConnectCandidates(const Napi::CallbackInfo& info);
        Napi::Value Get_ConnectionsLimit(const Napi::CallbackInfo& info);
        Napi::Value Get_CurrentTracker(const Napi::CallbackInfo& info);
        Napi::Value Get_DistributedCopies(const Napi::CallbackInfo& info);
        Napi::Value Get_DownBandwidthQueue(const Napi::CallbackInfo& info);
        Napi::Value Get_DownloadPayloadRate(const Napi::CallbackInfo& info);
        Napi::Value Get_DownloadRate(const Napi::CallbackInfo& info);
        Napi::Value Get_Errc(const Napi::CallbackInfo& info);
        Napi::Value Get_ErrorFile(const Napi::CallbackInfo& info);
        Napi::Value Get_FinishedDuration(const Napi::CallbackInfo& info);
        Napi::Value Get_Flags(const Napi::CallbackInfo& info);
        Napi::Value Get_Handle(const Napi::CallbackInfo& info);
        Napi::Value Get_HasIncoming(const Napi::CallbackInfo& info);
        Napi::Value Get_HasMetadata(const Napi::CallbackInfo& info);
        Napi::Value Get_InfoHash(const Napi::CallbackInfo& info);
        Napi::Value Get_IsFinished(const Napi::CallbackInfo& info);
        Napi::Value Get_IsSeeding(const Napi::CallbackInfo& info);
        Napi::Value Get_LastDownload(const Napi::CallbackInfo& info);
        Napi::Value Get_LastSeenComplete(const Napi::CallbackInfo& info);
        Napi::Value Get_LastUpload(const Napi::CallbackInfo& info);
        Napi::Value Get_ListPeers(const Napi::CallbackInfo& info);
        Napi::Value Get_ListSeeds(const Napi::CallbackInfo& info);
        Napi::Value Get_MovingStorage(const Napi::CallbackInfo& info);
        Napi::Value Get_Name(const Napi::CallbackInfo& info);
        Napi::Value Get_NeedSaveResume(const Napi::CallbackInfo& info);
        Napi::Value Get_NextAnnounce(const Napi::CallbackInfo& info);
        Napi::Value Get_NumComplete(const Napi::CallbackInfo& info);
        Napi::Value Get_NumConnections(const Napi::CallbackInfo& info);
        Napi::Value Get_NumIncomplete(const Napi::CallbackInfo& info);
        Napi::Value Get_NumPeers(const Napi::CallbackInfo& info);
        Napi::Value Get_NumPieces(const Napi::CallbackInfo& info);
        Napi::Value Get_NumSeeds(const Napi::CallbackInfo& info);
        Napi::Value Get_NumUploads(const Napi::CallbackInfo& info);
        Napi::Value Get_Progress(const Napi::CallbackInfo& info);
        Napi::Value Get_QueuePosition(const Napi::CallbackInfo& info);
        Napi::Value Get_SavePath(const Napi::CallbackInfo& info);
        Napi::Value Get_SeedRank(const Napi::CallbackInfo& info);
        Napi::Value Get_SeedingDuration(const Napi::CallbackInfo& info);
        Napi::Value Get_State(const Napi::CallbackInfo& info);
        Napi::Value Get_StorageMode(const Napi::CallbackInfo& info);
        Napi::Value Get_TorrentFile(const Napi::CallbackInfo& info);
        Napi::Value Get_Total(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalDone(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalDownload(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalFailedBytes(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalPayloadDownload(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalPayloadUpload(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalRedundantBytes(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalUpload(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalWanted(const Napi::CallbackInfo& info);
        Napi::Value Get_TotalWantedDone(const Napi::CallbackInfo& info);
        Napi::Value Get_UpBandwidthQueue(const Napi::CallbackInfo& info);
        Napi::Value Get_UploadPayloadRate(const Napi::CallbackInfo& info);
        Napi::Value Get_UploadRate(const Napi::CallbackInfo& info);
        Napi::Value Get_UploadsLimit(const Napi::CallbackInfo& info);

        std::unique_ptr<libtorrent::torrent_status> ts_;
    };
}

#endif
