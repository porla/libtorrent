#ifndef PORLA_LIBTORRENT_ADDTORRENTPARAMS_H
#define PORLA_LIBTORRENT_ADDTORRENTPARAMS_H

#include <libtorrent/add_torrent_params.hpp>
#include <napi.h>

namespace porla
{
    class AddTorrentParams : public Napi::ObjectWrap<AddTorrentParams>
    {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Value arg);

        AddTorrentParams(const Napi::CallbackInfo& info);
        libtorrent::add_torrent_params& Wrapped();

    private:
        Napi::Value Get_InfoHash(const Napi::CallbackInfo& info);
        Napi::Value Get_Name(const Napi::CallbackInfo& info);
        Napi::Value Get_SavePath(const Napi::CallbackInfo& info);
        Napi::Value Get_TorrentInfo(const Napi::CallbackInfo& info);
        Napi::Value Get_Trackers(const Napi::CallbackInfo& info);
        void Set_InfoHash(const Napi::CallbackInfo& info, const Napi::Value& value);
        void Set_Name(const Napi::CallbackInfo& info, const Napi::Value& value);
        void Set_SavePath(const Napi::CallbackInfo& info, const Napi::Value& value);
        void Set_TorrentInfo(const Napi::CallbackInfo& info, const Napi::Value& value);
        void Set_Trackers(const Napi::CallbackInfo& info, const Napi::Value& value);

        static Napi::FunctionReference constructor;

        std::unique_ptr<libtorrent::add_torrent_params> p_;
    };
}

#endif
