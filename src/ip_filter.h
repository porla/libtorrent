#ifndef PORLA_LIBTORRENT_IPFILTER_H
#define PORLA_LIBTORRENT_IPFILTER_H

#include <libtorrent/ip_filter.hpp>
#include <node_api.h>

namespace porla
{
    class IpFilter
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);
        static napi_value New(napi_env env, napi_callback_info cbinfo);
        libtorrent::ip_filter& Wrapped();

        static napi_ref constructor;

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);

        static napi_value Access(napi_env env, napi_callback_info cbinfo);
        static napi_value AddRule(napi_env env, napi_callback_info cbinfo);
        static napi_value ExportFilter(napi_env env, napi_callback_info cbinfo);

        IpFilter(libtorrent::ip_filter const& th);

        napi_ref wrapper_;
        std::unique_ptr<libtorrent::ip_filter> ipf_;
    };
}

#endif
