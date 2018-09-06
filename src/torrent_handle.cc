#include "torrent_handle.h"

#include <sstream>

#include <libtorrent/announce_entry.hpp>
#include <libtorrent/disk_interface.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_status.hpp>

#include "common.h"
#include "torrent_status.h"

napi_status LOG(napi_env env, napi_value val);

napi_status LOG(napi_env env, const char* msg);

#define SET_STATUS_BOOL(env, obj, property, value) \
        { \
            napi_value v; \
            napi_get_boolean(env, value, &v); \
            napi_set_named_property(env, obj, property, v); \
        }

#define SET_STATUS_DOUBLE(env, obj, property, value) \
        { \
            napi_value v; \
            napi_create_double(env, value, &v); \
            napi_set_named_property(env, obj, property, v); \
        }

#define SET_STATUS_INT32(env, obj, property, value) \
        { \
            napi_value v; \
            napi_create_int32(env, value, &v); \
            napi_set_named_property(env, obj, property, v); \
        }

#define SET_STATUS_UINT32(env, obj, property, value) \
        { \
            napi_value v; \
            napi_create_uint32(env, value, &v); \
            napi_set_named_property(env, obj, property, v); \
        }

#define SET_STATUS_INT64(env, obj, property, value) \
        { \
            napi_value v; \
            napi_create_int64(env, value, &v); \
            napi_set_named_property(env, obj, property, v); \
        }

#define SET_STATUS_STRING(env, obj, property, value) \
        { \
            napi_value v; \
            napi_create_string_utf8(env, value, NAPI_AUTO_LENGTH, &v); \
            napi_set_named_property(env, obj, property, v); \
        }

using porla::TorrentHandle;

napi_ref TorrentHandle::constructor;

TorrentHandle::TorrentHandle(napi_env env, libtorrent::torrent_handle const& th)
    : env_(env),
    wrapper_(nullptr)
{
    th_ = std::make_unique<libtorrent::torrent_handle>(th);
}

libtorrent::torrent_handle& TorrentHandle::Wrapped()
{
    return *th_.get();
}

void TorrentHandle::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<TorrentHandle*>(native_obj);
}

