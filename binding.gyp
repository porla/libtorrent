{
    "conditions": [
        [ 'OS=="win"', {
            'conditions': [
                ['target_arch=="x64"', {
                    'variables': {
                        'openssl_root%': 'C:/OpenSSL-Win64/lib/VC/static'
                    },
                }, {
                    'variables': {
                        'openssl_root%': 'C:/OpenSSL-Win32/lib/VC/static'
                    },
                }],
            ]
        }]
    ],

    "targets": [
        {
            "target_name": "porla_libtorrent",
            "dependencies": [ "boost-system", "libtorrent-rasterbar" ],
            "include_dirs":
            [
                "./vendor/boost-array/include",
                "./vendor/boost-asio/include",
                "./vendor/boost-assert/include",
                "./vendor/boost-bind/include",
                "./vendor/boost-concept_check/include",
                "./vendor/boost-config/include",
                "./vendor/boost-container/include",
                "./vendor/boost-container_hash/include",
                "./vendor/boost-core/include",
                "./vendor/boost-crc/include",
                "./vendor/boost-date_time/include",
                "./vendor/boost-detail/include",
                "./vendor/boost-function/include",
                "./vendor/boost-exception/include",
                "./vendor/boost-integer/include",
                "./vendor/boost-intrusive/include",
                "./vendor/boost-iterator/include",
                "./vendor/boost-lexical_cast/include",
                "./vendor/boost-math/include",
                "./vendor/boost-move/include",
                "./vendor/boost-mpl/include",
                "./vendor/boost-multiprecision/include",
                "./vendor/boost-numeric_conversion/include",
                "./vendor/boost-optional/include",
                "./vendor/boost-pool/include",
                "./vendor/boost-predef/include",
                "./vendor/boost-preprocessor/include",
                "./vendor/boost-range/include",
                "./vendor/boost-rational/include",
                "./vendor/boost-scope_exit/include",
                "./vendor/boost-smart_ptr/include",
                "./vendor/boost-static_assert/include",
                "./vendor/boost-system/include",
                "./vendor/boost-throw_exception/include",
                "./vendor/boost-type_index/include",
                "./vendor/boost-type_traits/include",
                "./vendor/boost-typeof/include",
                "./vendor/boost-utility/include",
                "./vendor/boost-variant/include",
                "./vendor/boost-winapi/include",
                "./vendor/libtorrent/include"
            ],
            "sources":
            [
                "./src/add_torrent_params.cc",
                "./src/alert.cc",
                "./src/bdecode.cc",
                "./src/common.cc",
                "./src/entry.cc",
                "./src/ip_filter.cc",
                "./src/porla-libtorrent.cc",
                "./src/session.cc",
                "./src/settings_pack.cc",
                "./src/torrent_info.cc",
                "./src/torrent_handle.cc",
                "./src/torrent_status.cc",
                "./src/utils.cc"
            ],
            "defines": [
                "BOOST_ALL_NO_LIB",
                "TORRENT_NO_DEPRECATE",
                "TORRENT_USE_OPENSSL"
            ],
            "conditions": [
                [ 'OS=="win"', {
                    'msvs_settings': {
                        'VCCLCompilerTool': {
                            "ExceptionHandling": 1,
                            "RuntimeTypeInfo": 'true'
                        }
                    },
                    "defines": [
                        "_WIN32",
                        "_WIN32_WINNT=0x0600",
                        "WIN32",
                        "WIN32_LEAN_AND_MEAN"
                    ],
                    "libraries": [
                        '-l<(openssl_root)/libeay32MT.lib',
                        '-l<(openssl_root)/ssleay32MT.lib',
                        '-liphlpapi',
                        '-llegacy_stdio_definitions'
                    ]
                }]
            ]
        },
        {
            "target_name": "boost-system",
            "type": "static_library",
            "defines":
            [
                "BOOST_SYSTEM_STATIC_LINK=1"
            ],
            "include_dirs":
            [
                "./vendor/boost-assert/include",
                "./vendor/boost-config/include",
                "./vendor/boost-container_hash/include",
                "./vendor/boost-core/include",
                "./vendor/boost-date_time/include",
                "./vendor/boost-exception/include",
                "./vendor/boost-mpl/include",
                "./vendor/boost-numeric_conversion/include",
                "./vendor/boost-pool/include",
                "./vendor/boost-predef/include",
                "./vendor/boost-preprocessor/include",
                "./vendor/boost-scope_exit/include",
                "./vendor/boost-smart_ptr/include",
                "./vendor/boost-static_assert/include",
                "./vendor/boost-system/include",
                "./vendor/boost-throw_exception/include",
                "./vendor/boost-type_traits/include",
                "./vendor/boost-utility/include",
                "./vendor/boost-winapi/include"
            ],
            "sources":
            [
                "./vendor/boost-system/src/error_code.cpp"
            ],
             "conditions": [
                [ 'OS=="win"', {
                    'msvs_settings': {
                        'VCCLCompilerTool': {
                            "ExceptionHandling": 1,
                            "RuntimeTypeInfo": 'true'
                        }
                    },
                    "defines": [
                        "_WIN32",
                        "_WIN32_WINNT=0x0600",
                        "WIN32",
                        "WIN32_LEAN_AND_MEAN"
                    ]
                }]
            ]
        },
        {
            "target_name": "libtorrent-rasterbar",
            "type": "static_library",
            "dependencies": [ "boost-system" ],
            "cflags!": [ "-fno-exceptions" ],
            "cflags":
            [
                "-Wall",
                "-Wextra",
                "-Wpedantic",
                "-Wmisleading-indentation",
                "-Wparentheses",
                "-Wvla",
                "-Wno-format-zero-length"
            ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "cflags_cc":
            [
                "-fPIC",
                "-Wc++11-compat"
            ],
            "defines":
            [
                "BOOST_ALL_NO_LIB",
                "BOOST_ASIO_ENABLE_CANCELIO",
                "BOOST_ASIO_HAS_STD_CHRONO",
                "BOOST_MULTI_INDEX_DISABLE_SERIALIZATION",
                "BOOST_NO_DEPRECATED",
                "BOOST_SYSTEM_NO_DEPRECATED",
                "BOOST_SYSTEM_STATIC_LINK=1",
                "OPENSSL_NO_SSL2",
                "TORRENT_BUILDING_LIBRARY",
                "TORRENT_NO_DEPRECATE",
                "TORRENT_USE_I2P=1",
                "TORRENT_USE_LIBCRYPTO",
                "TORRENT_USE_OPENSSL"
            ],
            "include_dirs":
            [
                "./vendor/boost-array/include",
                "./vendor/boost-asio/include",
                "./vendor/boost-assert/include",
                "./vendor/boost-bind/include",
                "./vendor/boost-concept_check/include",
                "./vendor/boost-config/include",
                "./vendor/boost-container/include",
                "./vendor/boost-container_hash/include",
                "./vendor/boost-core/include",
                "./vendor/boost-crc/include",
                "./vendor/boost-date_time/include",
                "./vendor/boost-detail/include",
                "./vendor/boost-function/include",
                "./vendor/boost-exception/include",
                "./vendor/boost-integer/include",
                "./vendor/boost-intrusive/include",
                "./vendor/boost-iterator/include",
                "./vendor/boost-lexical_cast/include",
                "./vendor/boost-math/include",
                "./vendor/boost-move/include",
                "./vendor/boost-mpl/include",
                "./vendor/boost-multiprecision/include",
                "./vendor/boost-numeric_conversion/include",
                "./vendor/boost-optional/include",
                "./vendor/boost-pool/include",
                "./vendor/boost-predef/include",
                "./vendor/boost-preprocessor/include",
                "./vendor/boost-range/include",
                "./vendor/boost-rational/include",
                "./vendor/boost-scope_exit/include",
                "./vendor/boost-smart_ptr/include",
                "./vendor/boost-static_assert/include",
                "./vendor/boost-system/include",
                "./vendor/boost-throw_exception/include",
                "./vendor/boost-type_index/include",
                "./vendor/boost-type_traits/include",
                "./vendor/boost-typeof/include",
                "./vendor/boost-utility/include",
                "./vendor/boost-variant/include",
                "./vendor/boost-winapi/include",
                "./vendor/libtorrent/include"
            ],
            "sources":
            [
                "./vendor/libtorrent/src/kademlia/dht_settings.cpp",
                "./vendor/libtorrent/src/kademlia/dht_state.cpp",
                "./vendor/libtorrent/src/kademlia/dht_storage.cpp",
                "./vendor/libtorrent/src/kademlia/dht_tracker.cpp",
                "./vendor/libtorrent/src/kademlia/dos_blocker.cpp",
                "./vendor/libtorrent/src/kademlia/ed25519.cpp",
                "./vendor/libtorrent/src/kademlia/find_data.cpp",
                "./vendor/libtorrent/src/kademlia/get_item.cpp",
                "./vendor/libtorrent/src/kademlia/get_peers.cpp",
                "./vendor/libtorrent/src/kademlia/item.cpp",
                "./vendor/libtorrent/src/kademlia/msg.cpp",
                "./vendor/libtorrent/src/kademlia/node_entry.cpp",
                "./vendor/libtorrent/src/kademlia/node_id.cpp",
                "./vendor/libtorrent/src/kademlia/node.cpp",
                "./vendor/libtorrent/src/kademlia/put_data.cpp",
                "./vendor/libtorrent/src/kademlia/refresh.cpp",
                "./vendor/libtorrent/src/kademlia/routing_table.cpp",
                "./vendor/libtorrent/src/kademlia/rpc_manager.cpp",
                "./vendor/libtorrent/src/kademlia/sample_infohashes.cpp",
                "./vendor/libtorrent/src/kademlia/traversal_algorithm.cpp",

                "./vendor/libtorrent/ed25519/src/add_scalar.cpp",
                "./vendor/libtorrent/ed25519/src/fe.cpp",
                "./vendor/libtorrent/ed25519/src/ge.cpp",
                "./vendor/libtorrent/ed25519/src/key_exchange.cpp",
                "./vendor/libtorrent/ed25519/src/keypair.cpp",
                "./vendor/libtorrent/ed25519/src/sc.cpp",
                "./vendor/libtorrent/ed25519/src/sign.cpp",
                "./vendor/libtorrent/ed25519/src/verify.cpp",

                "./vendor/libtorrent/src/add_torrent_params.cpp",
                "./vendor/libtorrent/src/alert_manager.cpp",
                "./vendor/libtorrent/src/alert.cpp",
                "./vendor/libtorrent/src/allocator.cpp",
                "./vendor/libtorrent/src/announce_entry.cpp",
                "./vendor/libtorrent/src/assert.cpp",
                "./vendor/libtorrent/src/bandwidth_limit.cpp",
                "./vendor/libtorrent/src/bandwidth_manager.cpp",
                "./vendor/libtorrent/src/bandwidth_queue_entry.cpp",
                "./vendor/libtorrent/src/bdecode.cpp",
                "./vendor/libtorrent/src/bitfield.cpp",
                "./vendor/libtorrent/src/block_cache.cpp",
                "./vendor/libtorrent/src/bloom_filter.cpp",
                "./vendor/libtorrent/src/broadcast_socket.cpp",
                "./vendor/libtorrent/src/bt_peer_connection.cpp",
                "./vendor/libtorrent/src/chained_buffer.cpp",
                "./vendor/libtorrent/src/choker.cpp",
                "./vendor/libtorrent/src/close_reason.cpp",
                "./vendor/libtorrent/src/ConvertUTF.cpp",
                "./vendor/libtorrent/src/cpuid.cpp",
                "./vendor/libtorrent/src/crc32c.cpp",
                "./vendor/libtorrent/src/create_torrent.cpp",
                "./vendor/libtorrent/src/disk_buffer_holder.cpp",
                "./vendor/libtorrent/src/disk_buffer_pool.cpp",
                "./vendor/libtorrent/src/disk_io_job.cpp",
                "./vendor/libtorrent/src/disk_io_thread_pool.cpp",
                "./vendor/libtorrent/src/disk_io_thread.cpp",
                "./vendor/libtorrent/src/disk_job_fence.cpp",
                "./vendor/libtorrent/src/disk_job_pool.cpp",
                "./vendor/libtorrent/src/entry.cpp",
                "./vendor/libtorrent/src/enum_net.cpp",
                "./vendor/libtorrent/src/error_code.cpp",
                "./vendor/libtorrent/src/escape_string.cpp",
                "./vendor/libtorrent/src/ffs.cpp",
                "./vendor/libtorrent/src/file_pool.cpp",
                "./vendor/libtorrent/src/file_progress.cpp",
                "./vendor/libtorrent/src/file_storage.cpp",
                "./vendor/libtorrent/src/file.cpp",
                "./vendor/libtorrent/src/fingerprint.cpp",
                "./vendor/libtorrent/src/generate_peer_id.cpp",
                "./vendor/libtorrent/src/gzip.cpp",
                "./vendor/libtorrent/src/hasher.cpp",
                "./vendor/libtorrent/src/hasher512.cpp",
                "./vendor/libtorrent/src/hex.cpp",
                "./vendor/libtorrent/src/http_connection.cpp",
                "./vendor/libtorrent/src/http_parser.cpp",
                "./vendor/libtorrent/src/http_seed_connection.cpp",
                "./vendor/libtorrent/src/http_stream.cpp",
                "./vendor/libtorrent/src/http_tracker_connection.cpp",
                "./vendor/libtorrent/src/i2p_stream.cpp",
                "./vendor/libtorrent/src/identify_client.cpp",
                "./vendor/libtorrent/src/instantiate_connection.cpp",
                "./vendor/libtorrent/src/ip_filter.cpp",
                "./vendor/libtorrent/src/ip_notifier.cpp",
                "./vendor/libtorrent/src/ip_voter.cpp",
                "./vendor/libtorrent/src/lazy_bdecode.cpp",
                "./vendor/libtorrent/src/listen_socket_handle.cpp",
                "./vendor/libtorrent/src/lsd.cpp",
                "./vendor/libtorrent/src/magnet_uri.cpp",
                "./vendor/libtorrent/src/merkle.cpp",
                "./vendor/libtorrent/src/natpmp.cpp",
                "./vendor/libtorrent/src/packet_buffer.cpp",
                "./vendor/libtorrent/src/parse_url.cpp",
                "./vendor/libtorrent/src/part_file.cpp",
                "./vendor/libtorrent/src/path.cpp",
                "./vendor/libtorrent/src/pe_crypto.cpp",
                "./vendor/libtorrent/src/peer_class_set.cpp",
                "./vendor/libtorrent/src/peer_class.cpp",
                "./vendor/libtorrent/src/peer_connection_handle.cpp",
                "./vendor/libtorrent/src/peer_connection.cpp",
                "./vendor/libtorrent/src/peer_info.cpp",
                "./vendor/libtorrent/src/peer_list.cpp",
                "./vendor/libtorrent/src/performance_counters.cpp",
                "./vendor/libtorrent/src/piece_picker.cpp",
                "./vendor/libtorrent/src/platform_util.cpp",
                "./vendor/libtorrent/src/proxy_base.cpp",
                "./vendor/libtorrent/src/proxy_settings.cpp",
                "./vendor/libtorrent/src/puff.cpp",
                "./vendor/libtorrent/src/random.cpp",
                "./vendor/libtorrent/src/read_resume_data.cpp",
                "./vendor/libtorrent/src/receive_buffer.cpp",
                "./vendor/libtorrent/src/request_blocks.cpp",
                "./vendor/libtorrent/src/resolve_links.cpp",
                "./vendor/libtorrent/src/resolver.cpp",
                "./vendor/libtorrent/src/session_call.cpp",
                "./vendor/libtorrent/src/session_handle.cpp",
                "./vendor/libtorrent/src/session_impl.cpp",
                "./vendor/libtorrent/src/session_settings.cpp",
                "./vendor/libtorrent/src/session_stats.cpp",
                "./vendor/libtorrent/src/session_udp_sockets.cpp",
                "./vendor/libtorrent/src/session.cpp",
                "./vendor/libtorrent/src/settings_pack.cpp",
                "./vendor/libtorrent/src/sha1_hash.cpp",
                "./vendor/libtorrent/src/sha1.cpp",
                "./vendor/libtorrent/src/sha512.cpp",
                "./vendor/libtorrent/src/smart_ban.cpp",
                "./vendor/libtorrent/src/socket_io.cpp",
                "./vendor/libtorrent/src/socket_type.cpp",
                "./vendor/libtorrent/src/socks5_stream.cpp",
                "./vendor/libtorrent/src/stack_allocator.cpp",
                "./vendor/libtorrent/src/stat_cache.cpp",
                "./vendor/libtorrent/src/stat.cpp",
                "./vendor/libtorrent/src/storage_piece_set.cpp",
                "./vendor/libtorrent/src/storage_utils.cpp",
                "./vendor/libtorrent/src/storage.cpp",
                "./vendor/libtorrent/src/string_util.cpp",
                "./vendor/libtorrent/src/time.cpp",
                "./vendor/libtorrent/src/timestamp_history.cpp",
                "./vendor/libtorrent/src/torrent_handle.cpp",
                "./vendor/libtorrent/src/torrent_info.cpp",
                "./vendor/libtorrent/src/torrent_peer_allocator.cpp",
                "./vendor/libtorrent/src/torrent_peer.cpp",
                "./vendor/libtorrent/src/torrent_status.cpp",
                "./vendor/libtorrent/src/torrent.cpp",
                "./vendor/libtorrent/src/tracker_manager.cpp",
                "./vendor/libtorrent/src/udp_socket.cpp",
                "./vendor/libtorrent/src/udp_tracker_connection.cpp",
                "./vendor/libtorrent/src/upnp.cpp",
                "./vendor/libtorrent/src/ut_metadata.cpp",
                "./vendor/libtorrent/src/ut_pex.cpp",
                "./vendor/libtorrent/src/utf8.cpp",
                "./vendor/libtorrent/src/utp_socket_manager.cpp",
                "./vendor/libtorrent/src/utp_stream.cpp",
                "./vendor/libtorrent/src/version.cpp",
                "./vendor/libtorrent/src/web_connection_base.cpp",
                "./vendor/libtorrent/src/web_peer_connection.cpp",
                "./vendor/libtorrent/src/write_resume_data.cpp",
                "./vendor/libtorrent/src/xml_parse.cpp"
            ],
            "conditions": [
                [ 'OS=="win"', {
                    'msvs_settings': {
                        'VCCLCompilerTool': {
                            "DisableSpecificWarnings": [ "4373", "4503" ],
                            "ExceptionHandling": 1,
                            "RuntimeTypeInfo": 'true'
                        }
                    },
                    "defines": [
                        "_WIN32",
                        "_WIN32_WINNT=0x0600",
                        "WIN32",
                        "WIN32_LEAN_AND_MEAN"
                    ],
                    "libraries": [
                        '-l<(openssl_root)/libeay32MT.lib',
                        '-l<(openssl_root)/ssleay32MT.lib',
                        '-ladvapi32',
                        '-liphlpapi',
                        '-llegacy_stdio_definitions'
                    ]
                }]
            ]
        }
    ]
}
