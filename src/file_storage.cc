#include "file_storage.h"

#include <libtorrent/torrent_info.hpp>
#include <sstream>

#include "common.h"

namespace lt = libtorrent;
using porla::FileStorage;

Napi::FunctionReference FileStorage::constructor;

Napi::Object FileStorage::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "FileStorage", {
        InstanceMethod("file_absolute_path", &FileStorage::FileAbsolutePath),
        InstanceMethod("file_flags", &FileStorage::FileFlags),
        InstanceMethod("file_name", &FileStorage::FileName),
        InstanceMethod("file_offset", &FileStorage::FileOffset),
        InstanceMethod("file_path", &FileStorage::FilePath),
        InstanceMethod("file_path_hash", &FileStorage::FilePathHash),
        InstanceMethod("file_size", &FileStorage::FileSize)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return exports;
}

Napi::Object FileStorage::NewInstance(Napi::Value arg)
{
    return constructor.New({ arg });
}

FileStorage::FileStorage(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<FileStorage>(info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
    }

    auto ext = info[0].As<Napi::External<lt::file_storage>>();
    fs_ = std::make_unique<lt::file_storage>(*ext.Data());
}

Napi::Value FileStorage::FileAbsolutePath(const Napi::CallbackInfo& info)
{
    auto idx = static_cast<lt::file_index_t>(info[0].As<Napi::Number>().Uint32Value());
    return Napi::Boolean::New(info.Env(), fs_->file_absolute_path(idx));
}

Napi::Value FileStorage::FileFlags(const Napi::CallbackInfo& info)
{
    auto idx = static_cast<lt::file_index_t>(info[0].As<Napi::Number>().Uint32Value());
    return Napi::Number::New(info.Env(), static_cast<uint8_t>(fs_->file_flags(idx)));
}

Napi::Value FileStorage::FileName(const Napi::CallbackInfo& info)
{
    auto idx = static_cast<lt::file_index_t>(info[0].As<Napi::Number>().Uint32Value());
    return Napi::String::New(info.Env(), fs_->file_name(idx).to_string());
}

Napi::Value FileStorage::FileOffset(const Napi::CallbackInfo& info)
{
    auto idx = lt::file_index_t{ info[0].As<Napi::Number>().Int32Value() };

    napi_value res;
    napi_create_int64(info.Env(), fs_->file_offset(idx), &res);

    return Napi::Value(info.Env(), res);
}

Napi::Value FileStorage::FilePath(const Napi::CallbackInfo& info)
{
    auto idx = static_cast<lt::file_index_t>(info[0].As<Napi::Number>().Uint32Value());
    return Napi::String::New(info.Env(), fs_->file_path(idx));
}

Napi::Value FileStorage::FilePathHash(const Napi::CallbackInfo& info)
{
    auto idx = static_cast<lt::file_index_t>(info[0].As<Napi::Number>().Uint32Value());
    auto savePath = info[1].As<Napi::String>().Utf8Value();

    return Napi::Number::New(info.Env(), fs_->file_path_hash(idx, savePath));
}

Napi::Value FileStorage::FileSize(const Napi::CallbackInfo& info)
{
    auto idx = lt::file_index_t{ info[0].As<Napi::Number>().Int32Value() };

    napi_value res;
    napi_create_int64(info.Env(), fs_->file_size(idx), &res);

    return Napi::Value(info.Env(), res);
}
