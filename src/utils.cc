#include "utils.h"

#include <napi.h>

#include <libtorrent/fingerprint.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/read_resume_data.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/session_handle.hpp>
#include <libtorrent/session_params.hpp>
#include <libtorrent/session_stats.hpp>
#include <libtorrent/write_resume_data.hpp>
#include <vector>

#include "add_torrent_params.h"
#include "common.h"
#include "entry.h"
#include "session_params.h"
#include "settings_pack.h"

namespace lt = libtorrent;
using porla::Utils;

class Dummy {};

napi_status Utils::Init(napi_env env, napi_value exports)
{
    // Download priority
    napi_value download_priority;
    napi_create_object(env, &download_priority);

    Value v(env, download_priority);
    v.SetNamedProperty("dont_download", static_cast<uint8_t>(lt::dont_download));
    v.SetNamedProperty("default_priority", static_cast<uint8_t>(lt::default_priority));
    v.SetNamedProperty("low_priority", static_cast<uint8_t>(lt::low_priority));
    v.SetNamedProperty("top_priority", static_cast<uint8_t>(lt::top_priority));

    // Save state flags
    napi_value save_state_flags;
    napi_create_object(env, &save_state_flags);

    Value ssf(env, save_state_flags);
    ssf.SetNamedProperty("save_dht_state", static_cast<uint32_t>(lt::session::save_dht_state));
    ssf.SetNamedProperty("save_settings", static_cast<uint32_t>(lt::session::save_settings));

    // Alert mask
    napi_value alert;
    napi_create_object(env, &alert);

    Value a(env, alert);
    a.SetNamedProperty("all_categories", static_cast<uint32_t>(lt::alert::all_categories));
    a.SetNamedProperty("block_progress_notification", static_cast<uint32_t>(lt::alert::block_progress_notification));
    a.SetNamedProperty("connect_notification", static_cast<uint32_t>(lt::alert::connect_notification));
    a.SetNamedProperty("dht_log_notification", static_cast<uint32_t>(lt::alert::dht_log_notification));
    a.SetNamedProperty("dht_notification", static_cast<uint32_t>(lt::alert::dht_notification));
    a.SetNamedProperty("dht_operation_notification", static_cast<uint32_t>(lt::alert::dht_operation_notification));
    a.SetNamedProperty("error_notification", static_cast<uint32_t>(lt::alert::error_notification));
    a.SetNamedProperty("file_progress_notification", static_cast<uint32_t>(lt::alert::file_progress_notification));
    a.SetNamedProperty("incoming_request_notification", static_cast<uint32_t>(lt::alert::incoming_request_notification));
    a.SetNamedProperty("ip_block_notification", static_cast<uint32_t>(lt::alert::ip_block_notification));
    a.SetNamedProperty("peer_log_notification", static_cast<uint32_t>(lt::alert::peer_log_notification));
    a.SetNamedProperty("peer_notification", static_cast<uint32_t>(lt::alert::peer_notification));
    a.SetNamedProperty("performance_warning", static_cast<uint32_t>(lt::alert::performance_warning));
    a.SetNamedProperty("picker_log_notification", static_cast<uint32_t>(lt::alert::picker_log_notification));
    a.SetNamedProperty("piece_progress_notification", static_cast<uint32_t>(lt::alert::piece_progress_notification));
    a.SetNamedProperty("port_mapping_log_notification", static_cast<uint32_t>(lt::alert::port_mapping_log_notification));
    a.SetNamedProperty("port_mapping_notification", static_cast<uint32_t>(lt::alert::port_mapping_notification));
    a.SetNamedProperty("session_log_notification", static_cast<uint32_t>(lt::alert::session_log_notification));
    a.SetNamedProperty("status_notification", static_cast<uint32_t>(lt::alert::status_notification));
    a.SetNamedProperty("storage_notification", static_cast<uint32_t>(lt::alert::storage_notification));
    a.SetNamedProperty("torrent_log_notification", static_cast<uint32_t>(lt::alert::torrent_log_notification));
    a.SetNamedProperty("tracker_notification", static_cast<uint32_t>(lt::alert::tracker_notification));
    a.SetNamedProperty("upload_notification", static_cast<uint32_t>(lt::alert::upload_notification));

    std::vector<napi_property_descriptor> properties
    {
        PORLA_METHOD_DESCRIPTOR("bencode", BEncode),
        PORLA_METHOD_DESCRIPTOR("generate_fingerprint", GenerateFingerprint),
        PORLA_METHOD_DESCRIPTOR("high_performance_seed", HighPerformanceSeed),
        PORLA_METHOD_DESCRIPTOR("min_memory_usage", MinMemoryUsage),
        PORLA_VALUE_DESCRIPTOR("download_priority", download_priority),
        PORLA_VALUE_DESCRIPTOR("alert", alert),
        PORLA_METHOD_DESCRIPTOR("parse_magnet_uri", ParseMagnetUri),
        PORLA_VALUE_DESCRIPTOR("save_state_flags", save_state_flags),
        PORLA_METHOD_DESCRIPTOR("read_resume_data", ReadResumeData),
        PORLA_METHOD_DESCRIPTOR("session_stats_metrics", SessionStatsMetrics),
        PORLA_METHOD_DESCRIPTOR("write_resume_data", WriteResumeData),
        PORLA_METHOD_DESCRIPTOR("write_resume_data_buf", WriteResumeDataBuf),
        PORLA_METHOD_DESCRIPTOR("write_session_params_buf", WriteSessionParamsBuf)
    };

    return napi_define_properties(env, exports, properties.size(), properties.data());
}