napi_status TorrentHandle::Init(napi_env env, napi_value exports)
{
    std::vector<napi_property_descriptor> properties
    {
        PORLA_METHOD_DESCRIPTOR("add_http_seed", AddHttpSeed),
        PORLA_METHOD_DESCRIPTOR("add_piece", AddPiece),
        PORLA_METHOD_DESCRIPTOR("add_tracker", AddTracker),
        PORLA_METHOD_DESCRIPTOR("add_url_seed", AddUrlSeed),
        PORLA_METHOD_DESCRIPTOR("clear_error", ClearError),
        PORLA_METHOD_DESCRIPTOR("clear_piece_deadlines", ClearPieceDeadlines),
        PORLA_METHOD_DESCRIPTOR("connect_peer", ConnectPeer),
        PORLA_METHOD_DESCRIPTOR("download_limit", DownloadLimit),
        PORLA_METHOD_DESCRIPTOR("file_priority", FilePriority),
        PORLA_METHOD_DESCRIPTOR("file_progress", FileProgress),
        PORLA_METHOD_DESCRIPTOR("file_status", FileStatus),
        PORLA_METHOD_DESCRIPTOR("flags", Flags),
        PORLA_METHOD_DESCRIPTOR("flush_cache", FlushCache),
        PORLA_METHOD_DESCRIPTOR("force_dht_announce", ForceDhtAnnounce),
        PORLA_METHOD_DESCRIPTOR("force_reannounce", ForceReannounce),
        PORLA_METHOD_DESCRIPTOR("force_recheck", ForceRecheck),
        PORLA_METHOD_DESCRIPTOR("get_download_queue", GetDownloadQueue),
        PORLA_METHOD_DESCRIPTOR("get_file_priorities", GetFilePriorities),
        PORLA_METHOD_DESCRIPTOR("get_peer_info", GetPeerInfo),
        PORLA_METHOD_DESCRIPTOR("get_piece_priorities", GetPiecePriorities),
        PORLA_METHOD_DESCRIPTOR("have_piece", HavePiece),
        PORLA_METHOD_DESCRIPTOR("id", Id),
        PORLA_METHOD_DESCRIPTOR("info_hash", InfoHash),
        PORLA_METHOD_DESCRIPTOR("is_valid", IsValid),
        PORLA_METHOD_DESCRIPTOR("max_connections", MaxConnections),
        PORLA_METHOD_DESCRIPTOR("max_uploads", MaxUploads),
        PORLA_METHOD_DESCRIPTOR("move_storage", MoveStorage),
        PORLA_METHOD_DESCRIPTOR("need_save_resume_data", NeedSaveResumeData),
        PORLA_METHOD_DESCRIPTOR("pause", Pause),
        PORLA_METHOD_DESCRIPTOR("piece_availability", PieceAvailability),
        PORLA_METHOD_DESCRIPTOR("piece_priority", PiecePriority),
        PORLA_METHOD_DESCRIPTOR("prioritize_files", PrioritizeFiles),
        PORLA_METHOD_DESCRIPTOR("prioritize_pieces", PrioritizePieces),
        PORLA_METHOD_DESCRIPTOR("queue_position", QueuePosition),
        PORLA_METHOD_DESCRIPTOR("queue_position_bottom", QueuePositionBottom),
        PORLA_METHOD_DESCRIPTOR("queue_position_down", QueuePositionDown),
        PORLA_METHOD_DESCRIPTOR("queue_position_set", QueuePositionSet),
        PORLA_METHOD_DESCRIPTOR("queue_position_top", QueuePositionTop),
        PORLA_METHOD_DESCRIPTOR("queue_position_up", QueuePositionUp),
        PORLA_METHOD_DESCRIPTOR("read_piece", ReadPiece),
        /*PORLA_METHOD_DESCRIPTOR("remove_http_seed", RemoveHttpSeed),
        PORLA_METHOD_DESCRIPTOR("remove_url_seed", RemoveUrlSeed),
        PORLA_METHOD_DESCRIPTOR("rename_file", RenameFile),
        PORLA_METHOD_DESCRIPTOR("replace_trackers", ReplaceTrackers),
        PORLA_METHOD_DESCRIPTOR("reset_piece_deadline", ResetPieceDeadline),*/
        PORLA_METHOD_DESCRIPTOR("resume", Resume),
        PORLA_METHOD_DESCRIPTOR("save_resume_data", SaveResumeData),
        /*PORLA_METHOD_DESCRIPTOR("scrape_tracker", ScrapeTracker),
        PORLA_METHOD_DESCRIPTOR("set_download_limit", SetDownloadLimit),
        PORLA_METHOD_DESCRIPTOR("set_flags", SetFlags),
        PORLA_METHOD_DESCRIPTOR("set_max_connections", SetMaxConnections),
        PORLA_METHOD_DESCRIPTOR("set_max_uploads", SetMaxUploads),
        PORLA_METHOD_DESCRIPTOR("set_metadata", SetMetadata),
        PORLA_METHOD_DESCRIPTOR("set_piece_deadline", SetPieceDeadline),
        PORLA_METHOD_DESCRIPTOR("set_ssl_certificate", SetSslCertificate),
        PORLA_METHOD_DESCRIPTOR("set_ssl_certificate_buffer", SetSslCertificateBuffer),
        PORLA_METHOD_DESCRIPTOR("set_upload_limit", SetUploadLimit),*/
        PORLA_METHOD_DESCRIPTOR("status", Status),
        /*PORLA_METHOD_DESCRIPTOR("torrent_file", TorrentFile),
        PORLA_METHOD_DESCRIPTOR("trackers", Trackers),
        PORLA_METHOD_DESCRIPTOR("unset_flags", UnsetFlags),
        PORLA_METHOD_DESCRIPTOR("upload_limit", UploadLimit),
        PORLA_METHOD_DESCRIPTOR("url_seeds", UrlSeeds)*/
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "TorrentHandle", NAPI_AUTO_LENGTH, New, nullptr, properties.size(), properties.data(), &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    return napi_ok;
}

napi_value TorrentHandle::New(napi_env env, napi_callback_info callback_info)
{
    napi_value target;
    napi_get_new_target(env, callback_info, &target);

    if (target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
        return nullptr;
    }

    size_t argc = 1;
    napi_value args[1];
    napi_value _this;
    NAPI_CALL(env, napi_get_cb_info(env, callback_info, &argc, args, &_this, nullptr));

    libtorrent::torrent_handle* th;
    napi_get_value_external(env, args[0], reinterpret_cast<void**>(&th));

    TorrentHandle* obj = new TorrentHandle(env, *th);
    NAPI_CALL(env, napi_wrap(env, _this, obj, TorrentHandle::Destructor, nullptr, &obj->wrapper_));

    return _this;
}

napi_value TorrentHandle::AddHttpSeed(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Invalid number of arguments");
        return nullptr;
    }

    Value url(env, info.args[0]);

    info.wrap->th_->add_http_seed(url.ToString());

    return nullptr;
}

