#include "errorcode.hpp"

Napi::Value ErrorCode::Wrap(Napi::Env env, const libtorrent::error_code &ec)
{
    if (ec)
    {
        auto err = Napi::Object::New(env);
        err.Set("message", ec.message());
        err.Set("value", ec.value());
        err.Set("what", ec.what());
        return err;
    }

    return env.Null();
}
