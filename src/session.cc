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
        { "add_torrent", nullptr, AddTorrent, nullptr, nullptr, 0, napi_default, 0 },
        { "pop_alerts", nullptr, PopAlerts, nullptr, nullptr, 0, napi_default, 0 },
        { "wait_for_alert", nullptr, WaitForAlert, nullptr, nullptr, 0, napi_default, 0}
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "Session", NAPI_AUTO_LENGTH, New, nullptr, 3, properties, &cons);
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

napi_value Session::PopAlerts(napi_env env, napi_callback_info callback_info)
{
    napi_value _this;
    Session* session;

    NAPI_CALL(env, napi_get_cb_info(env, callback_info, 0, nullptr, &_this, nullptr));
    NAPI_CALL(env, napi_unwrap(env, _this, reinterpret_cast<void**>(&session)));

    std::vector<libtorrent::alert*> alerts;
    session->session_->pop_alerts(&alerts);

    napi_value res;
    NAPI_CALL(env, napi_create_array_with_length(env, alerts.size(), &res));

    for (size_t i = 0; i < alerts.size(); i++)
    {
        libtorrent::alert* alert = alerts.at(i);

        napi_value obj;
        napi_value message;
        napi_value type;
        napi_value what;

        NAPI_CALL(env, napi_create_object(env, &obj));
        NAPI_CALL(env, napi_create_string_utf8(env, alert->message().c_str(), NAPI_AUTO_LENGTH, &message));
        NAPI_CALL(env, napi_create_int32(env, alert->type(), &type));
        NAPI_CALL(env, napi_create_string_utf8(env, alert->what(), NAPI_AUTO_LENGTH, &what));

        NAPI_CALL(env, napi_set_named_property(env, obj, "message", message));
        NAPI_CALL(env, napi_set_named_property(env, obj, "type", type));
        NAPI_CALL(env, napi_set_named_property(env, obj, "what", what));

        // Add alert to array at index
        NAPI_CALL(env, napi_set_element(env, res, i, obj));
    }

    return res;
}

struct AsyncRequest
{
    napi_ref callback_ref;
    bool result;
    Session* session;
    int32_t timeout;
    napi_async_work work;
};

void Session::WaitForAlertExecute(napi_env env, void* data)
{
    AsyncRequest* req = static_cast<AsyncRequest*>(data);
    auto alert = req->session->session_->wait_for_alert(libtorrent::milliseconds(req->timeout));
    req->result = (alert != nullptr);
}

void Session::WaitForAlertComplete(napi_env env, napi_status status, void* data)
{
    AsyncRequest* req = static_cast<AsyncRequest*>(data);

    napi_value callback;
    napi_get_reference_value(env, req->callback_ref, &callback);

    napi_value global;
    napi_get_global(env, &global);

    size_t argc = 2;
    napi_value argv[2];

    napi_get_null(env, &argv[0]);
    napi_get_boolean(env, req->result, &argv[1]);

    // Clean up
    napi_call_function(env, global, callback, argc, argv, nullptr);
    napi_delete_reference(env, req->callback_ref);
    napi_delete_async_work(env, req->work);

    delete req;
}

napi_value Session::WaitForAlert(napi_env env, napi_callback_info callback_info)
{
    size_t argc = 2;
    napi_value args[2];
    napi_value _this;
    NAPI_CALL(env, napi_get_cb_info(env, callback_info, &argc, args, &_this, nullptr));

    Session* session;
    napi_unwrap(env, _this, reinterpret_cast<void**>(&session));

    napi_value async_name;
    napi_create_string_utf8(env, "session.wait_for_alert", NAPI_AUTO_LENGTH, &async_name);

    AsyncRequest* req = new AsyncRequest();
    req->session = session;

    napi_create_reference(env, args[1], 1, &req->callback_ref);
    napi_get_value_int32(env, args[0], &req->timeout);

    napi_create_async_work(env, nullptr, async_name, WaitForAlertExecute, WaitForAlertComplete, req, &req->work);
    napi_queue_async_work(env, req->work);

    napi_value undef;
    napi_get_undefined(env, &undef);

    return undef;
}
