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
        InstanceMethod<&TorrentHandle::AddPiece>("add_piece"),
        InstanceMethod<&TorrentHandle::AddTracker>("add_tracker"),
        InstanceMethod<&TorrentHandle::ClearError>("clear_error"),
        InstanceMethod<&TorrentHandle::DownloadLimit>("download_limit"),
        InstanceMethod<&TorrentHandle::Flags>("flags"),
        InstanceMethod<&TorrentHandle::FlushCache>("flush_cache"),
        InstanceMethod<&TorrentHandle::ForceRecheck>("force_recheck"),
        InstanceMethod<&TorrentHandle::HavePiece>("have_piece"),
        InstanceMethod<&TorrentHandle::Id>("id"),
        InstanceMethod<&TorrentHandle::InfoHashes>("info_hashes"),
        InstanceMethod<&TorrentHandle::InSession>("in_session"),
        InstanceMethod<&TorrentHandle::IsValid>("is_valid"),
        InstanceMethod<&TorrentHandle::MaxConnections>("max_connections"),
        InstanceMethod<&TorrentHandle::MaxUploads>("max_uploads"),
        InstanceMethod<&TorrentHandle::MoveStorage>("move_storage"),
        InstanceMethod<&TorrentHandle::NeedSaveResumeData>("need_save_resume_data"),
        InstanceMethod<&TorrentHandle::Pause>("pause"),
        InstanceMethod<&TorrentHandle::QueuePosition>("queue_position"),
        InstanceMethod<&TorrentHandle::QueuePositionBottom>("queue_position_bottom"),
        InstanceMethod<&TorrentHandle::QueuePositionDown>("queue_position_down"),
        InstanceMethod<&TorrentHandle::QueuePositionTop>("queue_position_top"),
        InstanceMethod<&TorrentHandle::QueuePositionUp>("queue_position_up"),
        InstanceMethod<&TorrentHandle::ReadPiece>("read_piece"),
        InstanceMethod<&TorrentHandle::RenameFile>("rename_file"),
        InstanceMethod<&TorrentHandle::Resume>("resume"),
        InstanceMethod<&TorrentHandle::SaveResumeData>("save_resume_data"),
        InstanceMethod<&TorrentHandle::SetDownloadLimit>("set_download_limit"),
        InstanceMethod<&TorrentHandle::SetFlags>("set_flags"),
        InstanceMethod<&TorrentHandle::SetMaxConnections>("set_max_connections"),
        InstanceMethod<&TorrentHandle::SetUploadLimit>("set_upload_limit"),
        InstanceMethod<&TorrentHandle::Status>("status"),
        InstanceMethod<&TorrentHandle::Trackers>("trackers"),
        InstanceMethod<&TorrentHandle::UnsetFlags>("unset_flags"),
        InstanceMethod<&TorrentHandle::UploadLimit>("upload_limit"),
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

Napi::Value TorrentHandle::AddPiece(const Napi::CallbackInfo &info)
{
    auto buf = info[1].As<Napi::Buffer<char>>();

    // TODO: validation

    m_handle->add_piece(
        lt::piece_index_t{info[0].ToNumber()},
        std::vector<char>(buf.Data(), buf.Data() + buf.Length()));

    return info.Env().Undefined();
}

void TorrentHandle::AddTracker(const Napi::CallbackInfo &info)
{
    // TODO: support source,trackerid,fail_limit

    if (info.Length() > 0 && info[0].IsObject())
    {
        auto obj = info[0].ToObject();

        lt::announce_entry entry;

        if (obj.Has("tier"))
        {
            entry.tier = static_cast<std::uint8_t>(
                obj.Get("tier").ToNumber().Int32Value());
        }

        if (obj.Has("url")) { entry.url = obj.Get("url").ToString(); }

        m_handle->add_tracker(entry);

        return;
    }

    throw Napi::Error::New(info.Env(), "Invalid args.");
}

Napi::Value TorrentHandle::ClearError(const Napi::CallbackInfo &info)
{
    m_handle->clear_error();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::DownloadLimit(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_handle->download_limit());
}

Napi::Value TorrentHandle::Flags(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), static_cast<uint64_t>(m_handle->flags()));
}

void TorrentHandle::FlushCache(const Napi::CallbackInfo &info)
{
    m_handle->flush_cache();
}

void TorrentHandle::ForceRecheck(const Napi::CallbackInfo &info)
{
    m_handle->force_recheck();
}

Napi::Value TorrentHandle::HavePiece(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(
        info.Env(),
        m_handle->have_piece(
            lt::piece_index_t{ info[0].ToNumber() }));
}

Napi::Value TorrentHandle::Id(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_handle->id());
}

