
export declare interface add_torrent_params {
    dht_nodes?: any[];
    file_priorities?: number[];
    name?: string;
    save_path?: string;
    storage_mode?: number;
    ti?: torrent_info;
    tracker_tiers: number[];
    trackers: string[];
}

export declare interface alert {
    message: string;
    type: number;
    what: string;
}

export declare interface session_settings {
    active_checking?: number;
    active_dht_limit?: number;
    active_downloads?: number;
    active_limit?: number;
    active_lsd_limit?: number;
    active_seeds?: number;
    active_tracker_limit?: number;
    aio_max?: number;
    aio_threads?: number;
    alert_mask?: number;
    alert_queue_size?: number;
    allow_i2p_mixed?: boolean;
    allow_multiple_connections_per_ip?: boolean;
    allow_partial_disk_writes?: boolean;
    allowed_enc_level?: number;
    allowed_fast_set_size?: number;
    always_send_user_agent?: boolean;
    announce_crypto_support?: boolean;

    /**
     * The IP address passed along to trackers as the `&ip=` parameter. If
     * left as the default, that parameter is omitted.
     */
    announce_ip?: string;

    announce_to_all_tiers?: boolean;
    announce_to_all_trackers?: boolean;
    anonymous_mode?: boolean;
    apply_ip_filter_to_trackers?: boolean;
    auto_manage_interval?: number;
    auto_manage_prefer_seeds?: boolean;
    auto_manage_startup?: number;
    auto_scrape_interval?: number;
    auto_scrape_min_interval?: number;
    auto_sequential?: boolean;
    ban_web_seeds?: boolean;
    broadcast_lsd?: boolean;
    cache_expiry?: number;
    cache_size?: number;
    cache_size_volatile?: number;
    checking_mem_usage?: number;
    choking_algorithm?: number;
    close_file_interval?: number;
    close_redundant_connections?: boolean;
    coalesce_reads?: boolean;
    coalesce_writes?: boolean;
    connect_seed_every_n_download?: number;
    connection_speed?: number;
    connections_limit?: number;
    connections_slack?: number;
    decrease_est_reciprocation_rate?: number;
    default_est_reciprocation_rate?: number;
    dht_announce_interval?: number;
    dht_bootstrap_nodes?: string;
    disable_hash_checks?: boolean;
    disk_io_read_mode?: number;
    disk_io_write_mode?: number;
    dont_count_slow_torrents?: boolean;
    download_rate_limit?: number;
    enable_dht?: boolean;
    enable_incoming_tcp?: boolean;
    enable_incoming_utp?: boolean;
    enable_ip_notifier?: boolean;
    enable_lsd?: boolean;
    enable_natpmp?: boolean;
    enable_outgoing_tcp?: boolean;
    enable_outgoing_utp?: boolean;
    enable_upnp?: boolean;
    file_pool_size?: number;

    /**
     * The client name and version identifier sent to peers in the handshake
     * message. If this is an empty string, the user_agent is used instead.
     */
    handshake_client_version?: string;

    handshake_timeout?: number;
    i2p_hostname?: string;
    i2p_port?: number;
    in_enc_policy?: number;
    inactive_down_rate?: number;
    inactive_up_rate?: number;
    inactivity_timeout?: number;
    incoming_starts_queued_torrents?: boolean;
    increase_est_reciprocation_rate?: number;
    initial_picker_threshold?: number;

    /**
     * A comma-separated list of (IP or device name, port) pairs. These are the
     * listen ports that will be opened for accepting incoming uTP and TCP
     * connections. It is possible to listen on multiple interfaces and
     * multiple ports. Binding to port 0 will make the operating system pick
     * the port. The default is "0.0.0.0:6881,[::]:6881", which binds to all
     * interfaces on port 6881.
     * 
     * A port that has an "s" suffix will accept SSL connections. (note that
     * SSL sockets are not enabled by default).
     * 
     * If binding fails, the listen_failed_alert is posted. If or once a socket
     * binding succeeds, the listen_succeeded_alert is posted. There may be
     * multiple failures before a success.
     * 
     * For example:
     * `[::1]:8888` - will only accept connections on the IPv6 loopback address
     * on port 8888.
     * 
     * `eth0:4444,eth1:4444` - will accept connections on port 4444 on any IP
     * address bound to device ``eth0`` or ``eth1``.
     * 
     * `[::]:0s` - will accept SSL connections on a port chosen by the OS. And
     * not accept non-SSL connections at all.
     * 
     * Windows OS network adapter device name can be specified with GUID. It
     * can be obtained from "netsh lan show interfaces" command output. GUID
     * must be uppercased string embraced in curly brackets.
     * 
     * `{E4F0B674-0DFC-48BB-98A5-2AA730BDB6D6}::7777` - will accept connections
     * on port 7777 on adapter with this GUID.
     */
    listen_interfaces?: string;

    listen_queue_size?: number;
    listen_system_port_fallback?: boolean;
    local_service_announce_interval?: number;
    max_allowed_in_request_queue?: number;
    max_failcount?: number;
    max_http_recv_buffer_size?: number;
    max_metadata_size?: number;
    max_out_request_queue?: number;
    max_paused_peerlist_size?: number;
    max_peer_recv_buffer_size?: number;
    max_peerlist_size?: number;
    max_pex_peers?: number;
    max_queued_disk_bytes?: number;
    max_rejects?: number;
    max_retry_port_bind?: number;
    max_suggest_pieces?: number;
    max_web_seed_connections?: number;
    min_announce_interval?: number;
    min_reconnect_time?: number;
    mixed_mode_algorithm?: number;
    no_atime_storage?: boolean;
    no_connect_privileged_ports?: boolean;
    no_recheck_incomplete_resume?: boolean;
    num_optimistic_unchoke_slots?: number;
    num_outgoing_ports?: number;
    num_want?: number;
    optimistic_disk_retry?: number;
    optimistic_unchoke_interval?: number;
    out_enc_policy?: number;

