#ifndef PORLA_LIBTORRENT_FILESTORAGE_H
#define PORLA_LIBTORRENT_FILESTORAGE_H

#include <memory>
#include <string>

#include <libtorrent/file_storage.hpp>
#include <napi.h>

namespace porla
{
    class FileStorage : public Napi::ObjectWrap<FileStorage>
    {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static Napi::Object NewInstance(Napi::Value arg);

        FileStorage(const Napi::CallbackInfo& info);

    private:
        static Napi::FunctionReference constructor;

        Napi::Value FileAbsolutePath(const Napi::CallbackInfo& info);
        Napi::Value FileFlags(const Napi::CallbackInfo& info);
        Napi::Value FileName(const Napi::CallbackInfo& info);
        Napi::Value FileOffset(const Napi::CallbackInfo& info);
        Napi::Value FilePath(const Napi::CallbackInfo& info);
        Napi::Value FilePathHash(const Napi::CallbackInfo& info);
        Napi::Value FileSize(const Napi::CallbackInfo& info);

        std::unique_ptr<libtorrent::file_storage> fs_;
    };
}

#endif
