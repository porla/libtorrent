#include <napi.h>

#include "infohash.hpp"
#include "session.hpp"
#include "torrenthandle.hpp"
#include "torrentinfo.hpp"
#include "torrentstatus.hpp"

static Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    InfoHash::Init(env, exports);
    Session::Init(env, exports);
    TorrentHandle::Init(env, exports);
    TorrentInfo::Init(env, exports);
    TorrentStatus::Init(env, exports);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
