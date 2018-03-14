{
    "conditions": [
        [ 'OS=="win"', {
            'variables': {
                'boost_root%': 'C:/Libraries/boost_1_66_0',
            },

            'conditions': [
                ['target_arch=="x64"', {
                    'variables': {
                        'boostlib_root%': '<(boost_root)/lib64-msvc-14.0',
                        'libtorrent_root%': 'C:/Libraries/Rasterbar-libtorrent/msvc-14.0/x64',
                        'openssl_root%': 'C:/OpenSSL-Win64/lib/VC/static'
                    },
                }, {
                    'variables': {
                        'boostlib_root%': '<(boost_root)/lib32-msvc-14.0',
                        'libtorrent_root%': 'C:/Libraries/Rasterbar-libtorrent/msvc-14.0/x86',
                        'openssl_root%': 'C:/OpenSSL-Win32/lib/VC/static'
                    },
                }],
            ]
        }]
    ],

    "targets": [
        {
            "target_name": "<(module_name)",
            "sources":
            [
                "./src/porla-libtorrent.cc",
                "./src/session.cc",
                "./src/torrent_info.cc",
                "./src/torrent_handle.cc"
            ],
            "defines": [
                "BOOST_ALL_NO_LIB",
                "NAPI_BUILD_VERSION=<(napi_build_version)",
                "TORRENT_NO_DEPRECATE",
                "TORRENT_USE_OPENSSL"
            ],
            "conditions": [
                [ 'OS=="win"', {
                    'configurations': {
                        'Debug': {
                            'msvs_settings': {
                                'VCCLCompilerTool': {
                                    "ExceptionHandling": 1,
                                    "RuntimeTypeInfo": 'true'
                                }
                            }
                        }, # Debug
                        'Release': {
                            'msvs_settings': {
                                'VCCLCompilerTool': {
                                    "ExceptionHandling": 1,
                                    "RuntimeTypeInfo": 'true'
                                }
                            }
                        }
                    },
                    "defines": [
                        "_WIN32",
                        "_WIN32_WINNT=0x0600",
                        "WIN32",
                        "WIN32_LEAN_AND_MEAN"
                    ],
                    "include_dirs" : [
                        "<(libtorrent_root)/include",
                        '<(boost_root)/'
                    ],
                    "libraries": [
                        '-l<(boostlib_root)/libboost_system-vc140-mt-s-x64-1_66.lib',
                        '-l<(libtorrent_root)/lib/libtorrent.lib',
                        '-l<(openssl_root)/libeay32MT.lib',
                        '-l<(openssl_root)/ssleay32MT.lib',
                        '-liphlpapi',
                        '-llegacy_stdio_definitions'
                    ]
                },
                    'OS=="mac"', {
                    "libraries": [
                        "/usr/local/lib/libboost_system.a",
                        "$(HOME)/libtorrent/lib/libtorrent-rasterbar.a"
                    ]
                },
                    'OS=="linux"', {
                    "libraries": [
                        "$(HOME)/boost/lib/libboost_system.a",
                        "$(HOME)/libtorrent/lib/libtorrent-rasterbar.a"
                    ]
                }]
            ]
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": [ "<(module_name)" ],
            "copies": [
                {
                    "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
                    "destination": "<(module_path)"
                }
            ]
        }
    ]
}
