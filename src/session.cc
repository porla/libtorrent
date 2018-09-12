#include "session.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/entry.hpp>
#include <libtorrent/ip_filter.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_info.hpp>

#include <napi.h>

#include "add_torrent_params.h"
#include "alert.h"
#include "common.h"
#include "entry.h"
#include "ip_filter.h"
#include "settings_pack.h"
#include "torrent_info.h"
#include "torrent_handle.h"
#include "torrent_status.h"

#if !defined(WIN32) && __cplusplus <= 201103
    #include "_aux/std_make_unique.h"
#endif

using porla::Session;

napi_ref Session::constructor;

napi_status LOG(napi_env env, napi_value val)
{
    napi_value global;
    napi_get_global(env, &global);

    napi_value console;
    napi_get_named_property(env, global, "console", &console);

    napi_value log;
    napi_get_named_property(env, console, "log", &log);

    napi_value args[1];
    args[0] = val;

    return napi_call_function(env, console, log, 1, args, nullptr);
}

napi_status LOG(napi_env env, const char* msg)
{
    napi_value val;
    napi_create_string_utf8(env, msg, NAPI_AUTO_LENGTH, &val);

    return LOG(env, val);
}

Session::Session(napi_env env, libtorrent::settings_pack& settings)
    : env_(env),
    wrapper_(nullptr)
{
    session_ = std::make_unique<libtorrent::session>(settings);
}

void Session::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<Session*>(native_obj);
}

napi_status Session::Init(napi_env env, napi_value exports)
{
    std::vector<napi_property_descriptor> properties
    {
        PORLA_METHOD_DESCRIPTOR("add_dht_node", AddDhtNode),
        PORLA_METHOD_DESCRIPTOR("add_port_mapping", AddPortMapping),
        PORLA_METHOD_DESCRIPTOR("add_torrent", AddTorrent),
        PORLA_METHOD_DESCRIPTOR("apply_settings", ApplySettings),
        PORLA_METHOD_DESCRIPTOR("async_add_torrent", AsyncAddTorrent),
        PORLA_METHOD_DESCRIPTOR("create_peer_class", CreatePeerClass),
        PORLA_METHOD_DESCRIPTOR("delete_peer_class", DeletePeerClass),
        PORLA_METHOD_DESCRIPTOR("delete_port_mapping", DeletePortMapping),
        PORLA_METHOD_DESCRIPTOR("dht_announce", DhtAnnounce),
        PORLA_METHOD_DESCRIPTOR("dht_direct_request", DhtDirectRequest),
        PORLA_METHOD_DESCRIPTOR("dht_get_item", DhtGetItem),
        PORLA_METHOD_DESCRIPTOR("dht_get_peers", DhtGetPeers),
        PORLA_METHOD_DESCRIPTOR("dht_live_nodes", DhtLiveNodes),
        //TODO PORLA_METHOD_DESCRIPTOR("dht_put_item", DhtPutItem),
        //TODO PORLA_METHOD_DESCRIPTOR("dht_sample_infohashes", DhtSampleInfohashes),
        PORLA_METHOD_DESCRIPTOR("find_torrent", FindTorrent),
        PORLA_METHOD_DESCRIPTOR("get_cache_info", GetCacheInfo),
        PORLA_METHOD_DESCRIPTOR("get_dht_settings", GetDhtSettings),
        PORLA_METHOD_DESCRIPTOR("get_ip_filter", GetIpFilter),
        PORLA_METHOD_DESCRIPTOR("get_peer_class", GetPeerClass),
        PORLA_METHOD_DESCRIPTOR("get_peer_class_filter", GetPeerClassFilter),
        PORLA_METHOD_DESCRIPTOR("get_peer_class_type_filter", GetPeerClassTypeFilter),
        PORLA_METHOD_DESCRIPTOR("get_settings", GetSettings),
        PORLA_METHOD_DESCRIPTOR("get_torrent_status", GetTorrentStatus),
        PORLA_METHOD_DESCRIPTOR("get_torrents", GetTorrents),
        PORLA_METHOD_DESCRIPTOR("is_dht_running", IsDhtRunning),
        PORLA_METHOD_DESCRIPTOR("is_listening", IsListening),
        PORLA_METHOD_DESCRIPTOR("is_paused", IsPaused),
        PORLA_METHOD_DESCRIPTOR("is_valid", IsValid),
        PORLA_METHOD_DESCRIPTOR("listen_port", ListenPort),
        PORLA_METHOD_DESCRIPTOR("load_state", LoadState),
        PORLA_METHOD_DESCRIPTOR("pause", Pause),
        PORLA_METHOD_DESCRIPTOR("pop_alerts", PopAlerts),
        PORLA_METHOD_DESCRIPTOR("post_dht_stats", PostDhtStats),
        PORLA_METHOD_DESCRIPTOR("post_session_stats", PostSessionStats),
        PORLA_METHOD_DESCRIPTOR("post_torrent_updates", PostTorrentUpdates),
        /*PORLA_METHOD_DESCRIPTOR("refresh_torrent_status", RefreshTorrentStatus),*/
        PORLA_METHOD_DESCRIPTOR("remove_torrent", RemoveTorrent),
        PORLA_METHOD_DESCRIPTOR("reopen_network_sockets", ReopenNetworkSockets),
        PORLA_METHOD_DESCRIPTOR("resume", Resume),
        PORLA_METHOD_DESCRIPTOR("save_state", SaveState),
        PORLA_METHOD_DESCRIPTOR("save_state_buf", SaveStateBuffer),
        PORLA_METHOD_DESCRIPTOR("set_dht_settings", SetDhtSettings),
        PORLA_METHOD_DESCRIPTOR("set_ip_filter", SetIpFilter),
        PORLA_METHOD_DESCRIPTOR("set_peer_class", SetPeerClass),
        PORLA_METHOD_DESCRIPTOR("set_peer_class_filter", SetPeerClassFilter),
        PORLA_METHOD_DESCRIPTOR("set_peer_class_type_filter", SetPeerClassTypeFilter),
        PORLA_METHOD_DESCRIPTOR("set_port_filter", SetPortFilter),
        PORLA_METHOD_DESCRIPTOR("ssl_listen_port", SslListenPort),
        PORLA_METHOD_DESCRIPTOR("wait_for_alert", WaitForAlert)
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "Session", NAPI_AUTO_LENGTH, New, nullptr, properties.size(), properties.data(), &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env, exports, "session", cons);
    if (status != napi_ok) return status;

    return napi_ok;
}

