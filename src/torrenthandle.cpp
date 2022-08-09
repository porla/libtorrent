#include "torrenthandle.hpp"

#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_status.hpp>

#include "infohash.hpp"
#include "torrentstatus.hpp"

namespace lt = libtorrent;

Napi::FunctionReference* TorrentHandle::m_ctor = nullptr;

Napi::Object TorrentHandle::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "TorrentHandle", {
        InstanceMethod<&TorrentHandle::Id>("id"),
        InstanceMethod<&TorrentHandle::InfoHashes>("info_hashes"),
        InstanceMethod<&TorrentHandle::MaxConnections>("max_connections"),
        InstanceMethod<&TorrentHandle::MaxUploads>("max_uploads"),
        InstanceMethod<&TorrentHandle::MoveStorage>("move_storage"),
        InstanceMethod<&TorrentHandle::NeedSaveResumeData>("need_save_resume_data"),
        InstanceMethod<&TorrentHandle::Pause>("pause"),
        InstanceMethod<&TorrentHandle::QueuePosition>("queue_position"),
        InstanceMethod<&TorrentHandle::Resume>("resume"),
        InstanceMethod<&TorrentHandle::SaveResumeData>("save_resume_data"),
        InstanceMethod<&TorrentHandle::Status>("status")
    });

    m_ctor = new Napi::FunctionReference();
    *m_ctor = Napi::Persistent(func);

    env.SetInstanceData<Napi::FunctionReference>(m_ctor);

    return exports;
}

Napi::Value TorrentHandle::New(Napi::Env env, const lt::torrent_handle& th)
{
    if (m_ctor == nullptr)
    {
        Napi::TypeError::New(env, "TorrentHandle::m_ctor not initialized").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    return m_ctor->New({
        Napi::External<lt::torrent_handle>::New(env, new lt::torrent_handle(th))
    });
}

TorrentHandle::TorrentHandle(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<TorrentHandle>(info)
{
    m_handle = std::unique_ptr<lt::torrent_handle>(
        info[0].As<Napi::External<lt::torrent_handle>>().Data());
}

TorrentHandle::~TorrentHandle() = default;

TorrentHandle::operator libtorrent::torrent_handle()
{
    return *m_handle;
}

Napi::Value TorrentHandle::Id(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_handle->id());
}

Napi::Value TorrentHandle::InfoHashes(const Napi::CallbackInfo &info)
{
    return InfoHash::New(info.Env(), m_handle->info_hashes());
}

Napi::Value TorrentHandle::MaxConnections(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_handle->max_connections());
}

Napi::Value TorrentHandle::MaxUploads(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_handle->max_uploads());
}

Napi::Value TorrentHandle::MoveStorage(const Napi::CallbackInfo &info)
{
    lt::move_flags_t flags = lt::move_flags_t::always_replace_files;

    if (info.Length() >= 2)
    {
        flags = static_cast<lt::move_flags_t>(info[1].ToNumber().Int32Value());
    }

    m_handle->move_storage(info[0].ToString(), flags);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::NeedSaveResumeData(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_handle->need_save_resume_data());
}

Napi::Value TorrentHandle::Pause(const Napi::CallbackInfo &info)
{
    m_handle->pause(); // TODO: flags
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::QueuePosition(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<int>(m_handle->queue_position()));
}

Napi::Value TorrentHandle::Resume(const Napi::CallbackInfo &info)
{
    m_handle->resume();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SaveResumeData(const Napi::CallbackInfo &info)
{
    // TODO: flags
    m_handle->save_resume_data();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::Status(const Napi::CallbackInfo &info)
{
    // TODO: status flags
    return TorrentStatus::New(info.Env(), m_handle->status());
}
