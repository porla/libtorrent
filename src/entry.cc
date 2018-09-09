#include "entry.h"

#include <napi.h>

#include "common.h"

namespace lt = libtorrent;
using porla::Entry;

libtorrent::entry Entry::FromJson(napi_env env, napi_value value)
{
    Napi::Value v(env, value);

    if (v.IsNumber())
    {
        return lt::entry::integer_type(v.As<Napi::Number>().Int64Value());
    }

    if (v.IsBuffer())
    {
        auto buf = v.As<Napi::Buffer<char>>();
        return lt::entry::preformatted_type(buf.Data(), buf.Data() + buf.Length());
    }

    if (v.IsObject() && !v.IsArray())
    {
        lt::entry::dictionary_type dict;

        auto obj = v.As<Napi::Object>();
        auto propertyNames = obj.GetPropertyNames();

        for (uint32_t i = 0; i < propertyNames.Length(); i++)
        {
            auto prop = propertyNames.Get(i);
            auto item = obj.Get(prop);

            dict.insert({ prop.As<Napi::String>().Utf8Value(), FromJson(env, item) });
        }

        return dict;
    }

    if (v.IsString())
    {
        return v.As<Napi::String>().Utf8Value();
    }

    if (v.IsArray())
    {
        auto arr = v.As<Napi::Array>();
        lt::entry::list_type list;

        for (uint32_t i = 0; i < arr.Length(); i++)
        {
            auto item = arr.Get(i);
            list.push_back(FromJson(env, item));
        }

        return list;
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
        auto result = Napi::Object::New(env);

        for (auto const& p : dict)
        {
            result.Set(p.first, ToJson(env, p.second));
        }

        return result;
    }

    case libtorrent::entry::data_type::int_t:
    {
        auto integer = entry.integer();
        return Napi::Number::New(env, integer);
    }

    case libtorrent::entry::data_type::list_t:
    {
        auto list = entry.list();
        auto result = Napi::Array::New(env, list.size());

        for (size_t i = 0; i < list.size(); i++)
        {
            result.Set(i, ToJson(env, list.at(i)));
        }

        return result;
    }

    case libtorrent::entry::data_type::preformatted_t:
    {
        auto pref = entry.preformatted();
        return Napi::Buffer<char>::Copy(env, pref.data(), pref.size());
    }

    case libtorrent::entry::data_type::string_t:
    {
        return Napi::String::New(env, entry.string());
    }

    case libtorrent::entry::data_type::undefined_t:
    default:
    {
        napi_throw_error(env, nullptr, "Unknown type");
        return nullptr;
    }
    }
}
