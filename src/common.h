#pragma once

#include <node_api.h>

#include <string>
#include <vector>

// Empty value so that macros here are able to return NULL or void
#define NAPI_RETVAL_NOTHING  // Intentionally blank #define

#define PORLA_METHOD_DESCRIPTOR(name, function) \
    { name, nullptr, function, nullptr, nullptr, 0, napi_default, 0 }

#define PORLA_GETTER_DESCRIPTOR(name, function) \
    { name, nullptr, nullptr, function, nullptr, 0, napi_enumerable, 0 }

#define PORLA_GETSET_DESCRIPTOR(name, getter, setter) \
    { name, nullptr, nullptr, getter, setter, 0, napi_enumerable, 0 }

#define PORLA_VALUE_DESCRIPTOR(name, value) \
    { name, nullptr, nullptr, nullptr, nullptr, value, napi_default, 0 }

namespace porla
{
    template<typename T>
    struct Unwrapped
    {
        napi_value env;
        napi_value this_arg;
        napi_value new_target;
        std::vector<napi_value> args;
        T* wrap;
    };

    class Console
    {
    public:
        static napi_status Log(napi_env env, napi_value value)
        {
            napi_value global;
            napi_get_global(env, &global);

            napi_value console;
            napi_get_named_property(env, global, "console", &console);

            napi_value log;
            napi_get_named_property(env, console, "log", &log);

            napi_value args[1];
            args[0] = value;

            return napi_call_function(env, console, log, 1, args, nullptr);
        }
    };

    class Value
    {
    public:
        Value(napi_env env, napi_value val);

        Value GetArrayItem(uint32_t idx);
        uint32_t GetArrayLength();
        Value GetNamedProperty(const char* propertyName);

        bool GetNamedProperty(const char* propertyName, bool* target)
        {
            if (!HasNamedProperty(propertyName))
            {
                return false;
            }

            auto v = GetNamedProperty(propertyName);
            *target = v.ToBool();
            return true;
        }

        bool GetNamedProperty(const char* propertyName, int32_t* target)
        {
            if (!HasNamedProperty(propertyName))
            {
                return false;
            }

            auto v = GetNamedProperty(propertyName);
            *target = v.ToInt32();
            return true;
        }

        bool GetNamedProperty(const char* propertyName, std::string* target)
        {
            if (!HasNamedProperty(propertyName))
            {
                return false;
            }

            auto v = GetNamedProperty(propertyName);
            *target = v.ToString();
            return true;
        }

        Value GetPropertyNames();
        bool HasNamedProperty(const char* propertyName);
        void SetNamedProperty(const char* propertyName, bool value);
        void SetNamedProperty(const char* propertyName, int32_t value);
        void SetNamedProperty(const char* propertyName, int64_t value);
        void SetNamedProperty(const char* propertyName, std::string const& value);
        void SetNamedProperty(const char* propertyName, uint32_t value);
        void SetNamedProperty(const char* propertyName, uint64_t value);
        bool ToBool();
        int32_t ToInt32();
        std::string ToString();
        uint32_t ToUInt32();

        template<typename T>
        T* Unwrap()
        {
            T* val;
            napi_unwrap(env_, value_, reinterpret_cast<void**>(&val));
            return val;
        }

    private:
        napi_env env_;
        napi_value value_;
    };

    template<typename T>
    static Unwrapped<T> UnwrapCallback(napi_env env, napi_callback_info cbinfo)
    {
        Unwrapped<T> unwrapped;

        // Get arg count
        size_t argCount = 0;
        napi_get_cb_info(env, cbinfo, &argCount, nullptr, nullptr, nullptr);

        // Resize args to fit
        unwrapped.args.resize(argCount);

        napi_get_new_target(env, cbinfo, &unwrapped.new_target);
        napi_get_cb_info(env, cbinfo, &argCount, &unwrapped.args[0], &unwrapped.this_arg, nullptr);
        napi_unwrap(env, unwrapped.this_arg, reinterpret_cast<void**>(&unwrapped.wrap));

        return unwrapped;
    }

    template<typename T, typename U>
    static napi_value WrapExternal(napi_env env, U* data)
    {
        napi_value external;
        napi_create_external(env, data, nullptr, nullptr, &external);

        napi_value cons;
        napi_get_reference_value(env, T::constructor, &cons);

        napi_value argv[] = { external };
        napi_value instance;

        napi_new_instance(env, cons, 1, argv, &instance);

        return instance;
    }
}

#define GET_AND_THROW_LAST_ERROR(env)                                    \
  do {                                                                   \
    const napi_extended_error_info *error_info;                          \
    napi_get_last_error_info((env), &error_info);                        \
    bool is_pending;                                                     \
    napi_is_exception_pending((env), &is_pending);                       \
    /* If an exception is already pending, don't rethrow it */           \
    if (!is_pending) {                                                   \
      const char* error_message = error_info->error_message != NULL ?    \
        error_info->error_message :                                      \
        "empty error message";                                           \
      napi_throw_error((env), NULL, error_message);                      \
    }                                                                    \
  } while (0)

#define NAPI_ASSERT_BASE(env, assertion, message, ret_val)               \
  do {                                                                   \
    if (!(assertion)) {                                                  \
      napi_throw_error(                                                  \
          (env),                                                         \
        NULL,                                                            \
          "assertion (" #assertion ") failed: " message);                \
      return ret_val;                                                    \
    }                                                                    \
  } while (0)

// Returns NULL on failed assertion.
// This is meant to be used inside napi_callback methods.
#define NAPI_ASSERT(env, assertion, message)                             \
  NAPI_ASSERT_BASE(env, assertion, message, NULL)

// Returns empty on failed assertion.
// This is meant to be used inside functions with void return type.
#define NAPI_ASSERT_RETURN_VOID(env, assertion, message)                 \
  NAPI_ASSERT_BASE(env, assertion, message, NAPI_RETVAL_NOTHING)

#define NAPI_CALL_BASE(env, the_call, ret_val)                           \
  do {                                                                   \
    if ((the_call) != napi_ok) {                                         \
      GET_AND_THROW_LAST_ERROR((env));                                   \
      return ret_val;                                                    \
    }                                                                    \
  } while (0)

// Returns NULL if the_call doesn't return napi_ok.
#define NAPI_CALL(env, the_call)                                         \
  NAPI_CALL_BASE(env, the_call, NULL)

// Returns empty if the_call doesn't return napi_ok.
#define NAPI_CALL_RETURN_VOID(env, the_call)                             \
  NAPI_CALL_BASE(env, the_call, NAPI_RETVAL_NOTHING)

#define DECLARE_NAPI_PROPERTY(name, func)                                \
  { (name), 0, (func), 0, 0, 0, napi_default, 0 }

#define DECLARE_NAPI_GETTER(name, func)                                  \
  { (name), 0, 0, (func), 0, 0, napi_default, 0 }