napi_value TorrentHandle::AddPiece(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 3)
    {
        napi_throw_error(env, nullptr, "Expected 3 arguments");
        return nullptr;
    }

    Value idx(env, info.args[0]);
    Value buf(env, info.args[1]);
    Value flags(env, info.args[2]);

    char* data;
    size_t size;
    napi_get_buffer_info(env, info.args[1], reinterpret_cast<void**>(&data), &size);

    // TODO: segfaults
    info.wrap->th_->add_piece(
        libtorrent::piece_index_t(idx.ToInt32()),
        data,
        libtorrent::add_piece_flags_t(flags.ToInt32()));

    return nullptr;
}

napi_value TorrentHandle::AddTracker(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value obj(env, info.args[0]);
    Value url = obj.GetNamedProperty("url");
    Value tier = obj.GetNamedProperty("tier");

    libtorrent::announce_entry ae;
    ae.url = url.ToString();
    ae.tier = tier.ToInt32();

    info.wrap->th_->add_tracker(ae);

    return nullptr;
}

napi_value TorrentHandle::AddUrlSeed(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value url(env, info.args[0]);

    info.wrap->th_->add_url_seed(url.ToString());

    return nullptr;
}

napi_value TorrentHandle::ClearError(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->clear_error();
    return nullptr;
}

napi_value TorrentHandle::ClearPieceDeadlines(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->clear_piece_deadlines();
    return nullptr;
}

napi_value TorrentHandle::ConnectPeer(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 2)
    {
        napi_throw_error(env, nullptr, "Expected 2 arguments");
        return nullptr;
    }

    Value host(env, info.args[0]);
    Value port(env, info.args[1]);

    auto address = boost::asio::ip::address::from_string(host.ToString());
    auto endpoint = boost::asio::ip::tcp::endpoint(address, port.ToInt32());

    info.wrap->th_->connect_peer(endpoint);

    return nullptr;
}

napi_value TorrentHandle::DownloadLimit(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, info.wrap->th_->download_limit(), &val);

    return val;
}

napi_value TorrentHandle::FilePriority(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    switch (info.args.size())
    {
        case 1:
        {
            Value idx(env, info.args[0]);
            auto prio = info.wrap->th_->file_priority(libtorrent::file_index_t(idx.ToInt32()));

            napi_value val;
            napi_create_int32(env, static_cast<uint8_t>(prio), &val);

            return val;
        }

        case 2:
        {
            Value idx(env, info.args[0]);
            Value prio(env, info.args[1]);

            info.wrap->th_->file_priority(
                libtorrent::file_index_t{ idx.ToInt32() },
                libtorrent::download_priority_t{ static_cast<uint8_t>(prio.ToInt32()) });
            break;
        }

        default:
            napi_throw_error(env, nullptr, "Expected 1 or 2 arguments");
            break;
    }

    return nullptr;
}