napi_value Session::New(napi_env env, napi_callback_info cbinfo)
{
    // We don't actually have a Session in this wrap, but
    // lets pretend. DON'T USE IT THOUGH.
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.new_target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
    }

    libtorrent::settings_pack settings;

    if (info.args.size() > 0)
    {
        napi_valuetype type;
        napi_typeof(env, info.args[0], &type);

        if (type != napi_valuetype::napi_object)
        {
            napi_throw_error(env, nullptr, "Expected an Object.");
            return nullptr;
        }

        settings = SettingsPack::Parse(env, info.args[0]);
    }

    Session* obj = new Session(env, settings);
    napi_wrap(env, info.this_arg, obj, Session::Destructor, nullptr, &obj->wrapper_);

    return info.this_arg;
}

napi_value Session::AddDhtNode(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 2)
    {
        napi_throw_error(env, nullptr, "Expected two arguments");
        return nullptr;
    }

    Value host(env, info.args[0]);
    Value port(env, info.args[1]);

    info.wrap->session_->add_dht_node({ host.ToString(), port.ToInt32() });

    return nullptr;
}

napi_value Session::AddPortMapping(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 3)
    {
        napi_throw_error(env, nullptr, "Expected 3 arguments");
        return nullptr;
    }

    Value protocol(env, info.args[0]);
    Value external_port(env, info.args[1]);
    Value local_port(env, info.args[2]);

    auto res = info.wrap->session_->add_port_mapping(
        static_cast<libtorrent::portmap_protocol>(protocol.ToInt32()),
        external_port.ToInt32(),
        local_port.ToInt32());

    napi_value arr;
    napi_create_array_with_length(env, res.size(), &arr);

    for (size_t i = 0; i < res.size(); i++)
    {
        napi_value mapping;
        napi_create_int32(env, static_cast<int32_t>(res.at(i)), &mapping);
        napi_set_element(env, arr, i, mapping);
    }

    return arr;
}

