#pragma once

#include <libtorrent/error_code.hpp>
#include <napi.h>

class ErrorCode
{
public:
    static Napi::Value Wrap(Napi::Env env, const libtorrent::error_code& ec);
};
