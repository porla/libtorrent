#include "common.h"

using porla::UnwrapCallback;
using porla::Value;

Value::Value(napi_env env, napi_value val)
    : env_(env), value_(val)
{
}

Value Value::GetArrayItem(uint32_t idx)
{
    napi_value element;
    napi_get_element(env_, value_, idx, &element);
    return Value(env_, element);
}

uint32_t Value::GetArrayLength()
{
    uint32_t len;
    napi_get_array_length(env_, value_, &len);
    return len;
}

Value Value::GetNamedProperty(const char* propertyName)
{
    napi_value prop;
    napi_get_named_property(env_, value_, propertyName, &prop);
    return Value(env_, prop);
}

Value Value::GetPropertyNames()
{
    napi_value props;
    napi_get_property_names(env_, value_, &props);
    return Value(env_, props);
}

bool Value::HasNamedProperty(const char* propertyName)
{
    napi_value key;
    napi_create_string_utf8(env_, propertyName, NAPI_AUTO_LENGTH, &key);

    bool result;
    napi_has_own_property(env_, value_, key, &result);

    return result;
}

void Value::SetNamedProperty(const char* propertyName, bool value)
{
    napi_value v;
    napi_get_boolean(env_, value, &v);
    napi_set_named_property(env_, value_, propertyName, v);
}

void Value::SetNamedProperty(const char* propertyName, int32_t value)
{
    napi_value v;
    napi_create_int32(env_, value, &v);
    napi_set_named_property(env_, value_, propertyName, v);
}

void Value::SetNamedProperty(const char* propertyName, int64_t value)
{
    napi_value v;
    napi_create_int64(env_, value, &v);
    napi_set_named_property(env_, value_, propertyName, v);
}

void Value::SetNamedProperty(const char* propertyName, std::string const& value)
{
    napi_value v;
    napi_create_string_utf8(env_, value.c_str(), NAPI_AUTO_LENGTH, &v);
    napi_set_named_property(env_, value_, propertyName, v);
}

void Value::SetNamedProperty(const char* propertyName, uint32_t value)
{
    napi_value v;
    napi_create_uint32(env_, value, &v);
    napi_set_named_property(env_, value_, propertyName, v);
}

bool Value::ToBool()
{
    bool result;
    napi_get_value_bool(env_, value_, &result);
    return result;
}

int32_t Value::ToInt32()
{
    int32_t val;
    napi_get_value_int32(env_, value_, &val);
    return val;
}

std::string Value::ToString()
{
    char str[1024];
    size_t sz;
    napi_get_value_string_utf8(env_, value_, str, 1024, &sz);

    return std::string(str, sz);
}

uint32_t Value::ToUInt32()
{
    uint32_t val;
    napi_get_value_uint32(env_, value_, &val);
    return val;
}
