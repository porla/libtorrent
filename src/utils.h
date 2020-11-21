#ifndef PORLA_LIBTORRENT_UTILS_H
#define PORLA_LIBTORRENT_UTILS_H

#include <node_api.h>

namespace porla
{
    class Utils
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);

    private:
        static napi_value BEncode(napi_env env, napi_callback_info cbinfo);
        static napi_value GenerateFingerprint(napi_env env, napi_callback_info cbinfo);
        static napi_value HighPerformanceSeed(napi_env env, napi_callback_info cbinfo);
        static napi_value MinMemoryUsage(napi_env env, napi_callback_info cbinfo);
        static napi_value ParseMagnetUri(napi_env env, napi_callback_info cbinfo);
        static napi_value ReadResumeData(napi_env env, napi_callback_info cbinfo);
        static napi_value SessionStatsMetrics(napi_env env, napi_callback_info cbinfo);
        static napi_value WriteResumeData(napi_env env, napi_callback_info cbinfo);
        static napi_value WriteResumeDataBuf(napi_env env, napi_callback_info cbinfo);
        static napi_value WriteSessionParamsBuf(napi_env env, napi_callback_info cbinfo);
    };
}

#endif