napi_value Session::AddTorrent(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    napi_valuetype type;
    napi_typeof(env, info.args[0], &type);

    if (type != napi_valuetype::napi_object)
    {
        napi_throw_error(env, nullptr, "Expected an [object] argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    auto params = v.Unwrap<AddTorrentParams>();

    libtorrent::error_code ec;
    libtorrent::torrent_handle handle = info.wrap->session_->add_torrent(params->Wrapped(), ec);

    if (ec)
    {
        napi_throw_error(env, nullptr, ec.message().c_str());
        return nullptr;
    }

    auto arg = Napi::External<lt::torrent_handle>::New(env, &handle);
    return TorrentHandle::NewInstance(arg);
}

napi_value Session::ApplySettings(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    auto settings = SettingsPack::Parse(env, info.args[0]);
    info.wrap->session_->apply_settings(settings);

    return nullptr;
}

napi_value Session::AsyncAddTorrent(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    auto params = v.Unwrap<AddTorrentParams>();

    info.wrap->session_->async_add_torrent(params->Wrapped());

    return nullptr;
}

napi_value Session::CreatePeerClass(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value name(env, info.args[0]);
    auto cls = info.wrap->session_->create_peer_class(name.ToString().c_str());

    napi_value ret;
    napi_create_uint32(env, static_cast<uint32_t>(cls), &ret);

    return ret;
}

napi_value Session::DeletePeerClass(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value cls(env, info.args[0]);

    info.wrap->session_->delete_peer_class(
        static_cast<libtorrent::peer_class_t>(cls.ToUInt32()));
    
    return nullptr;
}

napi_value Session::DeletePortMapping(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value mapping(env, info.args[0]);

    info.wrap->session_->delete_port_mapping(
        static_cast<libtorrent::port_mapping_t>(mapping.ToUInt32()));
    
    return nullptr;
}

napi_value Session::DhtAnnounce(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    libtorrent::sha1_hash hash;
    int port = 0;
    libtorrent::dht::announce_flags_t flags { uint8_t('\000') }; 

    if (info.args.size() > 0)
    {
        Value ih(env, info.args[0]);
        std::stringstream ss(ih.ToString());
        ss >> hash;
    }
    else
    {
        napi_throw_error(env, nullptr, "Expected at least 1 argument");
        return nullptr;
    }

    if (info.args.size() > 1)
    {
        Value p(env, info.args[1]);
        port = p.ToInt32();
    }

    if (info.args.size() > 2)
    {
        Value f(env, info.args[2]);
        flags = static_cast<libtorrent::dht::announce_flags_t>(f.ToInt32());
    }

    info.wrap->session_->dht_announce(hash, port, flags);

    return nullptr;
}

napi_value Session::DhtDirectRequest(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    napi_throw_error(env, nullptr, "Not implemented");
    return nullptr;
}

napi_value Session::DhtGetItem(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    std::stringstream ss(v.ToString());
    libtorrent::sha1_hash hash;
    ss >> hash;

    info.wrap->session_->dht_get_item(hash);

    return nullptr;
}

napi_value Session::DhtGetPeers(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    std::stringstream ss(v.ToString());
    libtorrent::sha1_hash hash;
    ss >> hash;

    info.wrap->session_->dht_get_peers(hash);

    return nullptr;
}

napi_value Session::DhtLiveNodes(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    std::stringstream ss(v.ToString());
    libtorrent::sha1_hash hash;
    ss >> hash;

    info.wrap->session_->dht_live_nodes(hash);

    return nullptr;
}

napi_value Session::FindTorrent(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    std::stringstream ss(v.ToString());
    libtorrent::sha1_hash hash;
    ss >> hash;

    auto th = info.wrap->session_->find_torrent(hash);
    auto arg = Napi::External<lt::torrent_handle>::New(env, &th);

    return TorrentHandle::NewInstance(arg);
}

napi_value Session::GetCacheInfo(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    libtorrent::torrent_handle th;
    int flags = 0;

    if (info.args.size() > 0)
    {
        Value v(env, info.args[0]);
        th = v.Unwrap<TorrentHandle>()->Wrapped();
    }

    if (info.args.size() > 1)
    {
        Value v(env, info.args[1]);
        flags = v.ToInt32();
    }

    libtorrent::cache_status cache;
    info.wrap->session_->get_cache_info(&cache, th, flags);

    napi_value obj;
    napi_value pieces;
    napi_create_object(env, &obj);
    napi_create_array_with_length(env, cache.pieces.size(), &pieces);
    napi_set_named_property(env, obj, "pieces", pieces);

    for (size_t i = 0; i < cache.pieces.size(); i++)
    {
        napi_value p;
        napi_create_object(env, &p);
        napi_set_element(env, pieces, i, p);

        napi_value blocks;
        napi_create_array_with_length(env, cache.pieces.at(i).blocks.size(), &blocks);

        for (size_t j = 0; j < cache.pieces.at(i).blocks.size(); j++)
        {
            napi_value b;
            napi_get_boolean(env, cache.pieces.at(i).blocks.at(j), &b);
            napi_set_element(env, blocks, j, b);
        }

        napi_set_named_property(env, p, "blocks", blocks);

        Value piece(env, p);
        piece.SetNamedProperty("kind", cache.pieces.at(i).kind);
        piece.SetNamedProperty("last_use", cache.pieces.at(i).last_use.time_since_epoch().count());
        piece.SetNamedProperty("need_readback", cache.pieces.at(i).need_readback);
        piece.SetNamedProperty("next_to_hash", cache.pieces.at(i).next_to_hash);
        piece.SetNamedProperty("piece", static_cast<int32_t>(cache.pieces.at(i).piece));
    }

    return obj;
}

napi_value Session::GetDhtSettings(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    auto settings = info.wrap->session_->get_dht_settings();

    napi_value obj;
    napi_create_object(env, &obj);

    Value v(env, obj);
    v.SetNamedProperty("aggressive_lookups", settings.aggressive_lookups);
    v.SetNamedProperty("block_ratelimit", settings.block_ratelimit);
    v.SetNamedProperty("block_timeout", settings.block_timeout);
    v.SetNamedProperty("enforce_node_id", settings.enforce_node_id);
    v.SetNamedProperty("extended_routing_table", settings.extended_routing_table);
    v.SetNamedProperty("ignore_dark_internet", settings.ignore_dark_internet);
    v.SetNamedProperty("item_lifetime", settings.item_lifetime);
    v.SetNamedProperty("max_dht_items", settings.max_dht_items);
    v.SetNamedProperty("max_fail_count", settings.max_fail_count);
    v.SetNamedProperty("max_infohashes_sample_count", settings.max_infohashes_sample_count);
    v.SetNamedProperty("max_peers", settings.max_peers);
    v.SetNamedProperty("max_peers_reply", settings.max_peers_reply);
    v.SetNamedProperty("max_torrent_search_reply", settings.max_torrent_search_reply);
    v.SetNamedProperty("max_torrents", settings.max_torrents);
    v.SetNamedProperty("privacy_lookups", settings.privacy_lookups);
    v.SetNamedProperty("read_only", settings.read_only);
    v.SetNamedProperty("restrict_routing_ips", settings.restrict_routing_ips);
    v.SetNamedProperty("restrict_search_ips", settings.restrict_search_ips);
    v.SetNamedProperty("sample_infohashes_interval", settings.sample_infohashes_interval);
    v.SetNamedProperty("search_branching", settings.search_branching);
    v.SetNamedProperty("upload_rate_limit", settings.upload_rate_limit);

    return obj;
}

napi_value Session::GetIpFilter(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    auto filter = info.wrap->session_->get_ip_filter();

    return WrapExternal<IpFilter, libtorrent::ip_filter>(env, &filter);
}

napi_value Session::GetPeerClass(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);

    auto cls = info.wrap->session_->get_peer_class(
        static_cast<libtorrent::peer_class_t>(v.ToInt32()));

    napi_value obj;
    napi_create_object(env, &obj);

    Value tmp(env, obj);
    tmp.SetNamedProperty("connection_limit_factor", cls.connection_limit_factor);
    tmp.SetNamedProperty("download_limit", cls.download_limit);
    tmp.SetNamedProperty("download_priority", cls.download_priority);
    tmp.SetNamedProperty("ignore_unchoke_slots", cls.ignore_unchoke_slots);
    tmp.SetNamedProperty("label", cls.label.c_str());
    tmp.SetNamedProperty("upload_limit", cls.upload_limit);
    tmp.SetNamedProperty("upload_priority", cls.upload_priority);

    return obj;
}

napi_value Session::GetPeerClassFilter(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    auto filter = info.wrap->session_->get_peer_class_filter();
    return WrapExternal<IpFilter, libtorrent::ip_filter>(env, &filter);
}

napi_value Session::GetPeerClassTypeFilter(napi_env env, napi_callback_info cbinfo)
{
    // auto info = UnwrapCallback<Session>(env, cbinfo);
    // auto typeFilter = info.wrap->session_->get_peer_class_type_filter();
    napi_throw_error(env, nullptr, "Not implemented");
    return nullptr;
}

napi_value Session::GetSettings(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    auto settings = info.wrap->session_->get_settings();

    return SettingsPack::Objectify(env, settings);
}

napi_value Session::GetTorrentStatus(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    auto status = info.wrap->session_->get_torrent_status(
        [](lt::torrent_status const&) { return true; });

    // TODO: filter

    napi_value arr;
    napi_create_array_with_length(env, status.size(), &arr);

    for (size_t i = 0; i < status.size(); i++)
    {
        auto arg = Napi::External<lt::torrent_status>::New(env, &status.at(i));
        napi_set_element(env, arr, i, TorrentStatus::NewInstance(arg));
    }

    return arr;
}

napi_value Session::GetTorrents(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    auto torrents = info.wrap->session_->get_torrents();

    napi_value arr;
    napi_create_array_with_length(env, torrents.size(), &arr);

    for (size_t i = 0; i < torrents.size(); i++)
    {
        auto arg = Napi::External<lt::torrent_handle>::New(env, &torrents.at(i));
        napi_set_element(env, arr, i, TorrentHandle::NewInstance(arg));
    }

    return arr;
}

napi_value Session::IsDhtRunning(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    napi_value res;
    napi_get_boolean(env, info.wrap->session_->is_dht_running(), &res);

    return res;
}

napi_value Session::IsListening(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    napi_value res;
    napi_get_boolean(env, info.wrap->session_->is_listening(), &res);

    return res;
}

napi_value Session::IsPaused(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    napi_value res;
    napi_get_boolean(env, info.wrap->session_->is_paused(), &res);

    return res;
}

napi_value Session::IsValid(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    napi_value res;
    napi_get_boolean(env, info.wrap->session_->is_valid(), &res);

    return res;
}

napi_value Session::ListenPort(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    napi_value res;
    napi_create_int32(env, info.wrap->session_->listen_port(), &res);

    return res;
}

napi_value Session::LoadState(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Napi::Value v(env, info.args[0]);

    if (v.IsBuffer())
    {
        auto buf = v.As<Napi::Buffer<char>>();
        std::vector<char> b(buf.Data(), buf.Data() + buf.Length());

        lt::error_code ec;
        lt::bdecode_node node = lt::bdecode(b, ec);

        if (ec)
        {
            napi_throw_error(env, nullptr, ec.message().c_str());
            return nullptr;
        }

        info.wrap->session_->load_state(node);
    }
    else
    {
        libtorrent::entry e = Entry::FromJson(env, info.args[0]);

        std::vector<char> buf;
        libtorrent::bencode(std::back_inserter(buf), e);

        libtorrent::bdecode_node node;
        libtorrent::error_code ec;
        libtorrent::bdecode(buf, ec);

        if (ec)
        {
            napi_throw_error(env, nullptr, ec.message().c_str());
            return nullptr;
        }

        info.wrap->session_->load_state(node);
    }

    return nullptr;
}

napi_value Session::Pause(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    info.wrap->session_->pause();
    return nullptr;
}

napi_value Session::PopAlerts(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    std::vector<libtorrent::alert*> alerts;
    info.wrap->session_->pop_alerts(&alerts);

    napi_value res;
    NAPI_CALL(env, napi_create_array_with_length(env, alerts.size(), &res));

    for (size_t i = 0; i < alerts.size(); i++)
    {
        napi_value alert = Alert::ToJson(env, alerts.at(i));
        napi_set_element(env, res, i, alert);
    }

    return res;
}

napi_value Session::PostDhtStats(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    info.wrap->session_->post_dht_stats();
    return nullptr;
}

napi_value Session::PostSessionStats(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    info.wrap->session_->post_session_stats();
    return nullptr;
}

napi_value Session::PostTorrentUpdates(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    //TODO: flags
    info.wrap->session_->post_torrent_updates();
    return nullptr;
}

napi_value Session::RemoveTorrent(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    TorrentHandle* th = v.Unwrap<TorrentHandle>();

    // TODO: flags
    info.wrap->session_->remove_torrent(th->Wrapped());

    return nullptr;
}

napi_value Session::ReopenNetworkSockets(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    //TODO: flags
    info.wrap->session_->reopen_network_sockets();
    return nullptr;
}

napi_value Session::Resume(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    //TODO: flags
    info.wrap->session_->resume();
    return nullptr;
}

napi_value Session::SaveState(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    //TODO: flags
    libtorrent::entry e;
    info.wrap->session_->save_state(e);

    return Entry::ToJson(env, e);
}

napi_value Session::SaveStateBuffer(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);
    //TODO: flags
    libtorrent::entry e;
    info.wrap->session_->save_state(e);

    std::vector<char> buffer;
    lt::bencode(std::back_inserter(buffer), e);

    return Napi::Buffer<char>::Copy(env, buffer.data(), buffer.size());
}

