#include "addtorrentparams.hpp"

#include <libtorrent/add_torrent_params.hpp>

#include "torrentinfo.hpp"

namespace lt = libtorrent;

lt::add_torrent_params AddTorrentParams::Unwrap(Napi::Env env, const Napi::Object &obj)
{
    lt::add_torrent_params params;
    if (obj.Has("name")) params.name = obj.Get("name").ToString();
    if (obj.Has("save_path")) params.save_path = obj.Get("save_path").ToString();

    if (obj.Has("ti"))
    {
        auto ti = Napi::ObjectWrap<TorrentInfo>::Unwrap(
            obj.Get("ti").As<Napi::Object>());
        params.ti = ti->GetWrapped();
    }

    return params;
}

Napi::Value AddTorrentParams::Wrap(Napi::Env env, const lt::add_torrent_params& params)
{
    Napi::Object p = Napi::Object::New(env);
    p.Set("name", Napi::String::New(env, params.name));
    p.Set("save_path", Napi::String::New(env, params.save_path));
    return p;
}
