#include "torrent_handle.h"

#include <sstream>

#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_status.hpp>

#include "common.h"

using porla::TorrentHandle;

napi_ref TorrentHandle::constructor;

TorrentHandle::TorrentHandle(napi_env env, libtorrent::torrent_handle const& th)
    : env_(env),
    wrapper_(nullptr)
{
    th_ = std::make_unique<libtorrent::torrent_handle>(th);
}

void TorrentHandle::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<TorrentHandle*>(native_obj);
}

napi_status TorrentHandle::Init(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] =
    {
        { "status", nullptr, Status, nullptr, nullptr, 0, napi_default, 0 }
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "TorrentHandle", NAPI_AUTO_LENGTH, New, nullptr, 1, properties, &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    /*status = napi_set_named_property(env, exports, "torrent_info", cons);
    if (status != napi_ok) return status;*/

    return napi_ok;
}

napi_value TorrentHandle::New(napi_env env, napi_callback_info callback_info)
{
    napi_value target;
    napi_get_new_target(env, callback_info, &target);

    if (target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
        return nullptr;
    }

    size_t argc = 1;
    napi_value args[1];
    napi_value _this;
    NAPI_CALL(env, napi_get_cb_info(env, callback_info, &argc, args, &_this, nullptr));

    libtorrent::torrent_handle* th;
    napi_get_value_external(env, args[0], reinterpret_cast<void**>(&th));

    TorrentHandle* obj = new TorrentHandle(env, *th);
    NAPI_CALL(env, napi_wrap(env, _this, obj, TorrentHandle::Destructor, nullptr, &obj->wrapper_));

    return _this;
}

napi_value TorrentHandle::Status(napi_env env, napi_callback_info callback_info)
{
    napi_value _this;
    NAPI_CALL(env, napi_get_cb_info(env, callback_info, nullptr, nullptr, &_this, nullptr));

    TorrentHandle* th;
    napi_unwrap(env, _this, reinterpret_cast<void**>(&th));

    libtorrent::torrent_status ts = th->th_->status();

    napi_value obj;
    napi_create_object(env, &obj);

    if (ts.errc)
    {
        napi_value value;
        napi_create_int32(env, ts.errc.value(), &value);

        napi_value message;
        napi_create_string_utf8(env, ts.errc.message().c_str(), NAPI_AUTO_LENGTH, &message);

        napi_value errc;
        napi_create_object(env, &errc);

        napi_set_named_property(env, errc, "message", message);
        napi_set_named_property(env, errc, "value", value);

        napi_set_named_property(env, obj, "errc", errc);
    }

    std::stringstream ss;
    ss << ts.info_hash;

    napi_value info_hash;
    napi_create_string_utf8(env, ss.str().c_str(), NAPI_AUTO_LENGTH, &info_hash);

    napi_value name;
    napi_create_string_utf8(env, ts.name.c_str(), NAPI_AUTO_LENGTH, &name);

    napi_value progress;
    napi_create_double(env, ts.progress, &progress);

    napi_value dl;
    napi_create_int32(env, ts.download_rate, &dl);

    napi_value state;
    napi_create_int32(env, ts.state, &state);

    napi_set_named_property(env, obj, "info_hash", info_hash);
    napi_set_named_property(env, obj, "name", name);
    napi_set_named_property(env, obj, "progress", progress);
    napi_set_named_property(env, obj, "download_rate", dl);
    napi_set_named_property(env, obj, "state", state);

    return obj;
}