napi_value Session::SetDhtSettings(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);

    libtorrent::dht::dht_settings dht;

    if (v.HasNamedProperty("aggressive_lookups"))
    {
        dht.aggressive_lookups = v.GetNamedProperty("aggressive_lookups").ToBool();
    }

    // TODO: all dht settings

    info.wrap->session_->set_dht_settings(dht);

    return nullptr;
}

napi_value Session::SetIpFilter(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    IpFilter* ipf = v.Unwrap<IpFilter>();

    info.wrap->session_->set_ip_filter(ipf->Wrapped());

    return nullptr;
}

napi_value Session::SetPeerClass(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 2)
    {
        napi_throw_error(env, nullptr, "Expected 2 arguments");
        return nullptr;
    }


    Value cid(env, info.args[0]);
    Value v(env, info.args[1]);

    libtorrent::peer_class_info pci;
    v.GetNamedProperty("connection_limit_factor", &pci.connection_limit_factor);
    v.GetNamedProperty("download_limit", &pci.download_limit);
    v.GetNamedProperty("download_priority", &pci.download_priority);
    v.GetNamedProperty("ignore_unchoke_slots", &pci.ignore_unchoke_slots);
    v.GetNamedProperty("label", &pci.label);
    v.GetNamedProperty("upload_limit", &pci.upload_limit);
    v.GetNamedProperty("upload_priority", &pci.upload_priority);

    info.wrap->session_->set_peer_class(
        static_cast<libtorrent::peer_class_t>(cid.ToInt32()),
        pci);

    return nullptr;
}

