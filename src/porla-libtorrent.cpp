#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/read_resume_data.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/session_params.hpp>
#include <libtorrent/write_resume_data.hpp>

#include <napi.h>

#include "addtorrentparams.hpp"
#include "infohash.hpp"
#include "session.hpp"
#include "sessionparams.hpp"
#include "settingspack.hpp"
#include "torrenthandle.hpp"
#include "torrentinfo.hpp"
#include "torrentstatus.hpp"

namespace lt = libtorrent;

static Napi::Value DefaultSettings(const Napi::CallbackInfo& info)
{
    return SettingsPack::Wrap(info.Env(), lt::default_settings());
}

static Napi::Value ParseMagnetUri(const Napi::CallbackInfo& info)
{
    return AddTorrentParams::New(
        info.Env(),
        lt::parse_magnet_uri(info[0].ToString().Utf8Value()));
}

static Napi::Value ReadResumeData(const Napi::CallbackInfo& info)
{
    if (!info[0].IsBuffer())
    {
        throw Napi::Error::New(info.Env(), "Invalid argument. Expected buffer.");
    }

    auto buf = info[0].As<Napi::Buffer<char>>();

    return AddTorrentParams::New(
        info.Env(),
        lt::read_resume_data(
            lt::span<const char>(
                buf.Data(),
                static_cast<long>(buf.Length()))));
}

static Napi::Value ReadSessionParams(const Napi::CallbackInfo& info)
{
    if (!info[0].IsBuffer())
    {
        throw Napi::Error::New(info.Env(), "Invalid argument. Expected buffer.");
    }

    auto buf = info[0].As<Napi::Buffer<char>>();

    return SessionParams::New(
        info.Env(),
        lt::read_session_params(
            lt::span<const char>(
                buf.Data(),
                static_cast<long>(buf.Length()))));
}

static Napi::Value WriteResumeDataBuf(const Napi::CallbackInfo& info)
{
    auto params = Napi::ObjectWrap<AddTorrentParams>::Unwrap(info[0].ToObject());
    auto buf = lt::write_resume_data_buf(static_cast<lt::add_torrent_params>(*params));
    return Napi::Buffer<char>::Copy(info.Env(), buf.data(), buf.size());
}

static Napi::Value WriteSessionParamsBuf(const Napi::CallbackInfo& info)
{
    // TODO: flags
    auto sp = Napi::ObjectWrap<SessionParams>::Unwrap(info[0].ToObject());
    auto buf = lt::write_session_params_buf(sp->GetWrapped());
    return Napi::Buffer<char>::Copy(info.Env(), buf.data(), buf.size());
}

static Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    AddTorrentParams::Init(env, exports);
    InfoHash::Init(env, exports);
    Session::Init(env, exports);
    SessionParams::Init(env, exports);
    TorrentHandle::Init(env, exports);
    TorrentInfo::Init(env, exports);
    TorrentStatus::Init(env, exports);

    exports.Set(
        "default_settings",
        Napi::Function::New(env, &DefaultSettings));

    exports.Set(
        "parse_magnet_uri",
        Napi::Function::New(env, &ParseMagnetUri));

    exports.Set(
        "read_resume_data",
        Napi::Function::New(env, &ReadResumeData));

    exports.Set(
        "read_session_params",
        Napi::Function::New(env, &ReadSessionParams));

    exports.Set(
        "write_resume_data_buf",
        Napi::Function::New(env, &WriteResumeDataBuf));

    exports.Set(
        "write_session_params_buf",
        Napi::Function::New(env, &WriteSessionParamsBuf));

    auto move_flags_t = Napi::Object::New(env);
    move_flags_t["always_replace_files"] = Napi::Number::New(env, static_cast<uint8_t>(lt::move_flags_t::always_replace_files));
    move_flags_t["fail_if_exist"] = Napi::Number::New(env, static_cast<uint8_t>(lt::move_flags_t::fail_if_exist));
    move_flags_t["dont_replace"] = Napi::Number::New(env, static_cast<uint8_t>(lt::move_flags_t::dont_replace));

    auto pause_flags_t = Napi::Object::New(env);
    pause_flags_t["graceful_pause"] = Napi::Number::New(env, static_cast<uint8_t>(lt::torrent_handle::graceful_pause));

    auto remove_flags_t = Napi::Object::New(env);
    remove_flags_t["delete_files"] = Napi::Number::New(env, static_cast<uint8_t>(lt::session::delete_files));
    remove_flags_t["delete_partfile"] = Napi::Number::New(env, static_cast<uint8_t>(lt::session::delete_partfile));

    auto resume_data_flags_t = Napi::Object::New(env);
    resume_data_flags_t["flush_disk_cache"] = Napi::Number::New(env, static_cast<uint8_t>(lt::torrent_handle::flush_disk_cache));
    resume_data_flags_t["save_info_dict"] = Napi::Number::New(env, static_cast<uint8_t>(lt::torrent_handle::save_info_dict));
    resume_data_flags_t["only_if_modified"] = Napi::Number::New(env, static_cast<uint8_t>(lt::torrent_handle::only_if_modified));

    auto torrent_flags_t = Napi::Object::New(env);
    torrent_flags_t["seed_mode"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::seed_mode));
    torrent_flags_t["upload_mode"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::upload_mode));
    torrent_flags_t["share_mode"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::share_mode));
    torrent_flags_t["apply_ip_filter"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::apply_ip_filter));
    torrent_flags_t["paused"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::paused));
    torrent_flags_t["auto_managed"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::auto_managed));
    torrent_flags_t["duplicate_is_error"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::duplicate_is_error));
    torrent_flags_t["update_subscribe"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::update_subscribe));
    torrent_flags_t["super_seeding"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::super_seeding));
    torrent_flags_t["sequential_download"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::sequential_download));
    torrent_flags_t["stop_when_ready"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::stop_when_ready));
    torrent_flags_t["override_trackers"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::override_trackers));
    torrent_flags_t["override_web_seeds"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::override_web_seeds));
    torrent_flags_t["need_save_resume"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::need_save_resume));
    torrent_flags_t["disable_dht"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::disable_dht));
    torrent_flags_t["disable_lsd"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::disable_lsd));
    torrent_flags_t["disable_pex"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::disable_pex));
    torrent_flags_t["no_verify_files"] = Napi::Number::New(env, static_cast<uint64_t>(lt::torrent_flags::no_verify_files));

    exports.Set("move_flags_t", move_flags_t);
    exports.Set("pause_flags_t", pause_flags_t);
    exports.Set("remove_flags_t", remove_flags_t);
    exports.Set("resume_data_flags_t", resume_data_flags_t);
    exports.Set("torrent_flags_t", torrent_flags_t);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
