#include "settings_pack.h"

#include "common.h"

using porla::SettingsPack;

#define SET_SETTINGSPACK_BOOL(property, settings, key) \
    if (property.HasNamedProperty(#key)) \
    { \
        settings.set_bool(libtorrent::settings_pack::bool_types::key, property.GetNamedProperty(#key).ToBool()); \
    }

#define SET_SETTINGSPACK_INT32(property, settings, key) \
    if (property.HasNamedProperty(#key)) \
    { \
        settings.set_int(libtorrent::settings_pack::int_types::key, property.GetNamedProperty(#key).ToInt32()); \
    }

#define SET_SETTINGSPACK_STRING(property, settings, key) \
    if (property.HasNamedProperty(#key)) \
    { \
        settings.set_str(libtorrent::settings_pack::string_types::key, property.GetNamedProperty(#key).ToString()); \
    }

#define SET_VALUE_PROPERTY_BOOL(value, settings, key) \
    value.SetNamedProperty(#key, settings.get_bool(libtorrent::settings_pack::bool_types::key));

#define SET_VALUE_PROPERTY_INT32(value, settings, key) \
    value.SetNamedProperty(#key, settings.get_int(libtorrent::settings_pack::int_types::key));

#define SET_VALUE_PROPERTY_STRING(value, settings, key) \
    value.SetNamedProperty(#key, settings.get_str(libtorrent::settings_pack::string_types::key));


napi_value SettingsPack::Objectify(napi_env env, libtorrent::settings_pack const& settings)
{
    napi_value obj;
    napi_create_object(env, &obj);

    Value sp(env, obj);
    SET_VALUE_PROPERTY_BOOL(sp, settings, allow_i2p_mixed);
    SET_VALUE_PROPERTY_BOOL(sp, settings, allow_multiple_connections_per_ip);
    SET_VALUE_PROPERTY_BOOL(sp, settings, allow_partial_disk_writes);
    SET_VALUE_PROPERTY_BOOL(sp, settings, always_send_user_agent);
    SET_VALUE_PROPERTY_BOOL(sp, settings, announce_crypto_support);
    SET_VALUE_PROPERTY_BOOL(sp, settings, announce_to_all_tiers);
    SET_VALUE_PROPERTY_BOOL(sp, settings, announce_to_all_trackers);
    SET_VALUE_PROPERTY_BOOL(sp, settings, anonymous_mode);
    SET_VALUE_PROPERTY_BOOL(sp, settings, apply_ip_filter_to_trackers);
    SET_VALUE_PROPERTY_BOOL(sp, settings, auto_manage_prefer_seeds);
    SET_VALUE_PROPERTY_BOOL(sp, settings, auto_sequential);
    SET_VALUE_PROPERTY_BOOL(sp, settings, ban_web_seeds);
    SET_VALUE_PROPERTY_BOOL(sp, settings, broadcast_lsd);
    SET_VALUE_PROPERTY_BOOL(sp, settings, close_redundant_connections);
    SET_VALUE_PROPERTY_BOOL(sp, settings, coalesce_reads);
    SET_VALUE_PROPERTY_BOOL(sp, settings, coalesce_writes);
    SET_VALUE_PROPERTY_BOOL(sp, settings, disable_hash_checks);
    SET_VALUE_PROPERTY_BOOL(sp, settings, dont_count_slow_torrents);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_dht);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_incoming_tcp);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_incoming_utp);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_ip_notifier);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_lsd);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_natpmp);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_outgoing_tcp);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_outgoing_utp);
    SET_VALUE_PROPERTY_BOOL(sp, settings, enable_upnp);
    SET_VALUE_PROPERTY_BOOL(sp, settings, incoming_starts_queued_torrents);
    SET_VALUE_PROPERTY_BOOL(sp, settings, listen_system_port_fallback);
    SET_VALUE_PROPERTY_BOOL(sp, settings, no_atime_storage);
    SET_VALUE_PROPERTY_BOOL(sp, settings, no_connect_privileged_ports);
    SET_VALUE_PROPERTY_BOOL(sp, settings, no_recheck_incomplete_resume);
    SET_VALUE_PROPERTY_BOOL(sp, settings, prefer_rc4);
    SET_VALUE_PROPERTY_BOOL(sp, settings, prefer_udp_trackers);
    SET_VALUE_PROPERTY_BOOL(sp, settings, prioritize_partial_pieces);
    SET_VALUE_PROPERTY_BOOL(sp, settings, proxy_hostnames);
    SET_VALUE_PROPERTY_BOOL(sp, settings, proxy_peer_connections);
    SET_VALUE_PROPERTY_BOOL(sp, settings, proxy_tracker_connections);
    SET_VALUE_PROPERTY_BOOL(sp, settings, rate_limit_ip_overhead);
    SET_VALUE_PROPERTY_BOOL(sp, settings, report_redundant_bytes);
    SET_VALUE_PROPERTY_BOOL(sp, settings, report_true_downloaded);
    SET_VALUE_PROPERTY_BOOL(sp, settings, report_web_seed_downloads);
    SET_VALUE_PROPERTY_BOOL(sp, settings, seeding_outgoing_connections);
    SET_VALUE_PROPERTY_BOOL(sp, settings, send_redundant_have);
    SET_VALUE_PROPERTY_BOOL(sp, settings, smooth_connects);
    SET_VALUE_PROPERTY_BOOL(sp, settings, strict_end_game_mode);
    SET_VALUE_PROPERTY_BOOL(sp, settings, strict_super_seeding);
    SET_VALUE_PROPERTY_BOOL(sp, settings, support_merkle_torrents);
    SET_VALUE_PROPERTY_BOOL(sp, settings, support_share_mode);
    SET_VALUE_PROPERTY_BOOL(sp, settings, upnp_ignore_nonrouters);
    SET_VALUE_PROPERTY_BOOL(sp, settings, use_dht_as_fallback);
    SET_VALUE_PROPERTY_BOOL(sp, settings, use_parole_mode);
    SET_VALUE_PROPERTY_BOOL(sp, settings, use_read_cache);
    SET_VALUE_PROPERTY_BOOL(sp, settings, volatile_read_cache);

    SET_VALUE_PROPERTY_INT32(sp, settings, active_checking);
    SET_VALUE_PROPERTY_INT32(sp, settings, active_dht_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, active_downloads);
    SET_VALUE_PROPERTY_INT32(sp, settings, active_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, active_lsd_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, active_seeds);
    SET_VALUE_PROPERTY_INT32(sp, settings, active_tracker_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, aio_max);
    SET_VALUE_PROPERTY_INT32(sp, settings, aio_threads);
    SET_VALUE_PROPERTY_INT32(sp, settings, alert_mask);
    SET_VALUE_PROPERTY_INT32(sp, settings, alert_queue_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, allowed_enc_level);
    SET_VALUE_PROPERTY_INT32(sp, settings, allowed_fast_set_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, auto_manage_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, auto_manage_startup);
    SET_VALUE_PROPERTY_INT32(sp, settings, auto_scrape_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, auto_scrape_min_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, cache_expiry);
    SET_VALUE_PROPERTY_INT32(sp, settings, cache_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, cache_size_volatile);
    SET_VALUE_PROPERTY_INT32(sp, settings, checking_mem_usage);
    SET_VALUE_PROPERTY_INT32(sp, settings, choking_algorithm);
    SET_VALUE_PROPERTY_INT32(sp, settings, close_file_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, connect_seed_every_n_download);
    SET_VALUE_PROPERTY_INT32(sp, settings, connection_speed);
    SET_VALUE_PROPERTY_INT32(sp, settings, connections_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, connections_slack);
    SET_VALUE_PROPERTY_INT32(sp, settings, decrease_est_reciprocation_rate);
    SET_VALUE_PROPERTY_INT32(sp, settings, default_est_reciprocation_rate);
    SET_VALUE_PROPERTY_INT32(sp, settings, dht_announce_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, disk_io_read_mode);
    SET_VALUE_PROPERTY_INT32(sp, settings, disk_io_write_mode);
    SET_VALUE_PROPERTY_INT32(sp, settings, download_rate_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, file_pool_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, handshake_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, i2p_port);
    SET_VALUE_PROPERTY_INT32(sp, settings, in_enc_policy);
    SET_VALUE_PROPERTY_INT32(sp, settings, inactive_down_rate);
    SET_VALUE_PROPERTY_INT32(sp, settings, inactive_up_rate);
    SET_VALUE_PROPERTY_INT32(sp, settings, inactivity_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, increase_est_reciprocation_rate);
    SET_VALUE_PROPERTY_INT32(sp, settings, initial_picker_threshold);
    SET_VALUE_PROPERTY_INT32(sp, settings, listen_queue_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, local_service_announce_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_allowed_in_request_queue);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_failcount);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_http_recv_buffer_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_metadata_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_out_request_queue);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_paused_peerlist_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_peer_recv_buffer_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_peerlist_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_pex_peers);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_queued_disk_bytes);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_rejects);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_retry_port_bind);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_suggest_pieces);
    SET_VALUE_PROPERTY_INT32(sp, settings, max_web_seed_connections);
    SET_VALUE_PROPERTY_INT32(sp, settings, min_announce_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, min_reconnect_time);
    SET_VALUE_PROPERTY_INT32(sp, settings, mixed_mode_algorithm);
    SET_VALUE_PROPERTY_INT32(sp, settings, num_optimistic_unchoke_slots);
    SET_VALUE_PROPERTY_INT32(sp, settings, num_outgoing_ports);
    SET_VALUE_PROPERTY_INT32(sp, settings, num_want);
    SET_VALUE_PROPERTY_INT32(sp, settings, optimistic_disk_retry);
    SET_VALUE_PROPERTY_INT32(sp, settings, optimistic_unchoke_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, out_enc_policy);
    SET_VALUE_PROPERTY_INT32(sp, settings, outgoing_port);
    SET_VALUE_PROPERTY_INT32(sp, settings, peer_connect_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, peer_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, peer_tos);
    SET_VALUE_PROPERTY_INT32(sp, settings, peer_turnover);
    SET_VALUE_PROPERTY_INT32(sp, settings, peer_turnover_cutoff);
    SET_VALUE_PROPERTY_INT32(sp, settings, peer_turnover_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, piece_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, predictive_piece_announce);
    SET_VALUE_PROPERTY_INT32(sp, settings, proxy_port);
    SET_VALUE_PROPERTY_INT32(sp, settings, proxy_type);
    SET_VALUE_PROPERTY_INT32(sp, settings, read_cache_line_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, recv_socket_buffer_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, request_queue_time);
    SET_VALUE_PROPERTY_INT32(sp, settings, request_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, resolver_cache_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, seed_choking_algorithm);
    SET_VALUE_PROPERTY_INT32(sp, settings, seed_time_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, seed_time_ratio_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, seeding_piece_quota);
    SET_VALUE_PROPERTY_INT32(sp, settings, send_buffer_low_watermark);
    SET_VALUE_PROPERTY_INT32(sp, settings, send_buffer_watermark);
    SET_VALUE_PROPERTY_INT32(sp, settings, send_buffer_watermark_factor);
    SET_VALUE_PROPERTY_INT32(sp, settings, send_socket_buffer_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, share_mode_target);
    SET_VALUE_PROPERTY_INT32(sp, settings, share_ratio_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, stop_tracker_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, suggest_mode);
    SET_VALUE_PROPERTY_INT32(sp, settings, tick_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, torrent_connect_boost);
    SET_VALUE_PROPERTY_INT32(sp, settings, tracker_backoff);
    SET_VALUE_PROPERTY_INT32(sp, settings, tracker_completion_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, tracker_maximum_response_length);
    SET_VALUE_PROPERTY_INT32(sp, settings, tracker_receive_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, udp_tracker_token_expiry);
    SET_VALUE_PROPERTY_INT32(sp, settings, unchoke_interval);
    SET_VALUE_PROPERTY_INT32(sp, settings, unchoke_slots_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, upload_rate_limit);
    SET_VALUE_PROPERTY_INT32(sp, settings, urlseed_max_request_bytes);
    SET_VALUE_PROPERTY_INT32(sp, settings, urlseed_pipeline_size);
    SET_VALUE_PROPERTY_INT32(sp, settings, urlseed_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, urlseed_wait_retry);
    SET_VALUE_PROPERTY_INT32(sp, settings, utp_connect_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, utp_fin_resends);
    SET_VALUE_PROPERTY_INT32(sp, settings, utp_gain_factor);
    SET_VALUE_PROPERTY_INT32(sp, settings, utp_loss_multiplier);
    SET_VALUE_PROPERTY_INT32(sp, settings, utp_min_timeout);
    SET_VALUE_PROPERTY_INT32(sp, settings, utp_num_resends);
    SET_VALUE_PROPERTY_INT32(sp, settings, utp_syn_resends);
    SET_VALUE_PROPERTY_INT32(sp, settings, utp_target_delay);
    SET_VALUE_PROPERTY_INT32(sp, settings, web_seed_name_lookup_retry);
    SET_VALUE_PROPERTY_INT32(sp, settings, whole_pieces_threshold);
    SET_VALUE_PROPERTY_INT32(sp, settings, write_cache_line_size);

    SET_VALUE_PROPERTY_STRING(sp, settings, announce_ip);
    SET_VALUE_PROPERTY_STRING(sp, settings, dht_bootstrap_nodes);
    SET_VALUE_PROPERTY_STRING(sp, settings, handshake_client_version);
    SET_VALUE_PROPERTY_STRING(sp, settings, i2p_hostname);
    SET_VALUE_PROPERTY_STRING(sp, settings, listen_interfaces);
    SET_VALUE_PROPERTY_STRING(sp, settings, outgoing_interfaces);
    SET_VALUE_PROPERTY_STRING(sp, settings, peer_fingerprint);
    SET_VALUE_PROPERTY_STRING(sp, settings, proxy_hostname);
    SET_VALUE_PROPERTY_STRING(sp, settings, proxy_password);
    SET_VALUE_PROPERTY_STRING(sp, settings, proxy_username);
    SET_VALUE_PROPERTY_STRING(sp, settings, user_agent);

    return obj;
}

