#ifndef PORLA_LIBTORRENT_SESSION_H
#define PORLA_LIBTORRENT_SESSION_H

#include <memory>
#include <node_api.h>

namespace libtorrent
{
    class session;
}

namespace porla
{
    class Session
    {
    public:
        static napi_status Init(napi_env env, napi_value exports);

    private:
        static void Destructor(napi_env env, void* native_obj, void* finalize_hint);
        static napi_value New(napi_env env, napi_callback_info callback_info);

        static napi_value AddTorrent(napi_env env, napi_callback_info callback_info);
        static napi_value PopAlerts(napi_env env, napi_callback_info callback_info);
        static napi_value WaitForAlert(napi_env env, napi_callback_info callback_info);
        static void WaitForAlertComplete(napi_env env, napi_status status, void* data);
        static void WaitForAlertExecute(napi_env env, void* data);

        static napi_ref constructor;

        Session(napi_env env);

        napi_env env_;
        napi_ref wrapper_;

        std::unique_ptr<libtorrent::session> session_;
    };
}

#endif
