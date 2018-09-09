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

        std::shared_ptr<libtorrent::torrent_info> ti_;
    };
}

#endif
