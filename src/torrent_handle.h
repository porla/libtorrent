#ifndef PORLA_LIBTORRENT_TORRENTHANDLE_H
#define PORLA_LIBTORRENT_TORRENTHANDLE_H

#include <memory>
#include <node_api.h>

namespace libtorrent
{
    struct torrent_handle;
}

namespace porla
{
    class TorrentHandle
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);
        static napi_value New(napi_env env, napi_callback_info callback_info);

        static napi_ref constructor;

        libtorrent::torrent_handle& Wrapped();

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);

        static napi_value AddHttpSeed(napi_env env, napi_callback_info callback_info);
        static napi_value AddPiece(napi_env env, napi_callback_info callback_info);
        static napi_value AddTracker(napi_env env, napi_callback_info callback_info);
        static napi_value AddUrlSeed(napi_env env, napi_callback_info callback_info);
        static napi_value ClearError(napi_env env, napi_callback_info callback_info);
        static napi_value ClearPieceDeadlines(napi_env env, napi_callback_info callback_info);
        static napi_value ConnectPeer(napi_env env, napi_callback_info callback_info);
        static napi_value DownloadLimit(napi_env env, napi_callback_info callback_info);
        static napi_value FilePriority(napi_env env, napi_callback_info callback_info);
        static napi_value FileProgress(napi_env env, napi_callback_info callback_info);
        static napi_value FileStatus(napi_env env, napi_callback_info callback_info);
        static napi_value Flags(napi_env env, napi_callback_info callback_info);
        static napi_value FlushCache(napi_env env, napi_callback_info callback_info);
        static napi_value ForceDhtAnnounce(napi_env env, napi_callback_info callback_info);
        static napi_value ForceReannounce(napi_env env, napi_callback_info callback_info);
        static napi_value ForceRecheck(napi_env env, napi_callback_info callback_info);
        static napi_value GetDownloadQueue(napi_env env, napi_callback_info callback_info);
        static napi_value GetFilePriorities(napi_env env, napi_callback_info callback_info);
        static napi_value GetPeerInfo(napi_env env, napi_callback_info callback_info);
        static napi_value GetPiecePriorities(napi_env env, napi_callback_info callback_info);
        static napi_value HavePiece(napi_env env, napi_callback_info callback_info);
        static napi_value Id(napi_env env, napi_callback_info callback_info);
        static napi_value InfoHash(napi_env env, napi_callback_info callback_info);
        static napi_value IsValid(napi_env env, napi_callback_info callback_info);
        static napi_value MaxConnections(napi_env env, napi_callback_info callback_info);
        static napi_value MaxUploads(napi_env env, napi_callback_info callback_info);
        static napi_value MoveStorage(napi_env env, napi_callback_info callback_info);
        static napi_value Name(napi_env env, napi_callback_info callback_info);
        static napi_value NeedSaveResumeData(napi_env env, napi_callback_info callback_info);
        static napi_value Pause(napi_env env, napi_callback_info callback_info);
        static napi_value PieceAvailability(napi_env env, napi_callback_info callback_info);
        static napi_value PiecePriority(napi_env env, napi_callback_info callback_info);
        static napi_value PrioritizeFiles(napi_env env, napi_callback_info callback_info);
        static napi_value PrioritizePieces(napi_env env, napi_callback_info callback_info);
        static napi_value QueuePosition(napi_env env, napi_callback_info callback_info);
        static napi_value QueuePositionBottom(napi_env env, napi_callback_info callback_info);
        static napi_value QueuePositionDown(napi_env env, napi_callback_info callback_info);
        static napi_value QueuePositionSet(napi_env env, napi_callback_info callback_info);
        static napi_value QueuePositionTop(napi_env env, napi_callback_info callback_info);
        static napi_value QueuePositionUp(napi_env env, napi_callback_info callback_info);
        static napi_value ReadPiece(napi_env env, napi_callback_info callback_info);
        static napi_value RemoveHttpSeed(napi_env env, napi_callback_info callback_info);
        static napi_value RemoveUrlSeed(napi_env env, napi_callback_info callback_info);
        static napi_value RenameFile(napi_env env, napi_callback_info callback_info);
        static napi_value ReplaceTrackers(napi_env env, napi_callback_info callback_info);
        static napi_value ResetPieceDeadline(napi_env env, napi_callback_info callback_info);
        static napi_value Resume(napi_env env, napi_callback_info callback_info);
        static napi_value SaveResumeData(napi_env env, napi_callback_info callback_info);
        static napi_value ScrapeTracker(napi_env env, napi_callback_info callback_info);
        static napi_value SetDownloadLimit(napi_env env, napi_callback_info callback_info);
        static napi_value SetFlags(napi_env env, napi_callback_info callback_info);
        static napi_value SetMaxConnections(napi_env env, napi_callback_info callback_info);
        static napi_value SetMaxUploads(napi_env env, napi_callback_info callback_info);
        static napi_value SetMetadata(napi_env env, napi_callback_info callback_info);
        static napi_value SetPieceDeadline(napi_env env, napi_callback_info callback_info);
        static napi_value SetSslCertificate(napi_env env, napi_callback_info callback_info);
        static napi_value SetSslCertificateBuffer(napi_env env, napi_callback_info callback_info);
        static napi_value SetUploadLimit(napi_env env, napi_callback_info callback_info);
        static napi_value Status(napi_env env, napi_callback_info callback_info);
        static napi_value TorrentFile(napi_env env, napi_callback_info callback_info);
        static napi_value Trackers(napi_env env, napi_callback_info callback_info);
        static napi_value UnsetFlags(napi_env env, napi_callback_info callback_info);
        static napi_value UploadLimit(napi_env env, napi_callback_info callback_info);
        static napi_value UrlSeeds(napi_env env, napi_callback_info callback_info);

        TorrentHandle(napi_env env, libtorrent::torrent_handle const& th);

        napi_env env_;
        napi_ref wrapper_;

        std::unique_ptr<libtorrent::torrent_handle> th_;
    };
}

#endif
