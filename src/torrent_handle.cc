#include "torrent_handle.h"

#include <sstream>

#include <boost/asio/ip/address.hpp>
#include <libtorrent/announce_entry.hpp>
#include <libtorrent/disk_interface.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_status.hpp>

#include "info_hash.h"
#include "torrent_info.h"
#include "torrent_status.h"

using porla::TorrentHandle;

Napi::FunctionReference TorrentHandle::constructor;

Napi::Object TorrentHandle::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "TorrentHandle",
    {
        InstanceMethod("add_http_seed", &TorrentHandle::AddHttpSeed),
        InstanceMethod("add_piece", &TorrentHandle::AddPiece),
        InstanceMethod("add_tracker", &TorrentHandle::AddTracker),
        InstanceMethod("add_url_seed", &TorrentHandle::AddUrlSeed),
        InstanceMethod("clear_error", &TorrentHandle::ClearError),
        InstanceMethod("clear_piece_deadlines", &TorrentHandle::ClearPieceDeadlines),
        InstanceMethod("connect_peer", &TorrentHandle::ConnectPeer),
        InstanceMethod("download_limit", &TorrentHandle::DownloadLimit),
        InstanceMethod("file_priority", &TorrentHandle::FilePriority),
        InstanceMethod("file_progress", &TorrentHandle::FileProgress),
        InstanceMethod("file_status", &TorrentHandle::FileStatus),
        InstanceMethod("flags", &TorrentHandle::Flags),
        InstanceMethod("flush_cache", &TorrentHandle::FlushCache),
        InstanceMethod("force_dht_announce", &TorrentHandle::ForceDhtAnnounce),
        InstanceMethod("force_reannounce", &TorrentHandle::ForceReannounce),
        InstanceMethod("force_recheck", &TorrentHandle::ForceRecheck),
        InstanceMethod("get_download_queue", &TorrentHandle::GetDownloadQueue),
        InstanceMethod("get_file_priorities", &TorrentHandle::GetFilePriorities),
        InstanceMethod("get_peer_info", &TorrentHandle::GetPeerInfo),
        InstanceMethod("get_piece_priorities", &TorrentHandle::GetPiecePriorities),
        InstanceMethod("have_piece", &TorrentHandle::HavePiece),
        InstanceMethod("id", &TorrentHandle::Id),
        InstanceMethod("info_hash", &TorrentHandle::InfoHash),
        InstanceMethod("is_valid", &TorrentHandle::IsValid),
        InstanceMethod("max_connections", &TorrentHandle::MaxConnections),
        InstanceMethod("max_uploads", &TorrentHandle::MaxUploads),
        InstanceMethod("move_storage", &TorrentHandle::MoveStorage),
        InstanceMethod("need_save_resume_data", &TorrentHandle::NeedSaveResumeData),
        InstanceMethod("pause", &TorrentHandle::Pause),
        InstanceMethod("piece_availability", &TorrentHandle::PieceAvailability),
        InstanceMethod("piece_priority", &TorrentHandle::PiecePriority),
        InstanceMethod("prioritize_files", &TorrentHandle::PrioritizeFiles),
        InstanceMethod("prioritize_pieces", &TorrentHandle::PrioritizePieces),
        InstanceMethod("queue_position", &TorrentHandle::QueuePosition),
        InstanceMethod("queue_position_bottom", &TorrentHandle::QueuePositionBottom),
        InstanceMethod("queue_position_down", &TorrentHandle::QueuePositionDown),
        InstanceMethod("queue_position_set", &TorrentHandle::QueuePositionSet),
        InstanceMethod("queue_position_top", &TorrentHandle::QueuePositionTop),
        InstanceMethod("queue_position_up", &TorrentHandle::QueuePositionUp),
        InstanceMethod("read_piece", &TorrentHandle::ReadPiece),
        InstanceMethod("remove_http_seed", &TorrentHandle::RemoveHttpSeed),
        InstanceMethod("remove_url_seed", &TorrentHandle::RemoveUrlSeed),
        InstanceMethod("rename_file", &TorrentHandle::RenameFile),
        InstanceMethod("replace_trackers", &TorrentHandle::ReplaceTrackers),
        InstanceMethod("reset_piece_deadline", &TorrentHandle::ResetPieceDeadline),
        InstanceMethod("resume", &TorrentHandle::Resume),
        InstanceMethod("save_resume_data", &TorrentHandle::SaveResumeData),
        InstanceMethod("scrape_tracker", &TorrentHandle::ScrapeTracker),
        InstanceMethod("set_download_limit", &TorrentHandle::SetDownloadLimit),
        // InstanceMethod("set_flags", SetFlags),
        InstanceMethod("set_max_connections", &TorrentHandle::SetMaxConnections),
        InstanceMethod("set_max_uploads", &TorrentHandle::SetMaxUploads),
        // InstanceMethod("set_metadata", SetMetadata),
        InstanceMethod("set_piece_deadline", &TorrentHandle::SetPieceDeadline),
        InstanceMethod("set_ssl_certificate", &TorrentHandle::SetSslCertificate),
        InstanceMethod("set_ssl_certificate_buffer", &TorrentHandle::SetSslCertificateBuffer),
        InstanceMethod("set_upload_limit", &TorrentHandle::SetUploadLimit),
        InstanceMethod("status", &TorrentHandle::Status),
        InstanceMethod("torrent_file", &TorrentHandle::TorrentFile),
        /*PORLA_METHOD_DESCRIPTOR("trackers", Trackers),
        PORLA_METHOD_DESCRIPTOR("unset_flags", UnsetFlags),*/
        InstanceMethod("upload_limit", &TorrentHandle::UploadLimit),
        // PORLA_METHOD_DESCRIPTOR("url_seeds", UrlSeeds)*/
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return exports;
}

