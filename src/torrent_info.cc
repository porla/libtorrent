#include "torrent_info.h"

#include <libtorrent/torrent_info.hpp>

#include "common.h"

namespace lt = libtorrent;
using porla::TorrentInfo;

napi_ref TorrentInfo::constructor;

TorrentInfo::TorrentInfo(std::shared_ptr<lt::torrent_info> ti)
    : wrapper_(nullptr)
{
    ti_ = ti;
}

TorrentInfo::TorrentInfo(std::string const& filename, libtorrent::error_code& ec)
    : wrapper_(nullptr)
{
    ti_ = std::make_shared<lt::torrent_info>(filename, ec);
}

TorrentInfo::TorrentInfo(const char* buf, size_t len, libtorrent::error_code& ec)
    : wrapper_(nullptr)
{
    ti_ = std::make_shared<lt::torrent_info>(buf, len, ec);
}

void TorrentInfo::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<TorrentInfo*>(native_obj);
}

napi_status TorrentInfo::Init(napi_env env, napi_value exports)
{
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

napi_value TorrentInfo::New(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<TorrentInfo>(env, cbinfo);

    if (info.new_target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
        return nullptr;
    }

    napi_valuetype type;
    napi_typeof(env, info.args[0], &type);

    TorrentInfo* obj = nullptr;

    switch (type)
    {
    case napi_valuetype::napi_string:
    {
        Value v(env, info.args[0]);

        libtorrent::error_code ec;
        obj = new TorrentInfo(v.ToString(), ec);

        if (ec)
        {
            napi_throw_error(env, nullptr, ec.message().c_str());
            return nullptr;
        }

        break;
    }
    case napi_external:
    {
        std::shared_ptr<lt::torrent_info>* ti;
        napi_get_value_external(env, info.args[0], reinterpret_cast<void**>(&ti));
        obj = new TorrentInfo(*ti);
        break;
    }
    default:
    {
        bool isBuffer;
        napi_is_buffer(env, info.args[0], &isBuffer);

        if (isBuffer)
        {
            char* buf;
            size_t len;
            napi_get_buffer_info(env, info.args[0], reinterpret_cast<void**>(&buf), &len);

            libtorrent::error_code ec;
            obj = new TorrentInfo(buf, len, ec);

            break;
        }

        napi_throw_error(env, nullptr, "Invalid argument type");
        return nullptr;
    }
    }

    napi_wrap(env, info.this_arg, obj, TorrentInfo::Destructor, nullptr, &obj->wrapper_);

    return info.this_arg;
}

std::shared_ptr<lt::torrent_info> TorrentInfo::Wrapped()
{
    return ti_;
}
