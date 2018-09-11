#ifndef PORLA_LIBTORRENT_TORRENTHANDLE_H
#define PORLA_LIBTORRENT_TORRENTHANDLE_H

#include <memory>
#include <napi.h>

namespace libtorrent
{
    struct torrent_handle;
}

namespace porla
{
    class TorrentHandle : public Napi::ObjectWrap<TorrentHandle>
    {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Value arg);

        TorrentHandle(const Napi::CallbackInfo& info);

        libtorrent::torrent_handle& Wrapped();

    private:
        static Napi::FunctionReference constructor;

        Napi::Value AddHttpSeed(const Napi::CallbackInfo& info);
        Napi::Value AddPiece(const Napi::CallbackInfo& info);
        Napi::Value AddTracker(const Napi::CallbackInfo& info);
        Napi::Value AddUrlSeed(const Napi::CallbackInfo& info);
        Napi::Value ClearError(const Napi::CallbackInfo& info);
        Napi::Value ClearPieceDeadlines(const Napi::CallbackInfo& info);
        Napi::Value ConnectPeer(const Napi::CallbackInfo& info);
        Napi::Value DownloadLimit(const Napi::CallbackInfo& info);
        Napi::Value FilePriority(const Napi::CallbackInfo& info);
        Napi::Value FileProgress(const Napi::CallbackInfo& info);
        Napi::Value FileStatus(const Napi::CallbackInfo& info);
        Napi::Value Flags(const Napi::CallbackInfo& info);
        Napi::Value FlushCache(const Napi::CallbackInfo& info);
        Napi::Value ForceDhtAnnounce(const Napi::CallbackInfo& info);
        Napi::Value ForceReannounce(const Napi::CallbackInfo& info);
        Napi::Value ForceRecheck(const Napi::CallbackInfo& info);
        Napi::Value GetDownloadQueue(const Napi::CallbackInfo& info);
        Napi::Value GetFilePriorities(const Napi::CallbackInfo& info);
        Napi::Value GetPeerInfo(const Napi::CallbackInfo& info);
        Napi::Value GetPiecePriorities(const Napi::CallbackInfo& info);
        Napi::Value HavePiece(const Napi::CallbackInfo& info);
        Napi::Value Id(const Napi::CallbackInfo& info);
        Napi::Value InfoHash(const Napi::CallbackInfo& info);
        Napi::Value IsValid(const Napi::CallbackInfo& info);
        Napi::Value MaxConnections(const Napi::CallbackInfo& info);
        Napi::Value MaxUploads(const Napi::CallbackInfo& info);
        Napi::Value MoveStorage(const Napi::CallbackInfo& info);
        Napi::Value NeedSaveResumeData(const Napi::CallbackInfo& info);
        Napi::Value Pause(const Napi::CallbackInfo& info);
        Napi::Value PieceAvailability(const Napi::CallbackInfo& info);
        Napi::Value PiecePriority(const Napi::CallbackInfo& info);
        Napi::Value PrioritizeFiles(const Napi::CallbackInfo& info);
        Napi::Value PrioritizePieces(const Napi::CallbackInfo& info);
        Napi::Value QueuePosition(const Napi::CallbackInfo& info);
        Napi::Value QueuePositionBottom(const Napi::CallbackInfo& info);
        Napi::Value QueuePositionDown(const Napi::CallbackInfo& info);
        Napi::Value QueuePositionSet(const Napi::CallbackInfo& info);
        Napi::Value QueuePositionTop(const Napi::CallbackInfo& info);
        Napi::Value QueuePositionUp(const Napi::CallbackInfo& info);
        Napi::Value ReadPiece(const Napi::CallbackInfo& info);
        Napi::Value RemoveHttpSeed(const Napi::CallbackInfo& info);
        Napi::Value RemoveUrlSeed(const Napi::CallbackInfo& info);
        Napi::Value RenameFile(const Napi::CallbackInfo& info);
        Napi::Value ReplaceTrackers(const Napi::CallbackInfo& info);
        Napi::Value ResetPieceDeadline(const Napi::CallbackInfo& info);
        Napi::Value Resume(const Napi::CallbackInfo& info);
        Napi::Value SaveResumeData(const Napi::CallbackInfo& info);
        Napi::Value ScrapeTracker(const Napi::CallbackInfo& info);
        Napi::Value SetDownloadLimit(const Napi::CallbackInfo& info);
        Napi::Value SetFlags(const Napi::CallbackInfo& info);
        Napi::Value SetMaxConnections(const Napi::CallbackInfo& info);
        Napi::Value SetMaxUploads(const Napi::CallbackInfo& info);
        Napi::Value SetMetadata(const Napi::CallbackInfo& info);
        Napi::Value SetPieceDeadline(const Napi::CallbackInfo& info);
        Napi::Value SetSslCertificate(const Napi::CallbackInfo& info);
        Napi::Value SetSslCertificateBuffer(const Napi::CallbackInfo& info);
        Napi::Value SetUploadLimit(const Napi::CallbackInfo& info);
        Napi::Value Status(const Napi::CallbackInfo& info);
        Napi::Value TorrentFile(const Napi::CallbackInfo& info);
        Napi::Value Trackers(const Napi::CallbackInfo& info);
        Napi::Value UnsetFlags(const Napi::CallbackInfo& info);
        Napi::Value UploadLimit(const Napi::CallbackInfo& info);
        Napi::Value UrlSeeds(const Napi::CallbackInfo& info);

        std::unique_ptr<libtorrent::torrent_handle> th_;
    };
}

#endif