napi_value TorrentHandle::FileProgress(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    std::vector<int64_t> progress;
    info.wrap->th_->file_progress(progress);

    napi_value arr;
    napi_create_array_with_length(env, progress.size(), &arr);

    for (size_t i = 0; i < progress.size(); i++)
    {
        napi_value val;
        napi_create_int64(env, progress.at(i), &val);
        napi_set_element(env, arr, i, val);
    }

    return arr;
}

napi_value TorrentHandle::FileStatus(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    auto state = info.wrap->th_->file_status();

    napi_value arr;
    napi_create_array_with_length(env, state.size(), &arr);

    for (size_t i = 0; i < state.size(); i++)
    {
        libtorrent::open_file_state s = state.at(i);

        napi_value obj;
        napi_create_object(env, &obj);

        SET_STATUS_INT32(env, obj, "file_index", static_cast<int32_t>(s.file_index));
        SET_STATUS_INT64(env, obj, "last_use", libtorrent::time_point_cast<libtorrent::milliseconds>(s.last_use).time_since_epoch().count());
        SET_STATUS_INT32(env, obj, "open_mode", static_cast<uint8_t>(s.open_mode));
    }

    return arr;
}

napi_value TorrentHandle::Flags(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    
    napi_value val;
    napi_create_double(env, static_cast<uint64_t>(info.wrap->th_->flags()), &val);

    return val;
}

napi_value TorrentHandle::FlushCache(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->flush_cache();
    return nullptr;
}

napi_value TorrentHandle::ForceDhtAnnounce(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->force_dht_announce();
    return nullptr;
}

napi_value TorrentHandle::ForceReannounce(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    int seconds = 0;
    int trackerIndex = -1;

    if (info.args.size() > 0)
    {
        seconds = Value(env, info.args[0]).ToInt32();
    }

    if (info.args.size() > 1)
    {
        trackerIndex = Value(env, info.args[1]).ToInt32();
    }

    info.wrap->th_->force_reannounce(seconds, trackerIndex);

    return nullptr;
}

napi_value TorrentHandle::ForceRecheck(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->force_recheck();
    return nullptr;
}

napi_value TorrentHandle::GetDownloadQueue(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    std::vector<libtorrent::partial_piece_info> ppi;
    info.wrap->th_->get_download_queue(ppi);

    napi_value arr;
    napi_create_array_with_length(env, ppi.size(), &arr);

    for (size_t i = 0; i < ppi.size(); i++)
    {
        auto& info = ppi.at(i);

        napi_value obj;
        napi_create_object(env, &obj);

        // TODO: blocks
        SET_STATUS_INT32(env, obj, "blocks_in_piece", info.blocks_in_piece);
        SET_STATUS_INT32(env, obj, "finished", info.finished);
        SET_STATUS_INT32(env, obj, "piece_index", static_cast<int32_t>(info.piece_index));
        SET_STATUS_INT32(env, obj, "requested", info.requested);
        SET_STATUS_INT32(env, obj, "writing", info.writing);

        napi_set_element(env, arr, i, obj);
    }

    return nullptr;
}

napi_value TorrentHandle::GetFilePriorities(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    auto prios = info.wrap->th_->get_file_priorities();

    napi_value arr;
    napi_create_array_with_length(env, prios.size(), &arr);

    for (size_t i = 0; i < prios.size(); i++)
    {
        napi_value val;
        napi_create_uint32(env, static_cast<uint8_t>(prios.at(i)), &val);
        napi_set_element(env, arr, i, val);
    }

    return arr;
}