Napi::Value TorrentHandle::InfoHashes(const Napi::CallbackInfo &info)
{
    return InfoHash::New(info.Env(), m_handle->info_hashes());
}

Napi::Value TorrentHandle::InSession(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_handle->in_session());
}

Napi::Value TorrentHandle::IsValid(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), m_handle->is_valid());
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

void TorrentHandle::QueuePositionBottom(const Napi::CallbackInfo &info)
{
    m_handle->queue_position_bottom();
}

void TorrentHandle::QueuePositionDown(const Napi::CallbackInfo &info)
{
    m_handle->queue_position_down();
}

void TorrentHandle::QueuePositionTop(const Napi::CallbackInfo &info)
{
    m_handle->queue_position_top();
}

void TorrentHandle::QueuePositionUp(const Napi::CallbackInfo &info)
{
    m_handle->queue_position_up();
}

Napi::Value TorrentHandle::ReadPiece(const Napi::CallbackInfo &info)
{
    m_handle->read_piece(
        lt::piece_index_t{ info[0].ToNumber() });
    return info.Env().Undefined();
}

void TorrentHandle::RenameFile(const Napi::CallbackInfo &info)
{
    m_handle->rename_file(
        lt::file_index_t{ info[0].ToNumber() },
        info[1].ToString());
}

Napi::Value TorrentHandle::Resume(const Napi::CallbackInfo &info)
{
    m_handle->resume();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SaveResumeData(const Napi::CallbackInfo &info)
{
    auto flags = lt::resume_data_flags_t{};

    if (info[0].IsNumber())
    {
        flags = static_cast<lt::resume_data_flags_t>(info[0].ToNumber().Uint32Value());
    }

    m_handle->save_resume_data(flags);

    return info.Env().Undefined();
}

void TorrentHandle::SetDownloadLimit(const Napi::CallbackInfo &info)
{
    m_handle->set_download_limit(info[0].ToNumber());
}

void TorrentHandle::SetFlags(const Napi::CallbackInfo &info)
{
    switch (info.Length())
    {
    case 1:
        m_handle->set_flags(
            static_cast<lt::torrent_flags_t>(
                info[0].ToNumber().Int64Value()));
        break;
    }
}

void TorrentHandle::SetMaxConnections(const Napi::CallbackInfo &info)
{
    m_handle->set_max_connections(info[0].ToNumber());
}

void TorrentHandle::SetUploadLimit(const Napi::CallbackInfo &info)
{
    m_handle->set_upload_limit(info[0].ToNumber());
}

Napi::Value TorrentHandle::Status(const Napi::CallbackInfo &info)
{
    // TODO: status flags
    return TorrentStatus::New(info.Env(), m_handle->status());
}

Napi::Value TorrentHandle::Trackers(const Napi::CallbackInfo &info)
{
    auto trackers = m_handle->trackers();
    auto arr = Napi::Array::New(info.Env(), trackers.size());

    for (int i = 0; i < trackers.size(); ++i)
    {
        auto entry = Napi::Object::New(info.Env());
        entry["fail_limit"] = trackers.at(i).fail_limit;
        entry["source"] = trackers.at(i).source;
        entry["tier"] = trackers.at(i).tier;
        entry["trackerid"] = trackers.at(i).trackerid;
        entry["url"] = trackers.at(i).url;
        entry["verified"] = trackers.at(i).verified;

        auto endpoints = Napi::Array::New(info.Env(), trackers.at(i).endpoints.size());

        for (int j = 0; j < trackers.at(i).endpoints.size(); j++)
        {
            auto endpoint = Napi::Object::New(info.Env());
            endpoint["enabled"] = trackers.at(i).endpoints.at(j).enabled;

            auto lep = Napi::Array::New(info.Env(), 2);
            lep.Set(uint32_t(0), Napi::String::New(info.Env(), trackers.at(i).endpoints.at(j).local_endpoint.address().to_string()));
            lep.Set(uint32_t(1), Napi::Number::New(info.Env(), trackers.at(i).endpoints.at(j).local_endpoint.port()));

            auto hashes = Napi::Array::New(info.Env(), 2);

            // TODO: hashes

            endpoint["info_hashes"] = hashes;
            endpoint["local_endpoint"] = lep;

            endpoints.Set(j, endpoint);
        }

        entry["endpoints"] = endpoints;

        arr.Set(i, entry);
    }

    return arr;
}

void TorrentHandle::UnsetFlags(const Napi::CallbackInfo &info)
{
    m_handle->unset_flags(
        static_cast<lt::torrent_flags_t>(
            info[0].ToNumber().Int64Value()));
}

Napi::Value TorrentHandle::UploadLimit(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), m_handle->upload_limit());
}