napi_value Utils::BEncode(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Dummy>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    auto entry = Entry::FromJson(env, info.args[0]);

    std::vector<char> buf;
    lt::bencode(std::back_inserter(buf), entry);

    napi_value val;
    char* data;
    napi_create_buffer(env, buf.size(), reinterpret_cast<void**>(&data), &val);

    std::copy(buf.begin(), buf.end(), data);

    return val;
}

napi_value Utils::GenerateFingerprint(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Dummy>(env, cbinfo);

    if (info.args.size() < 2)
    {
        napi_throw_error(env, nullptr, "Expected at least 2 arguments");
        return nullptr;
    }

    Value name(env, info.args[0]);
    Value maj(env, info.args[1]);
    int minor = 0;
    int rev = 0;
    int tag = 0;

    if (info.args.size() > 2)
    {
        Value v(env, info.args[2]);
        minor = v.ToInt32();
    }

    if (info.args.size() > 3)
    {
        Value v(env, info.args[3]);
        rev = v.ToInt32();
    }

    if (info.args.size() > 4)
    {
        Value v(env, info.args[4]);
        tag = v.ToInt32();
    }

    auto fingerprint = lt::generate_fingerprint(name.ToString(), maj.ToInt32(), minor, rev, tag);

    napi_value ret;
    napi_create_string_utf8(env, fingerprint.c_str(), fingerprint.size(), &ret);

    return ret;
}

napi_value Utils::HighPerformanceSeed(napi_env env, napi_callback_info cbinfo)
{
    return SettingsPack::Objectify(env, lt::high_performance_seed());
}

napi_value Utils::MinMemoryUsage(napi_env env, napi_callback_info cbinfo)
{
    return SettingsPack::Objectify(env, lt::min_memory_usage());
}

napi_value Utils::ParseMagnetUri(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Dummy>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Napi::Value v(env, info.args[0]);
    auto params = lt::parse_magnet_uri(v.ToString().Utf8Value());
    auto arg = Napi::External<lt::add_torrent_params>::New(env, &params);

    return AddTorrentParams::NewInstance(arg);
}

napi_value Utils::ReadResumeData(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Dummy>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    lt::add_torrent_params params;
    lt::error_code ec;

    Napi::Value v(env, info.args[0]);

    if (v.IsBuffer())
    {
        auto b = v.As<Napi::Buffer<char>>();
        std::vector<char> buf(b.Data(), b.Data() + b.Length());
        params = lt::read_resume_data(buf, ec);
    }
    else
    {
        auto entry = Entry::FromJson(env, info.args[0]);
        std::vector<char> buf;
        lt::bencode(std::back_inserter(buf), entry);
        params = lt::read_resume_data(buf, ec);
    }

    if (ec)
    {
        napi_throw_error(env, nullptr, ec.message().c_str());
        return nullptr;
    }

    auto arg = Napi::External<lt::add_torrent_params>::New(env, &params);
    return AddTorrentParams::NewInstance(arg);
}

napi_value Utils::SessionStatsMetrics(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Dummy>(env, cbinfo);
    auto metrics = lt::session_stats_metrics();
    auto res = Napi::Array::New(env, metrics.size());

    for (size_t i = 0; i < metrics.size(); i++)
    {
        auto mtr = Napi::Object::New(env);
        mtr.Set("name", Napi::String::New(env, metrics.at(i).name));
        mtr.Set("type", Napi::Number::New(env, static_cast<int32_t>(metrics.at(i).type)));
        mtr.Set("value_index", Napi::Number::New(env, metrics.at(i).value_index));

        res.Set(i, mtr);
    }

    return res;
}

napi_value Utils::WriteResumeData(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Dummy>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    auto params = v.Unwrap<AddTorrentParams>();
    auto entry = lt::write_resume_data(params->Wrapped());

    return Entry::ToJson(env, entry);
}

napi_value Utils::WriteResumeDataBuf(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Dummy>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    auto params = v.Unwrap<AddTorrentParams>();
    auto buf = lt::write_resume_data_buf(params->Wrapped());

    napi_value val;
    char* data;
    napi_create_buffer(env, buf.size(), reinterpret_cast<void**>(&data), &val);

    std::copy(buf.begin(), buf.end(), data);

    return val;
}

napi_value Utils::WriteSessionParamsBuf(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<Dummy>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    auto params = v.Unwrap<SessionParams>();
    auto buf = lt::write_session_params_buf(params->Wrapped());

    napi_value val;
    char* data;
    napi_create_buffer(env, buf.size(), reinterpret_cast<void**>(&data), &val);

    std::copy(buf.begin(), buf.end(), data);

    return val;
}
