#include <node_api.h>

#include "bdecode.h"
#include "ip_filter.h"
#include "session.h"
#include "torrent_info.h"
#include "torrent_handle.h"
#include "torrent_status.h"

#ifdef WIN32
// TODO: Ugly hack
FILE _iob[] = { *stdin, *stdout, *stderr }; 
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif

napi_value Init(napi_env env, napi_value exports) {
    porla::BDecode::Init(env, exports);
    porla::IpFilter::Init(env, exports);
    porla::Session::Init(env, exports);
    porla::TorrentInfo::Init(env, exports);
    porla::TorrentHandle::Init(env, exports);
    porla::TorrentStatus::Init(env, exports);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