napi_value TorrentHandle::GetPeerInfo(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    std::vector<libtorrent::peer_info> pi;
    info.wrap->th_->get_peer_info(pi);

    napi_value arr;
    napi_create_array_with_length(env, pi.size(), &arr);

    for (size_t i = 0; i < pi.size(); i++)
    {
        auto& p = pi.at(i);
        
        napi_value obj;
        napi_create_object(env, &obj);

        SET_STATUS_INT32(env, obj, "busy_requests", p.busy_requests);
        SET_STATUS_STRING(env, obj, "client", p.client.c_str());
        SET_STATUS_INT32(env, obj, "connection_type", p.connection_type);
        SET_STATUS_INT32(env, obj, "down_speed", p.down_speed);
        SET_STATUS_INT32(env, obj, "download_queue_length", p.download_queue_length);
        SET_STATUS_INT64(env, obj, "download_queue_time", libtorrent::total_seconds(p.download_queue_time));
        SET_STATUS_INT32(env, obj, "download_rate_peak", p.download_rate_peak);
        SET_STATUS_INT32(env, obj, "downloading_block_index", p.downloading_block_index);
        SET_STATUS_INT32(env, obj, "downloading_piece_index", static_cast<int32_t>(p.downloading_piece_index));
        SET_STATUS_INT32(env, obj, "downloading_progress", p.downloading_progress);
        SET_STATUS_INT32(env, obj, "downloading_total", p.downloading_total);
        SET_STATUS_INT32(env, obj, "estimated_reciprocation_rate", p.estimated_reciprocation_rate);
        SET_STATUS_INT32(env, obj, "failcount", p.failcount);
        SET_STATUS_UINT32(env, obj, "flags", static_cast<uint32_t>(p.flags));

        // IP
        napi_value ip_arr;
        napi_create_array_with_length(env, 2, &ip_arr);
        napi_value ip;
        napi_value port;
        napi_create_string_utf8(env, p.ip.address().to_string().c_str(), NAPI_AUTO_LENGTH, &ip);
        napi_create_int32(env, p.ip.port(), &port);
        napi_set_element(env, ip_arr, 0, ip);
        napi_set_element(env, ip_arr, 1, port);
        napi_set_named_property(env, obj, "ip", ip_arr);

        SET_STATUS_INT64(env, obj, "last_active", libtorrent::total_seconds(p.last_active));
        SET_STATUS_INT64(env, obj, "last_request", libtorrent::total_seconds(p.last_request));
        
        // Local endpoint
        napi_value local_endpoint_arr;
        napi_create_array_with_length(env, 2, &local_endpoint_arr);
        napi_value local_ip;
        napi_value local_port;
        napi_create_string_utf8(env, p.local_endpoint.address().to_string().c_str(), NAPI_AUTO_LENGTH, &local_ip);
        napi_create_int32(env, p.local_endpoint.port(), &local_port);
        napi_set_element(env, local_endpoint_arr, 0, local_ip);
        napi_set_element(env, local_endpoint_arr, 1, local_port);
        napi_set_named_property(env, obj, "local_endpoint", local_endpoint_arr);

        SET_STATUS_INT32(env, obj, "num_hashfails", p.num_hashfails);
        SET_STATUS_INT32(env, obj, "num_pieces", p.num_pieces);
        SET_STATUS_INT32(env, obj, "payload_down_speed", p.payload_down_speed);
        SET_STATUS_INT32(env, obj, "payload_up_speed", p.payload_up_speed);
        SET_STATUS_INT32(env, obj, "pending_disk_bytes", p.pending_disk_bytes);
        SET_STATUS_INT32(env, obj, "pending_disk_read_bytes", p.pending_disk_read_bytes);

        std::stringstream ss;
        ss << p.pid;
        SET_STATUS_STRING(env, obj, "pid", ss.str().c_str());

        // TODO: pieces SET_STATUS_INT32(env, obj, "pending_disk_read_bytes", p.pieces);
        SET_STATUS_DOUBLE(env, obj, "progress", p.progress);
        SET_STATUS_INT32(env, obj, "queue_bytes", p.queue_bytes);
        SET_STATUS_UINT32(env, obj, "read_state", static_cast<uint8_t>(p.read_state));
        SET_STATUS_INT32(env, obj, "receive_buffer_size", p.receive_buffer_size);
        SET_STATUS_INT32(env, obj, "receive_buffer_watermark", p.receive_buffer_watermark);
        SET_STATUS_INT32(env, obj, "receive_quota", p.receive_quota);
        SET_STATUS_INT32(env, obj, "request_timeout", p.request_timeout);
        SET_STATUS_INT32(env, obj, "requests_in_buffer", p.requests_in_buffer);
        SET_STATUS_INT32(env, obj, "rtt", p.rtt);
        SET_STATUS_INT32(env, obj, "send_buffer_size", p.send_buffer_size);
        SET_STATUS_INT32(env, obj, "send_quota", p.send_quota);
        SET_STATUS_UINT32(env, obj, "source", static_cast<uint8_t>(p.source));
        SET_STATUS_INT32(env, obj, "target_dl_queue_length", p.target_dl_queue_length);
        SET_STATUS_INT32(env, obj, "timed_out_requests", p.timed_out_requests);
        SET_STATUS_INT64(env, obj, "total_download", p.total_download);
        SET_STATUS_INT64(env, obj, "total_upload", p.total_upload);
        SET_STATUS_INT32(env, obj, "up_speed", p.up_speed);
        SET_STATUS_INT32(env, obj, "upload_queue_length", p.upload_queue_length);
        SET_STATUS_INT32(env, obj, "upload_rate_peak", p.upload_rate_peak);
        SET_STATUS_INT32(env, obj, "used_receive_buffer", p.used_receive_buffer);
        SET_STATUS_INT32(env, obj, "used_send_buffer", p.used_send_buffer);
        SET_STATUS_UINT32(env, obj, "write_state", static_cast<uint8_t>(p.write_state));

        napi_set_element(env, arr, i, obj);
    }

    return arr;
}

