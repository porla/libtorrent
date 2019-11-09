#include "info_hash.h"

#include <sstream>

using porla::InfoHash;

Napi::Value InfoHash::ToString(Napi::Env env, libtorrent::info_hash_t const& hash)
{
    std::stringstream ss;

    if (hash.has_v2())
    {
        ss << hash.v2;
    }
    else
    {
        ss << hash.v1;
    }

    return Napi::String::New(env, ss.str());
}
