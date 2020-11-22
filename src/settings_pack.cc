#include "settings_pack.h"

#include <map>

#include "common.h"

using porla::SettingsPack;

#define BOOL_SETTING(name) \
    { #name, lt::settings_pack::bool_types:: name }

#define INT_SETTING(name) \
    { #name, lt::settings_pack::int_types:: name }

#define STRING_SETTING(name) \
    { #name, lt::settings_pack::string_types:: name }

static const std::map<std::string, int> BoolTypes =
{
    BOOL_SETTING(allow_multiple_connections_per_ip),
    BOOL_SETTING(send_redundant_have),
    BOOL_SETTING(use_dht_as_fallback),
    BOOL_SETTING(upnp_ignore_nonrouters),
    BOOL_SETTING(use_parole_mode),
    BOOL_SETTING(auto_manage_prefer_seeds),
    BOOL_SETTING(dont_count_slow_torrents),
    BOOL_SETTING(close_redundant_connections),
    BOOL_SETTING(prioritize_partial_pieces),
    BOOL_SETTING(rate_limit_ip_overhead),
    BOOL_SETTING(announce_to_all_tiers),
    BOOL_SETTING(announce_to_all_trackers),
    BOOL_SETTING(prefer_udp_trackers),
    BOOL_SETTING(disable_hash_checks),
    BOOL_SETTING(allow_i2p_mixed),
    BOOL_SETTING(volatile_read_cache),
    BOOL_SETTING(no_atime_storage),
    BOOL_SETTING(incoming_starts_queued_torrents),
    BOOL_SETTING(report_true_downloaded),
    BOOL_SETTING(strict_end_game_mode),
    BOOL_SETTING(enable_outgoing_utp),
    BOOL_SETTING(enable_incoming_utp),
    BOOL_SETTING(enable_outgoing_tcp),
    BOOL_SETTING(enable_incoming_tcp),
    BOOL_SETTING(no_recheck_incomplete_resume),
    BOOL_SETTING(anonymous_mode),
    BOOL_SETTING(report_web_seed_downloads),
    BOOL_SETTING(seeding_outgoing_connections),
    BOOL_SETTING(no_connect_privileged_ports),
    BOOL_SETTING(smooth_connects),
    BOOL_SETTING(always_send_user_agent),
    BOOL_SETTING(apply_ip_filter_to_trackers),
    BOOL_SETTING(ban_web_seeds),
    BOOL_SETTING(allow_partial_disk_writes),
    BOOL_SETTING(report_redundant_bytes),
    BOOL_SETTING(listen_system_port_fallback),
    BOOL_SETTING(announce_crypto_support),
    BOOL_SETTING(enable_upnp),
    BOOL_SETTING(enable_natpmp),
    BOOL_SETTING(enable_lsd),
    BOOL_SETTING(enable_dht),
    BOOL_SETTING(prefer_rc4),
    BOOL_SETTING(proxy_hostnames),
    BOOL_SETTING(proxy_peer_connections),
    BOOL_SETTING(auto_sequential),
    BOOL_SETTING(proxy_tracker_connections),
    BOOL_SETTING(enable_ip_notifier),
    BOOL_SETTING(dht_prefer_verified_node_ids),
    BOOL_SETTING(dht_restrict_routing_ips),
    BOOL_SETTING(dht_restrict_search_ips),
    BOOL_SETTING(dht_extended_routing_table),
    BOOL_SETTING(dht_aggressive_lookups),
    BOOL_SETTING(dht_privacy_lookups),
    BOOL_SETTING(dht_enforce_node_id),
    BOOL_SETTING(dht_ignore_dark_internet),
    BOOL_SETTING(dht_read_only),
    BOOL_SETTING(piece_extent_affinity),
    BOOL_SETTING(validate_https_trackers),
    BOOL_SETTING(enable_set_file_valid_data),
};

static const std::map<std::string, int> IntTypes =
{
    INT_SETTING(tracker_completion_timeout),
    INT_SETTING(tracker_receive_timeout),
    INT_SETTING(stop_tracker_timeout),
    INT_SETTING(tracker_maximum_response_length),
    INT_SETTING(piece_timeout),
    INT_SETTING(request_timeout),
    INT_SETTING(request_queue_time),
    INT_SETTING(max_allowed_in_request_queue),
    INT_SETTING(max_out_request_queue),
    INT_SETTING(whole_pieces_threshold),
    INT_SETTING(peer_timeout),
    INT_SETTING(urlseed_timeout),
    INT_SETTING(urlseed_pipeline_size),
    INT_SETTING(urlseed_wait_retry),
    INT_SETTING(file_pool_size),
    INT_SETTING(max_failcount),
    INT_SETTING(min_reconnect_time),
    INT_SETTING(peer_connect_timeout),
    INT_SETTING(connection_speed),
    INT_SETTING(inactivity_timeout),
    INT_SETTING(unchoke_interval),
    INT_SETTING(optimistic_unchoke_interval),
    INT_SETTING(num_want),
    INT_SETTING(initial_picker_threshold),
    INT_SETTING(allowed_fast_set_size),
    INT_SETTING(suggest_mode),
    INT_SETTING(max_queued_disk_bytes),
    INT_SETTING(handshake_timeout),
    INT_SETTING(send_buffer_low_watermark),
    INT_SETTING(send_buffer_watermark),
    INT_SETTING(send_buffer_watermark_factor),
    INT_SETTING(choking_algorithm),
    INT_SETTING(seed_choking_algorithm),
    INT_SETTING(disk_io_write_mode),
    INT_SETTING(disk_io_read_mode),
    INT_SETTING(outgoing_port),
    INT_SETTING(num_outgoing_ports),
    INT_SETTING(peer_tos),
    INT_SETTING(active_downloads),
    INT_SETTING(active_seeds),
    INT_SETTING(active_checking),
    INT_SETTING(active_dht_limit),
    INT_SETTING(active_tracker_limit),
    INT_SETTING(active_lsd_limit),
    INT_SETTING(active_limit),
    INT_SETTING(auto_manage_interval),
    INT_SETTING(seed_time_limit),
    INT_SETTING(auto_scrape_interval),
    INT_SETTING(auto_scrape_min_interval),
    INT_SETTING(max_peerlist_size),
    INT_SETTING(max_paused_peerlist_size),
    INT_SETTING(min_announce_interval),
    INT_SETTING(auto_manage_startup),
    INT_SETTING(seeding_piece_quota),
    INT_SETTING(max_rejects),
    INT_SETTING(recv_socket_buffer_size),
    INT_SETTING(send_socket_buffer_size),
    INT_SETTING(max_peer_recv_buffer_size),
    INT_SETTING(read_cache_line_size),
    INT_SETTING(write_cache_line_size),
    INT_SETTING(optimistic_disk_retry),
    INT_SETTING(max_suggest_pieces),
    INT_SETTING(local_service_announce_interval),
    INT_SETTING(dht_announce_interval),
    INT_SETTING(udp_tracker_token_expiry),
    INT_SETTING(num_optimistic_unchoke_slots),
    INT_SETTING(max_pex_peers),
    INT_SETTING(tick_interval),
    INT_SETTING(share_mode_target),
    INT_SETTING(upload_rate_limit),
    INT_SETTING(download_rate_limit),
    INT_SETTING(dht_upload_rate_limit),
    INT_SETTING(unchoke_slots_limit),
    INT_SETTING(connections_limit),
    INT_SETTING(connections_slack),
    INT_SETTING(utp_target_delay),
    INT_SETTING(utp_gain_factor),
    INT_SETTING(utp_min_timeout),
    INT_SETTING(utp_syn_resends),
    INT_SETTING(utp_fin_resends),
    INT_SETTING(utp_num_resends),
    INT_SETTING(utp_connect_timeout),
    INT_SETTING(utp_loss_multiplier),
    INT_SETTING(mixed_mode_algorithm),
    INT_SETTING(listen_queue_size),
    INT_SETTING(torrent_connect_boost),
    INT_SETTING(alert_queue_size),
    INT_SETTING(max_metadata_size),
    INT_SETTING(hashing_threads),
    INT_SETTING(checking_mem_usage),
    INT_SETTING(predictive_piece_announce),
    INT_SETTING(aio_threads),
    INT_SETTING(tracker_backoff),
    INT_SETTING(share_ratio_limit),
    INT_SETTING(seed_time_ratio_limit),
    INT_SETTING(peer_turnover),
    INT_SETTING(peer_turnover_cutoff),
    INT_SETTING(peer_turnover_interval),
    INT_SETTING(connect_seed_every_n_download),
    INT_SETTING(max_http_recv_buffer_size),
    INT_SETTING(max_retry_port_bind),
    INT_SETTING(alert_mask),
    INT_SETTING(out_enc_policy),
    INT_SETTING(in_enc_policy),
    INT_SETTING(allowed_enc_level),
    INT_SETTING(inactive_down_rate),
    INT_SETTING(inactive_up_rate),
    INT_SETTING(proxy_type),
    INT_SETTING(proxy_port),
    INT_SETTING(i2p_port),
    INT_SETTING(urlseed_max_request_bytes),
    INT_SETTING(web_seed_name_lookup_retry),
    INT_SETTING(close_file_interval),
    INT_SETTING(utp_cwnd_reduce_timer),
    INT_SETTING(max_web_seed_connections),
    INT_SETTING(resolver_cache_timeout),
    INT_SETTING(send_not_sent_low_watermark),
    INT_SETTING(rate_choker_initial_threshold),
    INT_SETTING(upnp_lease_duration),
    INT_SETTING(max_concurrent_http_announces),
    INT_SETTING(dht_max_peers_reply),
    INT_SETTING(dht_search_branching),
    INT_SETTING(dht_max_fail_count),
    INT_SETTING(dht_max_torrents),
    INT_SETTING(dht_max_dht_items),
    INT_SETTING(dht_max_peers),
    INT_SETTING(dht_max_torrent_search_reply),
    INT_SETTING(dht_block_timeout),
    INT_SETTING(dht_block_ratelimit),
    INT_SETTING(dht_item_lifetime),
    INT_SETTING(dht_sample_infohashes_interval),
    INT_SETTING(dht_max_infohashes_sample_count),
    INT_SETTING(max_piece_count),
};

static const std::map<std::string, int> StringTypes =
{
    STRING_SETTING(user_agent),
    STRING_SETTING(announce_ip),
    STRING_SETTING(handshake_client_version),
    STRING_SETTING(outgoing_interfaces),
    STRING_SETTING(listen_interfaces),
    STRING_SETTING(proxy_hostname),
    STRING_SETTING(proxy_username),
    STRING_SETTING(proxy_password),
    STRING_SETTING(i2p_hostname),
    STRING_SETTING(peer_fingerprint),
    STRING_SETTING(dht_bootstrap_nodes),
};

Napi::Object SettingsPack::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "SettingsPack",
    {
        InstanceMethod<&SettingsPack::GetBool>("get_bool"),
        InstanceMethod<&SettingsPack::GetInt>("get_int"),
        InstanceMethod<&SettingsPack::GetString>("get_str"),
        InstanceMethod<&SettingsPack::SetBool>("set_bool"),
        InstanceMethod<&SettingsPack::SetInt>("set_int"),
        InstanceMethod<&SettingsPack::SetString>("set_str")
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);

    exports.Set("settings_pack", func);

    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

Napi::Object SettingsPack::NewInstance(Napi::Env env, Napi::Value arg)
{
    Napi::EscapableHandleScope scope(env);
    Napi::Object obj = env.GetInstanceData<Napi::FunctionReference>()->New({ arg });
    return scope.Escape(napi_value(obj)).ToObject();
}

SettingsPack::SettingsPack(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<SettingsPack>(info),
    sp_(nullptr),
    owned_(false)
{
    if (info.Length() > 0)
    {
        auto data = info[0].As<Napi::External<SettingsPackData>>().Data();

        if (data->owned)
        {
            sp_ = data->pack;
            owned_ = true;
        }
        else
        {
            sp_ = new lt::settings_pack(*data->pack);
        }
    }
    else
    {
        sp_ = new lt::settings_pack();
    }
}

void SettingsPack::Finalize(Napi::Env env)
{
    if (!owned_)
    {
        delete sp_;
    }
}

libtorrent::settings_pack& SettingsPack::Wrapped()
{
    return *sp_;
}

Napi::Value SettingsPack::GetBool(const Napi::CallbackInfo& info)
{
    auto setting = info[0].ToString().Utf8Value();
    auto spb = BoolTypes.find(setting);

    if (spb == BoolTypes.end())
    {
        throw Napi::Error::New(info.Env(), "Invalid bool setting: " + setting);
    }

    return Napi::Boolean::New(info.Env(), sp_->get_bool(spb->second));
}

Napi::Value SettingsPack::GetInt(const Napi::CallbackInfo& info)
{
    auto setting = info[0].ToString().Utf8Value();
    auto spi = IntTypes.find(setting);

    if (spi != IntTypes.end())
    {
        if (spi->first == "alert_mask")
        {
            return Napi::Number::New(info.Env(), static_cast<uint32_t>(sp_->get_int(spi->second)));
        }

        return Napi::Number::New(info.Env(), sp_->get_int(spi->second));
    }

    throw Napi::Error::New(info.Env(), "Invalid int setting: " + setting);
}

Napi::Value SettingsPack::GetString(const Napi::CallbackInfo& info)
{
    auto setting = info[0].ToString().Utf8Value();
    auto sps = StringTypes.find(setting);

    if (sps == StringTypes.end())
    {
        throw Napi::Error::New(info.Env(), "Invalid string setting: " + setting);
    }

    return Napi::String::New(info.Env(), sp_->get_str(sps->second));
}

Napi::Value SettingsPack::SetBool(const Napi::CallbackInfo& info)
{
    auto setting = info[0].ToString().Utf8Value();
    auto spb = BoolTypes.find(setting);

    if (spb == BoolTypes.end())
    {
        throw Napi::Error::New(info.Env(), "Invalid bool setting: " + setting);
    }

    sp_->set_bool(spb->second, info[1].ToBoolean().Value());
    return info.Env().Undefined();
}

Napi::Value SettingsPack::SetInt(const Napi::CallbackInfo& info)
{
    auto setting = info[0].ToString().Utf8Value();
    auto spi = IntTypes.find(setting);

    if (spi == IntTypes.end())
    {
        throw Napi::Error::New(info.Env(), "Invalid int setting: " + setting);
    }

    sp_->set_int(spi->second, info[1].ToNumber().Int64Value());
    return info.Env().Undefined();
}

Napi::Value SettingsPack::SetString(const Napi::CallbackInfo& info)
{
    auto setting = info[0].ToString().Utf8Value();
    auto sps = StringTypes.find(setting);

    if (sps == StringTypes.end())
    {
        throw Napi::Error::New(info.Env(), "Invalid string setting: " + setting);
    }

    sp_->set_str(sps->second, info[1].ToString().Utf8Value());
    return info.Env().Undefined();
}