    /**
     * The network interface this session will use when it opens outgoing
     * connections. By default, it binds outgoing connections to INADDR_ANY and
     * port 0 (i.e. let the OS decide). Ths parameter must be a string
     * containing one or more, comma separated, adapter names. Adapter names on
     * unix systems are of the form "eth0", "eth1", "tun0", etc. When
     * specifying multiple interfaces, they will be assigned in round-robin
     * order. This may be useful for clients that are multi-homed. Binding an
     * outgoing connection to a local IP does not necessarily make the
     * connection via the associated NIC/Adapter. Setting this to an empty
     * string will disable binding of outgoing connections.
     */
    outgoing_interfaces?: string;

    outgoing_port?: number;
    peer_connect_timeout?: number;

    /**
     * The fingerprint for the client. It will be used as the prefix to the
     * peer_id. If this is 20 bytes (or longer) it will be truncated to 20
     * bytes and used as the entire peer-id.
     * 
     * There is a utility function, generate_fingerprint() that can be used to
     * generate a standard client peer ID fingerprint prefix.
     */
    peer_fingerprint?: string;

    peer_timeout?: number;
    peer_tos?: number;
    peer_turnover?: number;
    peer_turnover_cutoff?: number;
    peer_turnover_interval?: number;
    piece_timeout?: number;
    predictive_piece_announce?: number;
    prefer_rc4?: boolean;
    prefer_udp_trackers?: boolean;
    prioritize_partial_pieces?: boolean;

    /**
     * When using a poxy, this is the hostname where the proxy is running.
     */
    proxy_hostname?: string;

    proxy_hostnames?: boolean;
    proxy_password?: string;
    proxy_peer_connections?: boolean;
    proxy_port?: number;
    proxy_tracker_connections?: boolean;
    proxy_type?: number;
    proxy_username?: string;
    rate_limit_ip_overhead?: boolean;
    read_cache_line_size?: number;
    recv_socket_buffer_size?: number;
    report_redundant_bytes?: boolean;
    report_true_downloaded?: boolean;
    report_web_seed_downloads?: boolean;
    request_queue_time?: number;
    request_timeout?: number;
    resolver_cache_timeout?: number;
    seed_choking_algorithm?: number;
    seed_time_limit?: number;
    seed_time_ratio_limit?: number;
    seeding_outgoing_connections?: boolean;
    seeding_piece_quota?: number;
    send_buffer_low_watermark?: number;
    send_buffer_watermark?: number;
    send_buffer_watermark_factor?: number;
    send_redundant_have?: boolean;
    send_socket_buffer_size?: number;
    share_mode_target?: number;
    share_ratio_limit?: number;
    smooth_connects?: boolean;
    stop_tracker_timeout?: number;
    strict_end_game_mode?: boolean;
    strict_super_seeding?: boolean;
    suggest_mode?: number;
    support_merkle_torrents?: boolean;
    support_share_mode?: boolean;
    tick_interval?: number;
    torrent_connect_boost?: number;
    tracker_backoff?: number;
    tracker_completion_timeout?: number;
    tracker_maximum_response_length?: number;
    tracker_receive_timeout?: number;
    udp_tracker_token_expiry?: number;
    unchoke_interval?: number;
    unchoke_slots_limit?: number;
    upload_rate_limit?: number;
    upnp_ignore_nonrouters?: boolean;
    urlseed_max_request_bytes?: number;
    urlseed_pipeline_size?: number;
    urlseed_timeout?: number;
    urlseed_wait_retry?: number;
    use_dht_as_fallback?: boolean;
    use_parole_mode?: boolean;
    use_read_cache?: boolean;

    /**
     * The client identification to the tracker. The recommended format of this
     * string is: "ClientName/ClientVersion libtorrent/libtorrentVersion". This
     * name will not only be used when making HTTP requests, but also when
     * sending extended headers to peers that support that extension. It may
     * not contain \r or \n.
     */
    user_agent?: string;

    utp_connect_timeout?: number;
    utp_fin_resends?: number;
    utp_gain_factor?: number;
    utp_loss_multiplier?: number;
    utp_min_timeout?: number;
    utp_num_resends?: number;
    utp_syn_resends?: number;
    utp_target_delay?: number;
    volatile_read_cache?: boolean;
    web_seed_name_lookup_retry?: number;
    whole_pieces_threshold?: number;
    write_cache_line_size?: number;
}

export declare interface torrent_alert extends alert {
    handle: torrent_handle;
}

export declare class torrent_info {
    constructor(fileName: string);
}

export declare class torrent_handle {
    status(): torrent_status;
}

export declare class torrent_status {
    get active_time(): number;
    get added_time(): number;
    get all_time_download(): number;
    get all_time_upload(): number;
}

export declare class session {
    constructor(settings?: session_settings);

    add_torrent(params: add_torrent_params): torrent_handle;
    pop_alerts(): Array<alert>;
    wait_for_alert(timeout: number, callback: (err: Error, result: boolean) => void): void;
}