napi_value TorrentHandle::GetPiecePriorities(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    auto prios = info.wrap->th_->get_piece_priorities();

    napi_value arr;
    napi_create_array_with_length(env, prios.size(), &arr);

    for (size_t i = 0; i < prios.size(); i++)
    {
        napi_value val;
        napi_create_uint32(env, static_cast<uint8_t>(prios.at(i)), &val);
        napi_set_element(env, arr, i, val);
    }

    return arr;
}

napi_value TorrentHandle::HavePiece(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    libtorrent::piece_index_t idx = static_cast<libtorrent::piece_index_t>(v.ToUInt32());

    napi_value res;
    napi_get_boolean(env, info.wrap->th_->have_piece(idx), &res);

    return res;
}

napi_value TorrentHandle::Id(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    napi_value res;
    napi_create_uint32(env, info.wrap->th_->id(), &res);

    return res;
}

napi_value TorrentHandle::InfoHash(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    std::stringstream ss;
    ss << info.wrap->th_->info_hash();

    napi_value res;
    napi_create_string_utf8(env, ss.str().c_str(), NAPI_AUTO_LENGTH, &res);

    return res;
}

napi_value TorrentHandle::IsValid(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    napi_value res;
    napi_get_boolean(env, info.wrap->th_->is_valid(), &res);

    return res;
}

napi_value TorrentHandle::MaxConnections(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    napi_value res;
    napi_create_int32(env, info.wrap->th_->max_connections(), &res);

    return res;
}

napi_value TorrentHandle::MaxUploads(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    napi_value res;
    napi_create_int32(env, info.wrap->th_->max_uploads(), &res);

    return res;
}

napi_value TorrentHandle::MoveStorage(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    // TODO flags

    Value v(env, info.args[0]);

    info.wrap->th_->move_storage(v.ToString());

    return nullptr;
}