Napi::Object TorrentHandle::NewInstance(Napi::Value arg)
{
    return constructor.New({ arg });
}

TorrentHandle::TorrentHandle(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<TorrentHandle>(info)
{
    if (info.Length() > 0)
    {
        auto val = info[0].As<Napi::External<lt::torrent_handle>>();
        th_ = std::make_unique<lt::torrent_handle>(*val.Data());
    }
    else
    {
        // TODO: throw error
    }
}

libtorrent::torrent_handle& TorrentHandle::Wrapped()
{
    return *th_.get();
}

Napi::Value TorrentHandle::AddHttpSeed(const Napi::CallbackInfo& info)
{
    if (info.Length() != 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    th_->add_http_seed(info[0].As<Napi::String>().Utf8Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::AddPiece(const Napi::CallbackInfo& info)
{
    if (info.Length() != 3)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 3 arguments");
        return info.Env().Undefined();
    }

    // TODO: segfaults
    th_->add_piece(
        libtorrent::piece_index_t(info[0].As<Napi::Number>().Int32Value()),
        info[1].As<Napi::Buffer<char>>().Data(),
        libtorrent::add_piece_flags_t(info[2].As<Napi::Number>().Int32Value()));

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::AddTracker(const Napi::CallbackInfo& info)
{
    if (info.Length() != 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    auto obj = info[0].As<Napi::Object>();

    libtorrent::announce_entry ae;
    ae.url = obj.Get("url").As<Napi::String>().Utf8Value();
    ae.tier = obj.Get("tier").As<Napi::Number>().Int32Value();

    th_->add_tracker(ae);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::AddUrlSeed(const Napi::CallbackInfo& info)
{
    if (info.Length() != 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    th_->add_url_seed(info[0].As<Napi::String>().Utf8Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ClearError(const Napi::CallbackInfo& info)
{
    th_->clear_error();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ClearPieceDeadlines(const Napi::CallbackInfo& info)
{
    th_->clear_piece_deadlines();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ConnectPeer(const Napi::CallbackInfo& info)
{
    if (info.Length() != 2)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 2 arguments");
        return info.Env().Undefined();
    }

    auto address = boost::asio::ip::make_address(info[0].As<Napi::String>().Utf8Value());
    auto endpoint = boost::asio::ip::tcp::endpoint(address, info[0].As<Napi::Number>().Int32Value());

    th_->connect_peer(endpoint);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::DownloadLimit(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), th_->download_limit());
}

Napi::Value TorrentHandle::FilePriority(const Napi::CallbackInfo& info)
{
    switch (info.Length())
    {
        case 1:
        {
            auto idx = lt::file_index_t{ info[0].As<Napi::Number>().Int32Value() };
            auto prio = th_->file_priority(idx);
            return Napi::Number::New(info.Env(), static_cast<uint8_t>(prio));
        }

        case 2:
        {
            auto idx = static_cast<lt::file_index_t>(info[0].As<Napi::Number>().Int32Value());
            auto prio = static_cast<lt::download_priority_t>(info[1].As<Napi::Number>().Int32Value());
            th_->file_priority(idx, prio);
            break;
        }

        default:
            napi_throw_error(info.Env(), nullptr, "Expected 1 or 2 arguments");
            break;
    }

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::FileProgress(const Napi::CallbackInfo& info)
{
    std::vector<int64_t> progress;
    th_->file_progress(progress);

    auto arr = Napi::Array::New(info.Env(), progress.size());

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        napi_value val;
        napi_create_int64(info.Env(), progress.at(i), &val);

        arr.Set(i, Napi::Value(info.Env(), val));
    }

    return arr;
}

Napi::Value TorrentHandle::FileStatus(const Napi::CallbackInfo& info)
{
    auto state = th_->file_status();
    auto arr = Napi::Array::New(info.Env(), state.size());

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        const libtorrent::open_file_state& s = state.at(i);

        napi_value last_use;
        napi_create_int64(info.Env(), lt::time_point_cast<lt::milliseconds>(s.last_use).time_since_epoch().count(), &last_use);

        auto obj = Napi::Object::New(info.Env());
        obj.Set("file_index", Napi::Number::New(info.Env(), static_cast<int32_t>(s.file_index)));
        obj.Set("last_use", Napi::Value(info.Env(), last_use));
        obj.Set("open_mode", Napi::Number::New(info.Env(), static_cast<uint8_t>(s.open_mode)));

        arr.Set(i, obj);
    }

    return arr;
}

Napi::Value TorrentHandle::Flags(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), static_cast<uint64_t>(th_->flags()));
}

Napi::Value TorrentHandle::FlushCache(const Napi::CallbackInfo& info)
{
    th_->flush_cache();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ForceDhtAnnounce(const Napi::CallbackInfo& info)
{
    th_->force_dht_announce();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ForceReannounce(const Napi::CallbackInfo& info)
{
    int seconds = 0;
    int trackerIndex = -1;

    if (info.Length() > 0)
    {
        seconds = info[0].As<Napi::Number>().Int32Value();
    }

    if (info.Length() > 1)
    {
        trackerIndex = info[1].As<Napi::Number>().Int32Value();
    }

    th_->force_reannounce(seconds, trackerIndex);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ForceRecheck(const Napi::CallbackInfo& info)
{
    th_->force_recheck();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::GetDownloadQueue(const Napi::CallbackInfo& info)
{
    std::vector<libtorrent::partial_piece_info> ppi;
    th_->get_download_queue(ppi);

    auto arr = Napi::Array::New(info.Env(), ppi.size());

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        auto& item = ppi.at(i);

        // TODO: blocks

        auto obj = Napi::Object::New(info.Env());
        obj.Set("blocks_in_piece", Napi::Number::New(info.Env(), item.blocks_in_piece));
        obj.Set("finished", Napi::Number::New(info.Env(), item.finished));
        obj.Set("piece_index", Napi::Number::New(info.Env(), static_cast<int32_t>(item.piece_index)));
        obj.Set("requested", Napi::Number::New(info.Env(), item.requested));
        obj.Set("writing", Napi::Number::New(info.Env(), item.writing));

        arr.Set(i, obj);
    }

    return arr;
}

Napi::Value TorrentHandle::GetFilePriorities(const Napi::CallbackInfo& info)
{
    auto prios = th_->get_file_priorities();
    auto arr = Napi::Array::New(info.Env(), prios.size());

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        arr.Set(i, Napi::Number::New(info.Env(), static_cast<uint8_t>(prios.at(i))));
    }

    return arr;
}

Napi::Value TorrentHandle::GetPeerInfo(const Napi::CallbackInfo& info)
{
    std::vector<libtorrent::peer_info> pi;
    th_->get_peer_info(pi);

    auto arr = Napi::Array::New(info.Env(), pi.size());

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        auto& p = pi.at(i);

        napi_value download_queue_time;
        napi_create_int64(info.Env(), lt::total_seconds(p.download_queue_time), &download_queue_time);

        auto obj = Napi::Object::New(info.Env());
        obj.Set("busy_request", Napi::Number::New(info.Env(), p.busy_requests));
        obj.Set("client", Napi::String::New(info.Env(), p.client));
        obj.Set("connection_type", Napi::Number::New(info.Env(), p.connection_type));
        obj.Set("down_speed", Napi::Number::New(info.Env(), p.down_speed));
        obj.Set("download_queue_length", Napi::Number::New(info.Env(), p.download_queue_length));
        obj.Set("download_queue_time", Napi::Value(info.Env(), download_queue_time));
        obj.Set("download_rate_peak", Napi::Number::New(info.Env(), p.download_rate_peak));
        obj.Set("downloading_block_index", Napi::Number::New(info.Env(), p.downloading_block_index));
        obj.Set("downloading_piece_index", Napi::Number::New(info.Env(), static_cast<int32_t>(p.downloading_piece_index)));
        obj.Set("downloading_progress", Napi::Number::New(info.Env(), p.downloading_progress));
        obj.Set("downloading_total", Napi::Number::New(info.Env(), p.downloading_total));
        obj.Set("estimated_reciprocation_rate", Napi::Number::New(info.Env(), p.estimated_reciprocation_rate));
        obj.Set("failcount", Napi::Number::New(info.Env(), p.failcount));
        obj.Set("flags", Napi::Number::New(info.Env(), static_cast<uint32_t>(p.flags)));

        auto ip = Napi::Array::New(info.Env(), 2);
        ip.Set(uint32_t(0), Napi::String::New(info.Env(), p.ip.address().to_string()));
        ip.Set(uint32_t(1), Napi::Number::New(info.Env(), p.ip.port()));

        napi_value last_active;
        napi_create_int64(info.Env(), lt::total_seconds(p.last_active), &last_active);

        napi_value last_request;
        napi_create_int64(info.Env(), lt::total_seconds(p.last_request), &last_request);


        obj.Set("ip", ip);
        obj.Set("last_active", Napi::Value(info.Env(), last_active));
        obj.Set("last_request", Napi::Value(info.Env(), last_request));

        auto local_endpoint = Napi::Array::New(info.Env(), 2);
        local_endpoint.Set(uint32_t(0), Napi::String::New(info.Env(), p.local_endpoint.address().to_string()));
        local_endpoint.Set(uint32_t(1), Napi::Number::New(info.Env(), p.local_endpoint.port()));

        obj.Set("local_endpoint", local_endpoint);
        obj.Set("num_hashfails", Napi::Number::New(info.Env(), p.num_hashfails));
        obj.Set("num_pieces", Napi::Number::New(info.Env(), p.num_pieces));
        obj.Set("payload_down_speed", Napi::Number::New(info.Env(), p.payload_down_speed));
        obj.Set("payload_up_speed", Napi::Number::New(info.Env(), p.payload_up_speed));
        obj.Set("pending_disk_bytes", Napi::Number::New(info.Env(), p.pending_disk_bytes));
        obj.Set("pending_disk_read_bytes", Napi::Number::New(info.Env(), p.pending_disk_read_bytes));

        std::stringstream ss;
        ss << p.pid;

        obj.Set("pid", Napi::String::New(info.Env(), ss.str()));
        // TODO: pieces
        obj.Set("progress", Napi::Number::New(info.Env(), p.progress));
        obj.Set("queue_bytes", Napi::Number::New(info.Env(), p.queue_bytes));
        obj.Set("read_state", Napi::Number::New(info.Env(), static_cast<uint8_t>(p.read_state)));
        obj.Set("receive_buffer_size", Napi::Number::New(info.Env(), p.receive_buffer_size));
        obj.Set("receive_buffer_watermark", Napi::Number::New(info.Env(), p.receive_buffer_watermark));
        obj.Set("receive_quota", Napi::Number::New(info.Env(), p.receive_quota));
        obj.Set("request_timeout", Napi::Number::New(info.Env(), p.request_timeout));
        obj.Set("requests_in_buffer", Napi::Number::New(info.Env(), p.requests_in_buffer));
        obj.Set("rtt", Napi::Number::New(info.Env(), p.rtt));
        obj.Set("send_buffer_size", Napi::Number::New(info.Env(), p.send_buffer_size));
        obj.Set("send_quota", Napi::Number::New(info.Env(), p.send_quota));
        obj.Set("source", Napi::Number::New(info.Env(), static_cast<uint8_t>(p.source)));
        obj.Set("target_dl_queue_length", Napi::Number::New(info.Env(), p.target_dl_queue_length));
        obj.Set("timed_out_requests", Napi::Number::New(info.Env(), p.timed_out_requests));

        napi_value total_download;
        napi_create_int64(info.Env(), p.total_download, &total_download);

        napi_value total_upload;
        napi_create_int64(info.Env(), p.total_upload, &total_upload);

        obj.Set("total_download", Napi::Value(info.Env(), total_download));
        obj.Set("total_upload", Napi::Value(info.Env(), total_upload));
        obj.Set("up_speed", Napi::Number::New(info.Env(), p.up_speed));
        obj.Set("upload_queue_length", Napi::Number::New(info.Env(), p.upload_queue_length));
        obj.Set("upload_rate_peak", Napi::Number::New(info.Env(), p.upload_rate_peak));
        obj.Set("used_receive_buffer", Napi::Number::New(info.Env(), p.used_receive_buffer));
        obj.Set("used_send_buffer", Napi::Number::New(info.Env(), p.used_send_buffer));
        obj.Set("write_state", Napi::Number::New(info.Env(), static_cast<uint8_t>(p.write_state)));

        arr.Set(i, obj);
    }

    return arr;
}

Napi::Value TorrentHandle::GetPiecePriorities(const Napi::CallbackInfo& info)
{
    auto prios = th_->get_piece_priorities();
    auto arr = Napi::Array::New(info.Env(), prios.size());

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        arr.Set(i, Napi::Number::New(info.Env(), static_cast<uint8_t>(prios.at(i))));
    }

    return arr;
}

Napi::Value TorrentHandle::HavePiece(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    auto idx = static_cast<libtorrent::piece_index_t>(info[0].As<Napi::Number>().Int32Value());
    return Napi::Boolean::New(info.Env(), th_->have_piece(idx));
}

Napi::Value TorrentHandle::Id(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), th_->id());
}

Napi::Value TorrentHandle::InfoHash(const Napi::CallbackInfo& info)
{
    return InfoHash::ToString(info.Env(), th_->info_hash());
}

Napi::Value TorrentHandle::IsValid(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), th_->is_valid());
}

Napi::Value TorrentHandle::MaxConnections(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), th_->max_connections());
}