napi_value Session::SetPeerClassFilter(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    IpFilter* ipf = v.Unwrap<IpFilter>();

    info.wrap->session_->set_peer_class_filter(ipf->Wrapped());

    return nullptr;
}

napi_value Session::SetPeerClassTypeFilter(napi_env env, napi_callback_info cbinfo)
{
    // TODO
    napi_throw_error(env, nullptr, "Not implemented");
    return nullptr;
}

napi_value Session::SetPortFilter(napi_env env, napi_callback_info cbinfo)
{
    // TODO
    napi_throw_error(env, nullptr, "Not implemented");
    return nullptr;

    /*auto info = UnwrapCallback<Session>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    info.wrap->session_->set_port_filter()*/
}

napi_value Session::SslListenPort(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);   

    napi_value res;
    napi_create_int32(env, info.wrap->session_->ssl_listen_port(), &res);

    return res;
}

struct AsyncRequest
{
    napi_ref callback_ref;
    bool result;
    Session* session;
    int32_t timeout;
    napi_async_work work;
};

void Session::WaitForAlertExecute(napi_env env, void* data)
{
    AsyncRequest* req = static_cast<AsyncRequest*>(data);
    auto alert = req->session->session_->wait_for_alert(libtorrent::milliseconds(req->timeout));
    req->result = (alert != nullptr);
}

