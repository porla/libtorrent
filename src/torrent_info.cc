#include "torrent_info.h"

#include <libtorrent/torrent_info.hpp>

#include "common.h"

using porla::TorrentInfo;

napi_ref TorrentInfo::constructor;

TorrentInfo::TorrentInfo(napi_env env, std::string const& filename)
    : env_(env),
    wrapper_(nullptr)
{
    ti_ = std::make_unique<libtorrent::torrent_info>(filename);
}

void TorrentInfo::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<TorrentInfo*>(native_obj);
}

napi_status TorrentInfo::Init(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] =
    {
        nullptr
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "TorrentInfo", NAPI_AUTO_LENGTH, New, nullptr, 0, nullptr, &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env, exports, "torrent_info", cons);
    if (status != napi_ok) return status;

    return napi_ok;
}

napi_value TorrentInfo::New(napi_env env, napi_callback_info callback_info)
{
    napi_value target;
    napi_get_new_target(env, callback_info, &target);

    if (target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
    }

    size_t argc = 1;
    napi_value args[1];
    napi_value _this;
    NAPI_CALL(env, napi_get_cb_info(env, callback_info, &argc, args, &_this, nullptr));

    napi_valuetype type;
    napi_typeof(env, args[0], &type);

    TorrentInfo* obj = nullptr;

    switch (type)
    {
    case napi_valuetype::napi_string:
    {
        char buffer[1024];
        size_t buffer_size = 1024;
        size_t copied;

        NAPI_CALL(env, napi_get_value_string_latin1(env, args[0], buffer, buffer_size, &copied));

        obj = new TorrentInfo(env, buffer);
        break;
    }
    default:
        napi_throw_error(env, nullptr, "Invalid argument type");
        return napi_value();
    }

    NAPI_CALL(env, napi_wrap(env, _this, obj, TorrentInfo::Destructor, nullptr, &obj->wrapper_));

    return _this;
}

libtorrent::torrent_info& TorrentInfo::Wrapped()
{
    return *ti_.get();
}
