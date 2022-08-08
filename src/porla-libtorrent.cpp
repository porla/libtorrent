#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/read_resume_data.hpp>
#include <libtorrent/session_params.hpp>
#include <libtorrent/write_resume_data.hpp>

#include <napi.h>

#include "addtorrentparams.hpp"
#include "infohash.hpp"
#include "session.hpp"
#include "sessionparams.hpp"
#include "torrenthandle.hpp"
#include "torrentinfo.hpp"
#include "torrentstatus.hpp"

static Napi::Value ReadResumeData(const Napi::CallbackInfo& info)
{
    if (!info[0].IsBuffer())
    {
        throw Napi::Error::New(info.Env(), "Invalid argument. Expected buffer.");
    }

    auto buf = info[0].As<Napi::Buffer<char>>();

    return AddTorrentParams::Wrap(
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
    auto pm = AddTorrentParams::Unwrap(info.Env(), info[0].ToObject());
    auto buf = lt::write_resume_data_buf(pm);
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
    InfoHash::Init(env, exports);
    Session::Init(env, exports);
    SessionParams::Init(env, exports);
    TorrentHandle::Init(env, exports);
    TorrentInfo::Init(env, exports);
    TorrentStatus::Init(env, exports);

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

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
