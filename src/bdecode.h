#ifndef PORLA_LIBTORRENT_BDECODE_H
#define PORLA_LIBTORRENT_BDECODE_H

#include <node_api.h>

namespace porla
{
    class BDecode
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);

    private:
        static napi_value Decode(napi_env env, napi_callback_info cbinfo);
    };
}

#endif
