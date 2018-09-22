#ifndef PORLA_LIBTORRENT_TORRENTINFO_H
#define PORLA_LIBTORRENT_TORRENTINFO_H

#include <memory>
#include <string>

#include <libtorrent/torrent_info.hpp>
#include <napi.h>

namespace porla
{
    class TorrentInfo : public Napi::ObjectWrap<TorrentInfo>
    {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Value arg);

        TorrentInfo(const Napi::CallbackInfo& info);
        std::shared_ptr<libtorrent::torrent_info> Wrapped();

    private:
        static Napi::FunctionReference constructor;

        Napi::Value Comment(const Napi::CallbackInfo& info);
        Napi::Value CreationDate(const Napi::CallbackInfo& info);
        Napi::Value Creator(const Napi::CallbackInfo& info);
        Napi::Value InfoHash(const Napi::CallbackInfo& info);
        Napi::Value Name(const Napi::CallbackInfo& info);
        Napi::Value NumFiles(const Napi::CallbackInfo& info);
        Napi::Value NumPieces(const Napi::CallbackInfo& info);
        Napi::Value PieceLength(const Napi::CallbackInfo& info);
        Napi::Value PieceRange(const Napi::CallbackInfo& info);
        Napi::Value PieceSize(const Napi::CallbackInfo& info);
        Napi::Value Priv(const Napi::CallbackInfo& info);
        Napi::Value SslCert(const Napi::CallbackInfo& info);
        Napi::Value TotalSize(const Napi::CallbackInfo& info);

        std::shared_ptr<libtorrent::torrent_info> ti_;
    };
}

#endif