Napi::Value TorrentHandle::MaxUploads(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), th_->max_uploads());
}

Napi::Value TorrentHandle::MoveStorage(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    // TODO flags
    th_->move_storage(info[0].As<Napi::String>().Utf8Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::NeedSaveResumeData(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), th_->need_save_resume_data());
}

Napi::Value TorrentHandle::Pause(const Napi::CallbackInfo& info)
{
    // TODO: flags
    th_->pause();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::PieceAvailability(const Napi::CallbackInfo& info)
{
    std::vector<int> avail;
    th_->piece_availability(avail);

    auto arr = Napi::Array::New(info.Env(), avail.size());

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        arr.Set(i, Napi::Number::New(info.Env(), avail.at(i)));
    }

    return arr;
}

Napi::Value TorrentHandle::PiecePriority(const Napi::CallbackInfo& info)
{
    switch (info.Length())
    {
        case 1:
        {
            auto idx = static_cast<lt::piece_index_t>(info[0].As<Napi::Number>().Int32Value());
            auto prio = th_->piece_priority(idx);
            return Napi::Number::New(info.Env(), static_cast<uint8_t>(prio));
        }

        case 2:
        {
            auto idx = static_cast<lt::piece_index_t>(info[0].As<Napi::Number>().Int32Value());
            auto prio = static_cast<lt::download_priority_t>(info[1].As<Napi::Number>().Int32Value());
            th_->piece_priority(idx, prio);
            break;
        }

        default:
            napi_throw_error(info.Env(), nullptr, "Expected 1 or 2 arguments");
            break;
    }

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ReadPiece(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    auto idx = static_cast<lt::piece_index_t>(info[0].As<Napi::Number>().Int32Value());
    th_->read_piece(idx);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::PrioritizeFiles(const Napi::CallbackInfo& info)
{
    if (info.Length() != 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    auto arr = info[0].As<Napi::Array>();
    std::vector<lt::download_priority_t> prio;

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        prio.push_back(static_cast<lt::download_priority_t>(arr.Get(i).As<Napi::Number>().Int32Value()));
    }

    th_->prioritize_files(prio);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::PrioritizePieces(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    auto arr = info[0].As<Napi::Array>();
    std::vector<lt::download_priority_t> prio;

    for (uint32_t i = 0; i < arr.Length(); i++)
    {
        prio.push_back(static_cast<lt::download_priority_t>(arr.Get(i).As<Napi::Number>().Int32Value()));
    }

    th_->prioritize_pieces(prio);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::QueuePosition(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), static_cast<int32_t>(th_->queue_position()));
}

Napi::Value TorrentHandle::QueuePositionBottom(const Napi::CallbackInfo& info)
{
    th_->queue_position_bottom();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::QueuePositionDown(const Napi::CallbackInfo& info)
{
    th_->queue_position_down();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::QueuePositionSet(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        napi_throw_error(info.Env(), nullptr, "Expected 1 argument");
        return info.Env().Undefined();
    }

    auto pos = static_cast<lt::queue_position_t>(info[0].As<Napi::Number>().Int32Value());
    th_->queue_position_set(pos);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::QueuePositionTop(const Napi::CallbackInfo& info)
{
    th_->queue_position_top();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::QueuePositionUp(const Napi::CallbackInfo& info)
{
    th_->queue_position_up();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::RemoveHttpSeed(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    th_->remove_http_seed(info[0].As<Napi::String>().Utf8Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::RemoveUrlSeed(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    th_->remove_url_seed(info[0].As<Napi::String>().Utf8Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::RenameFile(const Napi::CallbackInfo& info)
{
    if (info.Length() < 2)
    {
        Napi::Error::New(info.Env(), "Expected 2 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    auto idx = static_cast<lt::file_index_t>(info[0].As<Napi::Number>().Int32Value());
    auto name = info[1].As<Napi::String>().Utf8Value();

    th_->rename_file(idx, name);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ReplaceTrackers(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    auto input = info[0].As<Napi::Array>();
    std::vector<lt::announce_entry> trackers;

    for (uint32_t i = 0; i < input.Length(); i++)
    {
        auto val = input.Get(i);

        if (val.IsString())
        {
            lt::announce_entry entry;
            entry.url = val.As<Napi::String>().Utf8Value();

            trackers.push_back(entry);
        }
        else if (val.IsObject())
        {
            auto obj = val.As<Napi::Object>();

            lt::announce_entry entry;
            entry.url = obj.Get("url").As<Napi::String>().Utf8Value();
            entry.tier = static_cast<uint8_t>(obj.Get("tier").As<Napi::Number>().Int32Value());

            trackers.push_back(entry);
        }
    }

    th_->replace_trackers(trackers);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ResetPieceDeadline(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    auto idx = static_cast<lt::piece_index_t>(info[0].As<Napi::Number>().Int32Value());
    th_->reset_piece_deadline(idx);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::Resume(const Napi::CallbackInfo& info)
{
    th_->resume();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SaveResumeData(const Napi::CallbackInfo& info)
{
    // TODO: flags
    th_->save_resume_data();
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::ScrapeTracker(const Napi::CallbackInfo& info)
{
    int idx = -1;

    if (info.Length() > 0)
    {
        idx = info[0].As<Napi::Number>().Int32Value();
    }

    th_->scrape_tracker(idx);
    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SetDownloadLimit(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    th_->set_download_limit(info[0].As<Napi::Number>().Int32Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SetMaxConnections(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    th_->set_max_connections(info[0].As<Napi::Number>().Int32Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SetMaxUploads(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    th_->set_max_uploads(info[0].As<Napi::Number>().Int32Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SetPieceDeadline(const Napi::CallbackInfo& info)
{
    if (info.Length() < 2)
    {
        Napi::Error::New(info.Env(), "Expected 2 arguments").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    auto idx = info[0].As<Napi::Number>().Int32Value();
    auto deadline = info[0].As<Napi::Number>().Int32Value();
    // TODO flags

    th_->set_piece_deadline(
        lt::piece_index_t{idx},
        deadline);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SetSslCertificate(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    auto obj = info[0].As<Napi::Object>();
    std::string passphrase = "";

    if (obj.HasOwnProperty("passphrase"))
    {
        passphrase = obj.Get("passphrase").As<Napi::String>().Utf8Value();
    }

    th_->set_ssl_certificate(
        obj.Get("certificate").As<Napi::String>().Utf8Value(),
        obj.Get("private_key").As<Napi::String>().Utf8Value(),
        obj.Get("dh_params").As<Napi::String>().Utf8Value(),
        passphrase);

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SetSslCertificateBuffer(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    auto obj = info[0].As<Napi::Object>();

    th_->set_ssl_certificate_buffer(
        obj.Get("certificate").As<Napi::String>().Utf8Value(),
        obj.Get("private_key").As<Napi::String>().Utf8Value(),
        obj.Get("dh_params").As<Napi::String>().Utf8Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::SetUploadLimit(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    th_->set_upload_limit(info[0].As<Napi::Number>().Int32Value());

    return info.Env().Undefined();
}

Napi::Value TorrentHandle::Status(const Napi::CallbackInfo& info)
{
    auto ts = th_->status();
    auto arg = Napi::External<lt::torrent_status>::New(info.Env(), &ts);
    return TorrentStatus::NewInstance(arg);
}

Napi::Value TorrentHandle::TorrentFile(const Napi::CallbackInfo& info)
{
    auto ti = th_->torrent_file();
    auto arg = Napi::External<std::shared_ptr<const lt::torrent_info>>::New(info.Env(), &ti);
    return TorrentInfo::NewInstance(arg);
}

Napi::Value TorrentHandle::UploadLimit(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), th_->upload_limit());
}
