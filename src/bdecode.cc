#include "bdecode.h"

#include <libtorrent/bdecode.hpp>
#include <vector>

#include "common.h"
#include "entry.h"

using porla::BDecode;

napi_status BDecode::Init(napi_env env, napi_value exports)
{
    std::vector<napi_property_descriptor> properties
    {
        PORLA_METHOD_DESCRIPTOR("bdecode", Decode),
    };

    return napi_define_properties(env, exports, properties.size(), properties.data());
}

napi_value BDecode::Decode(napi_env env, napi_callback_info cbinfo)
{
    // We don't actually have a wrap object, so don't use it.
    auto info = UnwrapCallback<BDecode>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    napi_valuetype type;
    napi_typeof(env, info.args[0], &type);
    bool isBuffer;
    napi_is_buffer(env, info.args[0], &isBuffer);

    if (type != napi_valuetype::napi_string && !isBuffer)
    {
        napi_throw_error(env, nullptr, "Expected a string or a buffer");
        return nullptr;
    }

    std::vector<char> buf;
    libtorrent::error_code ec;

    if (isBuffer)
    {
        char* data;
        size_t len;
        napi_get_buffer_info(env, info.args[0], reinterpret_cast<void**>(&data), &len);
        buf = std::vector<char>(data, data + len);
    }
    else
    {
        Value tmp(env, info.args[0]);
        std::string b = tmp.ToString();
        buf = std::vector<char>(b.begin(), b.end());
    }

    auto node = libtorrent::bdecode(buf, ec);

    if (ec)
    {
        napi_throw_error(env, nullptr, ec.message().c_str());
        return nullptr;
    }

    libtorrent::entry e;
    e = node;

    return Entry::ToJson(env, e);
}