napi_value TorrentHandle::NeedSaveResumeData(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    napi_value res;
    napi_get_boolean(env, info.wrap->th_->need_save_resume_data(), &res);

    return res;
}

napi_value TorrentHandle::Pause(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    // TODO flags
    info.wrap->th_->pause();
    return nullptr;
}

napi_value TorrentHandle::PieceAvailability(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    std::vector<int> avail;
    info.wrap->th_->piece_availability(avail);

    napi_value arr;
    napi_create_array_with_length(env, avail.size(), &arr);

    for (size_t i = 0; i < avail.size(); i++)
    {
        napi_value item;
        napi_create_int32(env, avail.at(i), &item);
        napi_set_element(env, arr, i, item);
    }

    return arr;
}

napi_value TorrentHandle::PiecePriority(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    switch (info.args.size())
    {
        case 1:
        {
            Value idx(env, info.args[0]);
            auto prio = info.wrap->th_->piece_priority(libtorrent::piece_index_t(idx.ToInt32()));

            napi_value val;
            napi_create_int32(env, static_cast<uint8_t>(prio), &val);

            return val;
        }

        case 2:
        {
            Value idx(env, info.args[0]);
            Value prio(env, info.args[1]);

            info.wrap->th_->piece_priority(
                libtorrent::piece_index_t{ idx.ToInt32() },
                libtorrent::download_priority_t{ static_cast<uint8_t>(prio.ToInt32()) });
            break;
        }

        default:
            napi_throw_error(env, nullptr, "Expected 1 or 2 arguments");
            break;
    }

    return nullptr;
}

napi_value TorrentHandle::ReadPiece(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    libtorrent::piece_index_t idx = static_cast<libtorrent::piece_index_t>(v.ToInt32());

    info.wrap->th_->read_piece(idx);

    return nullptr;
}

napi_value TorrentHandle::PrioritizeFiles(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    std::vector<lt::download_priority_t> prio;
    Value v(env, info.args[0]);

    for (uint32_t i = 0; i < v.GetArrayLength(); i++)
    {
        prio.push_back(static_cast<lt::download_priority_t>(v.GetArrayItem(i).ToUInt32()));
    }

    info.wrap->th_->prioritize_files(prio);

    return nullptr;
}

napi_value TorrentHandle::PrioritizePieces(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    std::vector<lt::download_priority_t> prio;
    Value v(env, info.args[0]);

    for (uint32_t i = 0; i < v.GetArrayLength(); i++)
    {
        prio.push_back(static_cast<lt::download_priority_t>(v.GetArrayItem(i).ToUInt32()));
    }

    info.wrap->th_->prioritize_pieces(prio);

    return nullptr;
}

napi_value TorrentHandle::QueuePosition(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    napi_value val;
    napi_create_int32(env, static_cast<int32_t>(info.wrap->th_->queue_position()), &val);

    return val;
}


napi_value TorrentHandle::QueuePositionBottom(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->queue_position_bottom();
    return nullptr;
}

napi_value TorrentHandle::QueuePositionDown(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->queue_position_down();
    return nullptr;
}

napi_value TorrentHandle::QueuePositionSet(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);

    info.wrap->th_->queue_position_set(static_cast<lt::queue_position_t>(v.ToInt32()));

    return nullptr;
}

napi_value TorrentHandle::QueuePositionTop(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->queue_position_top();
    return nullptr;
}

napi_value TorrentHandle::QueuePositionUp(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->queue_position_up();
    return nullptr;
}

napi_value TorrentHandle::Resume(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->resume();
    return nullptr;
}

napi_value TorrentHandle::SaveResumeData(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    info.wrap->th_->save_resume_data();
    return nullptr;
}

napi_value TorrentHandle::Status(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentHandle>(env, cbinfo);
    libtorrent::torrent_status ts = info.wrap->th_->status();

    return WrapExternal<TorrentStatus, libtorrent::torrent_status>(env, &ts);
}
