#include "session.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_info.hpp>

#include "common.h"
#include "torrent_info.h"
#include "torrent_handle.h"

using porla::Session;

napi_ref Session::constructor;

napi_status LOG(napi_env env, napi_value val)
{
    napi_value global;
    napi_get_global(env, &global);

    napi_value console;
    napi_get_named_property(env, global, "console", &console);

    napi_value log;
    napi_get_named_property(env, console, "log", &log);

    napi_value args[1];
    args[0] = val;

    return napi_call_function(env, console, log, 1, args, nullptr);
}

napi_status LOG(napi_env env, const char* msg)
{
    napi_value val;
    napi_create_string_utf8(env, msg, NAPI_AUTO_LENGTH, &val);

    return LOG(env, val);
}

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
        { "add_torrent", nullptr, AddTorrent, nullptr, nullptr, 0, napi_default, 0 }
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "Session", NAPI_AUTO_LENGTH, New, nullptr, 1, properties, &cons);
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

napi_value Session::AddTorrent(napi_env env, napi_callback_info callback_info)
{
    size_t argc = 1;
    napi_value args[1];
    napi_value _this;
    NAPI_CALL(env, napi_get_cb_info(env, callback_info, &argc, args, &_this, nullptr));

    napi_valuetype type;
    napi_typeof(env, args[0], &type);

    if (type != napi_valuetype::napi_object)
    {
        napi_throw_error(env, nullptr, "Expected an [object] argument");
        return nullptr;
    }

    napi_value property_names;
    napi_get_property_names(env, args[0], &property_names);

    uint32_t len;
    napi_get_array_length(env, property_names, &len);

    libtorrent::add_torrent_params params;

    for (uint32_t i = 0; i < len; i++)
    {
        napi_value prop;
        napi_get_element(env, property_names, i, &prop);

        napi_value value;
        napi_get_property(env, args[0], prop, &value);
        
        char buf[1024];
        size_t size;
        NAPI_CALL(env, napi_get_value_string_utf8(env, prop, buf, 1024, &size));

        std::string propName(buf, size);

        if (propName == "save_path")
        {
            char sp_buffer[1024];
            size_t sp_size;
            NAPI_CALL(env, napi_get_value_string_utf8(env, value, sp_buffer, 1024, &sp_size));

            params.save_path = std::string(sp_buffer, sp_size);
        }
        else if (propName == "ti")
        {
            TorrentInfo* ti;
            napi_unwrap(env, value, reinterpret_cast<void**>(&ti));

            params.ti = std::make_shared<libtorrent::torrent_info>(ti->Wrapped());
        }
    }

    Session* session;
    napi_unwrap(env, _this, reinterpret_cast<void**>(&session));

    libtorrent::error_code ec;
    libtorrent::torrent_handle handle = session->session_->add_torrent(params, ec);

    if (ec)
    {
        napi_throw_error(env, nullptr, ec.message().c_str());
    }

    napi_value external;
    napi_create_external(env, &handle, nullptr, nullptr, &external);

    napi_value cons;
    NAPI_CALL(env, napi_get_reference_value(env, TorrentHandle::constructor, &cons));

    napi_value argv[] = { external };
    napi_value instance;
    NAPI_CALL(env, napi_new_instance(env, cons, 1, argv, &instance));

    return instance;
}
