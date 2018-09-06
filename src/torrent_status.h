#ifndef PORLA_LIBTORRENT_TORRENTSTATUS_H
#define PORLA_LIBTORRENT_TORRENTSTATUS_H

#include <memory>
#include <node_api.h>

// Seems unpossible to forward declare this
#include <libtorrent/torrent_status.hpp>

namespace porla
{
    class TorrentStatus
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);
        static napi_value New(napi_env env, napi_callback_info callback_info);

        static napi_ref constructor;

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);

        static napi_value Get_ActiveTime(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_AddedTime(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_AllTimeDownload(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_AllTimeUpload(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_AnnouncingToDht(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_AnnouncingToLsd(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_AnnouncingToTrackers(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_BlockSize(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_CompletedTime(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_ConnectCandidates(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_ConnectionsLimit(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_CurrentTracker(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_DistributedCopies(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_DownBandwidthQueue(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_DownloadPayloadRate(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_DownloadRate(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_Errc(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_ErrorFile(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_FinishedDuration(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_Flags(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_Handle(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_HasIncoming(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_HasMetadata(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_InfoHash(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_IsFinished(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_IsSeeding(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_LastDownload(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_LastSeenComplete(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_LastUpload(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_ListPeers(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_ListSeeds(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_MovingStorage(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_Name(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NeedSaveResume(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NextAnnounce(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NumComplete(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NumConnections(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NumIncomplete(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NumPeers(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NumPieces(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NumSeeds(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_NumUploads(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_Progress(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_QueuePosition(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_SavePath(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_SeedRank(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_SeedingDuration(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_State(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_StorageMode(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_Total(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalDone(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalDownload(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalFailedBytes(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalPayloadDownload(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalPayloadUpload(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalRedundantBytes(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalUpload(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalWanted(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_TotalWantedDone(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_UpBandwidthQueue(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_UploadPayloadRate(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_UploadRate(napi_env env, napi_callback_info cbinfo);
        static napi_value Get_UploadsLimit(napi_env env, napi_callback_info cbinfo);

        TorrentStatus(napi_env env, libtorrent::torrent_status const& ts);

        napi_env env_;
        napi_ref wrapper_;

        std::unique_ptr<libtorrent::torrent_status> ts_;
    };
}

#endif
