export declare function read_resume_data(buffer: Buffer): AddTorrentParams;

export declare function write_resume_data_buf(params: AddTorrentParams): Buffer;

export declare interface AddTorrentAlert {
  handle: TorrentHandle;
}

export declare interface SettingsPack {
  user_agent: string;
  outgoing_interfaces: string;
  listen_interfaces: string;
  proxy_hostname: string;
  proxy_username: string;
  proxy_password: string;
  i2p_hostname: string;
  peer_fingerprint: string;
  dht_bootstrap_nodes: string;

  tracker_completion_timeout: number;
  tracker_receive_timeout: number;
  stop_tracker_timeout: number;
  tracker_maximum_response_length: number;
  piece_timeout: number;
  request_timeout: number;
  request_queue_time: number;
  max_allowed_in_request_queue: number;
  max_out_request_queue: number;
  whole_pieces_threshold: number;
  peer_timeout: number;
  urlseed_timeout: number;
  urlseed_pipeline_size: number;
  urlseed_wait_retry: number;
  file_pool_size: number;
  max_failcount: number;
  min_reconnect_time: number;
  peer_connect_timeout: number;
  connection_speed: number;
  inactivity_timeout: number;
  unchoke_interval: number;
  optimistic_unchoke_interval: number;
  num_want: number;
  initial_picker_threshold: number;
  allowed_fast_set_size: number;
  suggest_mode: number;
  max_queued_disk_bytes: number;
  handshake_timeout: number;
  send_buffer_low_watermark: number;
  send_buffer_watermark: number;
  send_buffer_watermark_factor: number;
  choking_algorithm: number;
  seed_choking_algorithm: number;
  disk_io_write_mode: number;
  disk_io_read_mode: number;
  outgoing_port: number;
  num_outgoing_ports: number;
  peer_dscp: number;
  active_downloads: number;
  active_seeds: number;
  active_checking: number;
  active_dht_limit: number;
  active_tracker_limit: number;
  active_lsd_limit: number;
  active_limit: number;
  auto_manage_interval: number;
  seed_time_limit: number;
  auto_scrape_interval: number;
  auto_scrape_min_interval: number;
  max_peerlist_size: number;
  max_paused_peerlist_size: number;
  min_announce_interval: number;
  auto_manage_startup: number;
  seeding_piece_quota: number;
  max_rejects: number;
  recv_socket_buffer_size: number;
  send_socket_buffer_size: number;
  max_peer_recv_buffer_size: number;
  optimistic_disk_retry: number;
  max_suggest_pieces: number;
  local_service_announce_interval: number;
  dht_announce_interval: number;
  udp_tracker_token_expiry: number;
  num_optimistic_unchoke_slots: number;
  max_pex_peers: number;
  tick_interval: number;
  share_mode_target: number;
  upload_rate_limit: number;
  download_rate_limit: number;
  dht_upload_rate_limit: number;
  unchoke_slots_limit: number;
  connections_limit: number;
  connections_slack: number;
  utp_target_delay: number;
  utp_gain_factor: number;  
  utp_min_timeout: number;
  utp_syn_resends: number;
  utp_fin_resends: number;
  utp_num_resends: number;
  utp_connect_timeout: number;
  utp_loss_multiplier: number;
  mixed_mode_algorithm: number;
  listen_queue_size: number;
  torrent_connect_boost: number;
  alert_queue_size: number;
  max_metadata_size: number;
  hashing_threads: number;
  checking_mem_usage: number;
  predictive_piece_announce: number;
  aio_threads: number;
  tracker_backoff: number;
  share_ratio_limit: number;
  seed_time_ratio_limit: number;
  peer_turnover: number;
  peer_turnover_cutoff: number;
  peer_turnover_interval: number;
  connect_seed_every_n_download: number;
  max_http_recv_buffer_size: number;
  max_retry_port_bind: number;
  alert_mask: number;
  out_enc_policy: number;
  in_enc_policy: number;
  allowed_enc_level: number;
  inactive_down_rate: number;
  inactive_up_rate: number;
  proxy_type: number;
  proxy_port: number;
  i2p_port: number;
  urlseed_max_request_bytes: number;
  web_seed_name_lookup_retry: number;
  close_file_interval: number;
  utp_cwnd_reduce_timer: number;
  max_web_seed_connections: number;
  resolver_cache_timeout: number;
  send_not_sent_low_watermark: number;
  rate_choker_initial_threshold: number;
  upnp_lease_duration: number;
  max_concurrent_http_announces: number;
  dht_max_peers_reply: number;
  dht_search_branching: number;
  dht_max_fail_count: number;
  dht_max_torrents: number;
  dht_max_dht_items: number;
  dht_max_peers: number;
  dht_max_torrent_search_reply: number;
  dht_block_timeout: number;
  dht_block_ratelimit: number;
  dht_item_lifetime: number;
  dht_sample_infohashes_interval: number;
  dht_max_infohashes_sample_count: number;
  max_piece_count: number;
  metadata_token_limit: number;