libtorrent::settings_pack SettingsPack::Parse(napi_env env, napi_value value)
{
    libtorrent::settings_pack sp;
    Value properties(env, value);

    SET_SETTINGSPACK_BOOL(properties, sp, allow_i2p_mixed);
    SET_SETTINGSPACK_BOOL(properties, sp, allow_multiple_connections_per_ip);
    SET_SETTINGSPACK_BOOL(properties, sp, allow_partial_disk_writes);
    SET_SETTINGSPACK_BOOL(properties, sp, always_send_user_agent);
    SET_SETTINGSPACK_BOOL(properties, sp, announce_crypto_support);
    SET_SETTINGSPACK_BOOL(properties, sp, announce_to_all_tiers);
    SET_SETTINGSPACK_BOOL(properties, sp, announce_to_all_trackers);
    SET_SETTINGSPACK_BOOL(properties, sp, anonymous_mode);
    SET_SETTINGSPACK_BOOL(properties, sp, apply_ip_filter_to_trackers);
    SET_SETTINGSPACK_BOOL(properties, sp, auto_manage_prefer_seeds);
    SET_SETTINGSPACK_BOOL(properties, sp, auto_sequential);
    SET_SETTINGSPACK_BOOL(properties, sp, ban_web_seeds);
    SET_SETTINGSPACK_BOOL(properties, sp, broadcast_lsd);
    SET_SETTINGSPACK_BOOL(properties, sp, close_redundant_connections);
    SET_SETTINGSPACK_BOOL(properties, sp, coalesce_reads);
    SET_SETTINGSPACK_BOOL(properties, sp, coalesce_writes);
    SET_SETTINGSPACK_BOOL(properties, sp, disable_hash_checks);
    SET_SETTINGSPACK_BOOL(properties, sp, dont_count_slow_torrents);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_dht);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_incoming_tcp);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_incoming_utp);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_ip_notifier);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_lsd);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_natpmp);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_outgoing_tcp);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_outgoing_utp);
    SET_SETTINGSPACK_BOOL(properties, sp, enable_upnp);
    SET_SETTINGSPACK_BOOL(properties, sp, incoming_starts_queued_torrents);
    SET_SETTINGSPACK_BOOL(properties, sp, listen_system_port_fallback);
    SET_SETTINGSPACK_BOOL(properties, sp, no_atime_storage);
    SET_SETTINGSPACK_BOOL(properties, sp, no_connect_privileged_ports);
    SET_SETTINGSPACK_BOOL(properties, sp, no_recheck_incomplete_resume);
    SET_SETTINGSPACK_BOOL(properties, sp, prefer_rc4);
    SET_SETTINGSPACK_BOOL(properties, sp, prefer_udp_trackers);
    SET_SETTINGSPACK_BOOL(properties, sp, prioritize_partial_pieces);
    SET_SETTINGSPACK_BOOL(properties, sp, proxy_hostnames);
    SET_SETTINGSPACK_BOOL(properties, sp, proxy_peer_connections);
    SET_SETTINGSPACK_BOOL(properties, sp, proxy_tracker_connections);
    SET_SETTINGSPACK_BOOL(properties, sp, rate_limit_ip_overhead);
    SET_SETTINGSPACK_BOOL(properties, sp, report_redundant_bytes);
    SET_SETTINGSPACK_BOOL(properties, sp, report_true_downloaded);
    SET_SETTINGSPACK_BOOL(properties, sp, report_web_seed_downloads);
    SET_SETTINGSPACK_BOOL(properties, sp, seeding_outgoing_connections);
    SET_SETTINGSPACK_BOOL(properties, sp, send_redundant_have);
    SET_SETTINGSPACK_BOOL(properties, sp, smooth_connects);
    SET_SETTINGSPACK_BOOL(properties, sp, strict_end_game_mode);
    SET_SETTINGSPACK_BOOL(properties, sp, strict_super_seeding);
    SET_SETTINGSPACK_BOOL(properties, sp, support_merkle_torrents);
    SET_SETTINGSPACK_BOOL(properties, sp, support_share_mode);
    SET_SETTINGSPACK_BOOL(properties, sp, upnp_ignore_nonrouters);
    SET_SETTINGSPACK_BOOL(properties, sp, use_dht_as_fallback);
    SET_SETTINGSPACK_BOOL(properties, sp, use_parole_mode);
    SET_SETTINGSPACK_BOOL(properties, sp, use_read_cache);
    SET_SETTINGSPACK_BOOL(properties, sp, volatile_read_cache);

    SET_SETTINGSPACK_INT32(properties, sp, active_checking);
    SET_SETTINGSPACK_INT32(properties, sp, active_dht_limit);
    SET_SETTINGSPACK_INT32(properties, sp, active_downloads);
    SET_SETTINGSPACK_INT32(properties, sp, active_limit);
    SET_SETTINGSPACK_INT32(properties, sp, active_lsd_limit);
    SET_SETTINGSPACK_INT32(properties, sp, active_seeds);
    SET_SETTINGSPACK_INT32(properties, sp, active_tracker_limit);
    SET_SETTINGSPACK_INT32(properties, sp, aio_max);
    SET_SETTINGSPACK_INT32(properties, sp, aio_threads);
    SET_SETTINGSPACK_INT32(properties, sp, alert_mask);
    SET_SETTINGSPACK_INT32(properties, sp, alert_queue_size);
    SET_SETTINGSPACK_INT32(properties, sp, allowed_enc_level);
    SET_SETTINGSPACK_INT32(properties, sp, allowed_fast_set_size);
    SET_SETTINGSPACK_INT32(properties, sp, auto_manage_interval);
    SET_SETTINGSPACK_INT32(properties, sp, auto_manage_startup);
    SET_SETTINGSPACK_INT32(properties, sp, auto_scrape_interval);
    SET_SETTINGSPACK_INT32(properties, sp, auto_scrape_min_interval);
    SET_SETTINGSPACK_INT32(properties, sp, cache_expiry);
    SET_SETTINGSPACK_INT32(properties, sp, cache_size);
    SET_SETTINGSPACK_INT32(properties, sp, cache_size_volatile);
    SET_SETTINGSPACK_INT32(properties, sp, checking_mem_usage);
    SET_SETTINGSPACK_INT32(properties, sp, choking_algorithm);
    SET_SETTINGSPACK_INT32(properties, sp, close_file_interval);
    SET_SETTINGSPACK_INT32(properties, sp, connect_seed_every_n_download);
    SET_SETTINGSPACK_INT32(properties, sp, connection_speed);
    SET_SETTINGSPACK_INT32(properties, sp, connections_limit);
    SET_SETTINGSPACK_INT32(properties, sp, connections_slack);
    SET_SETTINGSPACK_INT32(properties, sp, decrease_est_reciprocation_rate);
    SET_SETTINGSPACK_INT32(properties, sp, default_est_reciprocation_rate);
    SET_SETTINGSPACK_INT32(properties, sp, dht_announce_interval);
    SET_SETTINGSPACK_INT32(properties, sp, disk_io_read_mode);
    SET_SETTINGSPACK_INT32(properties, sp, disk_io_write_mode);
    SET_SETTINGSPACK_INT32(properties, sp, download_rate_limit);
    SET_SETTINGSPACK_INT32(properties, sp, file_pool_size);
    SET_SETTINGSPACK_INT32(properties, sp, handshake_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, i2p_port);
    SET_SETTINGSPACK_INT32(properties, sp, in_enc_policy);
    SET_SETTINGSPACK_INT32(properties, sp, inactive_down_rate);
    SET_SETTINGSPACK_INT32(properties, sp, inactive_up_rate);
    SET_SETTINGSPACK_INT32(properties, sp, inactivity_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, increase_est_reciprocation_rate);
    SET_SETTINGSPACK_INT32(properties, sp, initial_picker_threshold);
    SET_SETTINGSPACK_INT32(properties, sp, listen_queue_size);
    SET_SETTINGSPACK_INT32(properties, sp, local_service_announce_interval);
    SET_SETTINGSPACK_INT32(properties, sp, max_allowed_in_request_queue);
    SET_SETTINGSPACK_INT32(properties, sp, max_failcount);
    SET_SETTINGSPACK_INT32(properties, sp, max_http_recv_buffer_size);
    SET_SETTINGSPACK_INT32(properties, sp, max_metadata_size);
    SET_SETTINGSPACK_INT32(properties, sp, max_out_request_queue);
    SET_SETTINGSPACK_INT32(properties, sp, max_paused_peerlist_size);
    SET_SETTINGSPACK_INT32(properties, sp, max_peer_recv_buffer_size);
    SET_SETTINGSPACK_INT32(properties, sp, max_peerlist_size);
    SET_SETTINGSPACK_INT32(properties, sp, max_pex_peers);
    SET_SETTINGSPACK_INT32(properties, sp, max_queued_disk_bytes);
    SET_SETTINGSPACK_INT32(properties, sp, max_rejects);
    SET_SETTINGSPACK_INT32(properties, sp, max_retry_port_bind);
    SET_SETTINGSPACK_INT32(properties, sp, max_suggest_pieces);
    SET_SETTINGSPACK_INT32(properties, sp, max_web_seed_connections);
    SET_SETTINGSPACK_INT32(properties, sp, min_announce_interval);
    SET_SETTINGSPACK_INT32(properties, sp, min_reconnect_time);
    SET_SETTINGSPACK_INT32(properties, sp, mixed_mode_algorithm);
    SET_SETTINGSPACK_INT32(properties, sp, num_optimistic_unchoke_slots);
    SET_SETTINGSPACK_INT32(properties, sp, num_outgoing_ports);
    SET_SETTINGSPACK_INT32(properties, sp, num_want);
    SET_SETTINGSPACK_INT32(properties, sp, optimistic_disk_retry);
    SET_SETTINGSPACK_INT32(properties, sp, optimistic_unchoke_interval);
    SET_SETTINGSPACK_INT32(properties, sp, out_enc_policy);
    SET_SETTINGSPACK_INT32(properties, sp, outgoing_port);
    SET_SETTINGSPACK_INT32(properties, sp, peer_connect_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, peer_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, peer_tos);
    SET_SETTINGSPACK_INT32(properties, sp, peer_turnover);
    SET_SETTINGSPACK_INT32(properties, sp, peer_turnover_cutoff);
    SET_SETTINGSPACK_INT32(properties, sp, peer_turnover_interval);
    SET_SETTINGSPACK_INT32(properties, sp, piece_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, predictive_piece_announce);
    SET_SETTINGSPACK_INT32(properties, sp, proxy_port);
    SET_SETTINGSPACK_INT32(properties, sp, proxy_type);
    SET_SETTINGSPACK_INT32(properties, sp, read_cache_line_size);
    SET_SETTINGSPACK_INT32(properties, sp, recv_socket_buffer_size);
    SET_SETTINGSPACK_INT32(properties, sp, request_queue_time);
    SET_SETTINGSPACK_INT32(properties, sp, request_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, resolver_cache_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, seed_choking_algorithm);
    SET_SETTINGSPACK_INT32(properties, sp, seed_time_limit);
    SET_SETTINGSPACK_INT32(properties, sp, seed_time_ratio_limit);
    SET_SETTINGSPACK_INT32(properties, sp, seeding_piece_quota);
    SET_SETTINGSPACK_INT32(properties, sp, send_buffer_low_watermark);
    SET_SETTINGSPACK_INT32(properties, sp, send_buffer_watermark);
    SET_SETTINGSPACK_INT32(properties, sp, send_buffer_watermark_factor);
    SET_SETTINGSPACK_INT32(properties, sp, send_socket_buffer_size);
    SET_SETTINGSPACK_INT32(properties, sp, share_mode_target);
    SET_SETTINGSPACK_INT32(properties, sp, share_ratio_limit);
    SET_SETTINGSPACK_INT32(properties, sp, stop_tracker_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, suggest_mode);
    SET_SETTINGSPACK_INT32(properties, sp, tick_interval);
    SET_SETTINGSPACK_INT32(properties, sp, torrent_connect_boost);
    SET_SETTINGSPACK_INT32(properties, sp, tracker_backoff);
    SET_SETTINGSPACK_INT32(properties, sp, tracker_completion_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, tracker_maximum_response_length);
    SET_SETTINGSPACK_INT32(properties, sp, tracker_receive_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, udp_tracker_token_expiry);
    SET_SETTINGSPACK_INT32(properties, sp, unchoke_interval);
    SET_SETTINGSPACK_INT32(properties, sp, unchoke_slots_limit);
    SET_SETTINGSPACK_INT32(properties, sp, upload_rate_limit);
    SET_SETTINGSPACK_INT32(properties, sp, urlseed_max_request_bytes);
    SET_SETTINGSPACK_INT32(properties, sp, urlseed_pipeline_size);
    SET_SETTINGSPACK_INT32(properties, sp, urlseed_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, urlseed_wait_retry);
    SET_SETTINGSPACK_INT32(properties, sp, utp_connect_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, utp_fin_resends);
    SET_SETTINGSPACK_INT32(properties, sp, utp_gain_factor);
    SET_SETTINGSPACK_INT32(properties, sp, utp_loss_multiplier);
    SET_SETTINGSPACK_INT32(properties, sp, utp_min_timeout);
    SET_SETTINGSPACK_INT32(properties, sp, utp_num_resends);
    SET_SETTINGSPACK_INT32(properties, sp, utp_syn_resends);
    SET_SETTINGSPACK_INT32(properties, sp, utp_target_delay);
    SET_SETTINGSPACK_INT32(properties, sp, web_seed_name_lookup_retry);
    SET_SETTINGSPACK_INT32(properties, sp, whole_pieces_threshold);
    SET_SETTINGSPACK_INT32(properties, sp, write_cache_line_size);

    SET_SETTINGSPACK_STRING(properties, sp, announce_ip);
    SET_SETTINGSPACK_STRING(properties, sp, dht_bootstrap_nodes);
    SET_SETTINGSPACK_STRING(properties, sp, handshake_client_version);
    SET_SETTINGSPACK_STRING(properties, sp, i2p_hostname);
    SET_SETTINGSPACK_STRING(properties, sp, listen_interfaces);
    SET_SETTINGSPACK_STRING(properties, sp, outgoing_interfaces);
    SET_SETTINGSPACK_STRING(properties, sp, peer_fingerprint);
    SET_SETTINGSPACK_STRING(properties, sp, proxy_hostname);
    SET_SETTINGSPACK_STRING(properties, sp, proxy_password);
    SET_SETTINGSPACK_STRING(properties, sp, proxy_username);
    SET_SETTINGSPACK_STRING(properties, sp, user_agent);

    return sp;
}
