#include "session.h"

#include <libtorrent/session.hpp>

#include "common.h"

using porla::Session;

napi_ref Session::constructor;

Session::Session(napi_env env)
    : env_(env),
    wrapper_(nullptr)
{
    session_ = std::make_unique<libtorrent::session>();
}

void Session::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<Session*>(native_obj);
}

napi_status Session::Init(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] =
    {
        nullptr
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "Session", NAPI_AUTO_LENGTH, New, nullptr, 0, nullptr, &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env, exports, "session", cons);
    if (status != napi_ok) return status;

    return napi_ok;
}

napi_value Session::New(napi_env env, napi_callback_info callback_info)
{
    napi_value target;
    napi_get_new_target(env, callback_info, &target);

    if (target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
    }

    napi_value _this;
    NAPI_CALL(env, napi_get_cb_info(env, callback_info, 0, nullptr, &_this, nullptr));

    Session* obj = new Session(env);
    NAPI_CALL(env, napi_wrap(env, _this, obj, Session::Destructor, nullptr, &obj->wrapper_));

    return _this;
}
