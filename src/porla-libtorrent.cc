#include <napi.h>

#include "add_torrent_params.h"
#include "bdecode.h"
#include "create_torrent.h"
#include "file_storage.h"
#include "ip_filter.h"
#include "session.h"
#include "torrent_info.h"
#include "torrent_handle.h"
#include "torrent_status.h"
#include "utils.h"

#ifdef WIN32
// TODO: Ugly hack
FILE _iob[] = { *stdin, *stdout, *stderr }; 
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    porla::AddTorrentParams::Init(env, exports);
    porla::BDecode::Init(env, exports);
    porla::CreateTorrent::Init(env, exports);
    porla::FileStorage::Init(env, exports);
    porla::IpFilter::Init(env, exports);
    porla::Session::Init(env, exports);
    porla::TorrentInfo::Init(env, exports);
    porla::TorrentHandle::Init(env, exports);
    porla::TorrentStatus::Init(env, exports);
    porla::Utils::Init(env, exports);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