void Session::WaitForAlertComplete(napi_env env, napi_status status, void* data)
{
    AsyncRequest* req = static_cast<AsyncRequest*>(data);

    napi_value callback;
    napi_get_reference_value(env, req->callback_ref, &callback);

    napi_value global;
    napi_get_global(env, &global);

    size_t argc = 2;
    napi_value argv[2];

    napi_get_null(env, &argv[0]);
    napi_get_boolean(env, req->result, &argv[1]);

    // Clean up
    napi_call_function(env, global, callback, argc, argv, nullptr);
    napi_delete_reference(env, req->callback_ref);
    napi_delete_async_work(env, req->work);

    delete req;
}

napi_value Session::WaitForAlert(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Session>(env, cbinfo);

    napi_value async_name;
    napi_create_string_utf8(env, "session.wait_for_alert", NAPI_AUTO_LENGTH, &async_name);

    AsyncRequest* req = new AsyncRequest();
    req->session = info.wrap;

    napi_create_reference(env, info.args[1], 1, &req->callback_ref);
    napi_get_value_int32(env, info.args[0], &req->timeout);

    napi_create_async_work(env, nullptr, async_name, WaitForAlertExecute, WaitForAlertComplete, req, &req->work);
    napi_queue_async_work(env, req->work);

    return nullptr;
}