  allow_multiple_connections_per_ip: boolean;
  send_redundant_have: boolean;
  use_dht_as_fallback: boolean;
  upnp_ignore_nonrouters: boolean;
  use_parole_mode: boolean;
  auto_manage_prefer_seeds: boolean;
  dont_count_slow_torrents: boolean;
  close_redundant_connections: boolean;
  prioritize_partial_pieces: boolean;
  rate_limit_ip_overhead: boolean;
  announce_to_all_trackers: boolean;
  announce_to_all_tiers: boolean;
  prefer_udp_trackers: boolean;
  disable_hash_checks: boolean;
  allow_i2p_mixed: boolean;
  no_atime_storage: boolean;
  incoming_starts_queued_torrents: boolean;
  report_true_downloaded: boolean;
  strict_end_game_mode: boolean;
  enable_outgoing_utp: boolean;
  enable_incoming_utp: boolean;
  enable_outgoing_tcp: boolean;
  enable_incoming_tcp: boolean;
  no_recheck_incomplete_resume: boolean;
  anonymous_mode: boolean;
  report_web_seed_downloads: boolean;
  seeding_outgoing_connections: boolean;
  no_connect_privileged_ports: boolean;
  smooth_connects: boolean;
  always_send_user_agent: boolean;
  apply_ip_filter_to_trackers: boolean;
  ban_web_seeds: boolean;
  support_share_mode: boolean;
  report_redundant_bytes: boolean;
  listen_system_port_fallback: boolean;
  announce_crypto_support: boolean;
  enable_upnp: boolean;
  enable_natpmp: boolean;
  enable_lsd: boolean;
  enable_dht: boolean;
  prefer_rc4: boolean;
  proxy_hostnames: boolean;
  proxy_peer_connections: boolean;
  auto_sequential: boolean;
  proxy_tracker_connections: boolean;
  enable_ip_notifier: boolean;
  dht_prefer_verified_node_ids: boolean;
  dht_restrict_routing_ips: boolean;
  dht_restrict_search_ips: boolean;
  dht_extended_routing_table: boolean;
  dht_aggressive_lookups: boolean;
  dht_privacy_lookups: boolean;
  dht_enforce_node_id: boolean;
  dht_ignore_dark_internet: boolean;
  dht_read_only: boolean;
  piece_extent_affinity: boolean;
  validate_https_trackers: boolean;
  ssrf_mitigation: boolean;
  allow_idna: boolean;
  enable_set_file_valid_data: boolean;
  socks5_udp_send_local_ep: boolean;
}

export declare class Session {
  add_torrent(params: AddTorrentParams): void;
  on(event: "add_torrent", callback: (data: AddTorrentAlert) => void): void;
  post_torrent_updates(): void;
}

export declare class AddTorrentParams {
  save_path: string;
  ti: TorrentInfo;
}

export declare class InfoHash {
  has_v1(): boolean;
  has_v2(): boolean;

  v1: string | null;
  v2: string | null;
}

export declare class TorrentInfo {
  constructor(file: string);
}

export declare class TorrentHandle {
  status(): TorrentStatus;
}

export declare class TorrentStatus {
  info_hashes: InfoHash;
  name: string;
}
