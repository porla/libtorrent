#include "add_torrent_params.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_info.hpp>

#include "common.h"
#include "torrent_info.h"

using porla::AddTorrentParams;

napi_ref AddTorrentParams::constructor;

AddTorrentParams::AddTorrentParams()
    : wrapper_(nullptr)
{
    p_ = std::make_unique<libtorrent::add_torrent_params>();
}

AddTorrentParams::AddTorrentParams(libtorrent::add_torrent_params const& params)
    : wrapper_(nullptr)
{
    p_ = std::make_unique<libtorrent::add_torrent_params>(params);
}

void AddTorrentParams::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<AddTorrentParams*>(native_obj);
}

napi_status AddTorrentParams::Init(napi_env env, napi_value exports)
{
    std::vector<napi_property_descriptor> properties
    {
        PORLA_GETSET_DESCRIPTOR("save_path", Get_SavePath, Set_SavePath),
        PORLA_GETSET_DESCRIPTOR("ti", Get_TorrentInfo, Set_TorrentInfo)
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "AddTorrentParams", NAPI_AUTO_LENGTH, New, nullptr, properties.size(), properties.data(), &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env, exports, "add_torrent_params", cons);
    if (status != napi_ok) return status;

    return napi_ok;
}

napi_value AddTorrentParams::New(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<AddTorrentParams>(env, cbinfo);

    if (info.new_target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
        return nullptr;
    }

    AddTorrentParams* obj = nullptr;

    if (info.args.size() > 0)
    {
        libtorrent::add_torrent_params* p;
        napi_get_value_external(env, info.args[0], reinterpret_cast<void**>(&p));
        obj = new AddTorrentParams(*p);
    }
    else
    {
        obj = new AddTorrentParams();
    }

    napi_wrap(env, info.this_arg, obj, AddTorrentParams::Destructor, nullptr, &obj->wrapper_);

    return info.this_arg;
}

libtorrent::add_torrent_params& AddTorrentParams::Wrapped()
{
    return *p_.get();
}

napi_value AddTorrentParams::Get_SavePath(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<AddTorrentParams>(env, cbinfo);

    napi_value sp;
    napi_create_string_utf8(env, info.wrap->p_->save_path.c_str(), NAPI_AUTO_LENGTH, &sp);

    return sp;
}

napi_value AddTorrentParams::Get_TorrentInfo(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<AddTorrentParams>(env, cbinfo);
    auto ti = info.wrap->p_->ti;

    if (ti)
    {
        return WrapExternal<TorrentInfo, std::shared_ptr<lt::torrent_info>>(env, &ti);
    }

    return nullptr;
}

napi_value AddTorrentParams::Set_SavePath(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<AddTorrentParams>(env, cbinfo);

    Value v(env, info.args[0]);
    info.wrap->p_->save_path = v.ToString();

    return nullptr;
}

napi_value AddTorrentParams::Set_TorrentInfo(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<AddTorrentParams>(env, cbinfo);

    Value v(env, info.args[0]);
    info.wrap->p_->ti = v.Unwrap<TorrentInfo>()->Wrapped();

    return nullptr;
}

