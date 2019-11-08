#include "ip_filter.h"

#include <boost/asio/ip/address.hpp>

#include "common.h"

using porla::IpFilter;

napi_ref IpFilter::constructor;

IpFilter::IpFilter(libtorrent::ip_filter const& filter)
    : wrapper_(nullptr)
{
    ipf_ = std::make_unique<libtorrent::ip_filter>(filter);
}

libtorrent::ip_filter& IpFilter::Wrapped()
{
    return *ipf_.get();
}

void IpFilter::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<IpFilter*>(native_obj);
}

napi_status IpFilter::Init(napi_env env, napi_value exports)
{
    std::vector<napi_property_descriptor> properties
    {
        PORLA_METHOD_DESCRIPTOR("access", Access),
        PORLA_METHOD_DESCRIPTOR("add_rule", AddRule),
        PORLA_METHOD_DESCRIPTOR("export_filter", ExportFilter)
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "IpFilter", NAPI_AUTO_LENGTH, New, nullptr, properties.size(), properties.data(), &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    return napi_ok;
}

napi_value IpFilter::New(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<IpFilter>(env, cbinfo);

    if (info.new_target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
        return nullptr;
    }

    libtorrent::ip_filter* filter;
    napi_get_value_external(env, info.args[0], reinterpret_cast<void**>(&filter));

    IpFilter* obj = new IpFilter(*filter);
    napi_wrap(env, info.this_arg, obj, IpFilter::Destructor, nullptr, &obj->wrapper_);

    return info.this_arg;
}

napi_value IpFilter::Access(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<IpFilter>(env, cbinfo);

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value addr(env, info.args[0]);

    auto parsed = boost::asio::ip::make_address(addr.ToString());
    auto access = info.wrap->ipf_->access(parsed);

    napi_value ret;
    napi_create_int32(env, access, &ret);

    return ret;
}

napi_value IpFilter::AddRule(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<IpFilter>(env, cbinfo);

    if (info.args.size() != 3)
    {
        napi_throw_error(env, nullptr, "Expected 3 arguments");
        return nullptr;
    }

    boost::system::error_code ec;

    auto first = boost::asio::ip::make_address(
        Value(env, info.args[0]).ToString(),
        ec);

    if (ec)
    {
        napi_throw_error(env, nullptr, ec.message().c_str());
        return nullptr;
    }

    auto last = boost::asio::ip::make_address(
        Value(env, info.args[1]).ToString(),
        ec);

    if (ec)
    {
        napi_throw_error(env, nullptr, ec.message().c_str());
        return nullptr;
    }

    int32_t flags = Value(env, info.args[2]).ToInt32();

    info.wrap->ipf_->add_rule(first, last, flags);

    return nullptr;
}

napi_value IpFilter::ExportFilter(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<IpFilter>(env, cbinfo);
    auto ex = info.wrap->ipf_->export_filter();
    auto v4 = std::get<0>(ex);
    auto v6 = std::get<1>(ex);

    napi_value v4_arr;
    napi_value v6_arr;
    napi_create_array_with_length(env, v4.size(), &v4_arr);
    napi_create_array_with_length(env, v6.size(), &v6_arr);

    for (size_t i = 0; i < v4.size(); i++)
    {
        napi_value obj;
        napi_create_object(env, &obj);

        Value v(env, obj);
        v.SetNamedProperty("first", v4.at(i).first.to_string().c_str());
        v.SetNamedProperty("flags", v4.at(i).flags);
        v.SetNamedProperty("last", v4.at(i).last.to_string().c_str());
    }

    for (size_t i = 0; i < v6.size(); i++)
    {
        napi_value obj;
        napi_create_object(env, &obj);

        Value v(env, obj);
        v.SetNamedProperty("first", v6.at(i).first.to_string().c_str());
        v.SetNamedProperty("flags", v6.at(i).flags);
        v.SetNamedProperty("last", v6.at(i).last.to_string().c_str());
    }

    napi_value val;
    napi_create_object(env, &val);
    napi_set_named_property(env, val, "v4", v4_arr);
    napi_set_named_property(env, val, "v6", v6_arr);

    return val;
}
