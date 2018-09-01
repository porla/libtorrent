#include "entry.h"

#include "common.h"

using porla::Entry;

libtorrent::entry Entry::FromJson(napi_env env, napi_value value)
{
    napi_valuetype type;
    napi_typeof(env, value, &type);

    if (type == napi_number)
    {
        int64_t res;
        napi_get_value_int64(env, value, &res);

        return libtorrent::entry::integer_type(res);
    }

    return libtorrent::entry();
}

napi_value Entry::ToJson(napi_env env, libtorrent::entry const& entry)
{
    switch (entry.type())
    {
    case libtorrent::entry::data_type::dictionary_t:
    {
        auto dict = entry.dict();

        napi_value result;
        napi_create_object(env, &result);

        for (auto const& p : dict)
        {
            napi_set_named_property(
                env,
                result,
                p.first.data(),
                ToJson(env, p.second));
        }

        return result;
    }

    case libtorrent::entry::data_type::int_t:
    {
        auto integer = entry.integer();

        napi_value result;
        napi_create_int64(env, integer, &result);

        return result;
    }

    case libtorrent::entry::data_type::list_t:
    {
        auto list = entry.list();

        napi_value result;
        napi_create_array_with_length(env, list.size(), &result);

        for (size_t i = 0; i < list.size(); i++)
        {
            napi_set_element(
                env,
                result,
                i,
                ToJson(env, list.at(i)));
        }

        return result;
    }

    case libtorrent::entry::data_type::preformatted_t:
    {
        auto pref = entry.preformatted();

        char* data;
        napi_value result;
        napi_create_buffer(env, pref.size(), reinterpret_cast<void**>(&data), &result);

        std::copy(pref.begin(), pref.end(), data);

        return result;
    }

    case libtorrent::entry::data_type::string_t:
    {
        auto string = entry.string();

        napi_value result;
        napi_create_string_utf8(env, string.data(), string.size(), &result);

        return result;
    }

    case libtorrent::entry::data_type::undefined_t:
    default:
    {
        napi_throw_error(env, nullptr, "Unknown type");
        return nullptr;
    }
    }
}
