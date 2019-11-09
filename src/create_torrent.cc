#include "create_torrent.h"

#include <libtorrent/create_torrent.hpp>
#include <libtorrent/torrent_info.hpp>

#include "common.h"
#include "entry.h"
#include "torrent_info.h"

namespace lt = libtorrent;
using porla::CreateTorrent;

napi_ref CreateTorrent::constructor;

CreateTorrent::CreateTorrent()
    : wrapper_(nullptr)
{
    // TODO
    // ct_ = std::make_unique<lt::create_torrent>();
}

CreateTorrent::CreateTorrent(lt::torrent_info const& ti)
    : wrapper_(nullptr)
{
    ct_ = std::make_unique<lt::create_torrent>(ti);
}

void CreateTorrent::Destructor(napi_env env, void* native_obj, void* finalize_hint)
{
    delete static_cast<CreateTorrent*>(native_obj);
}

napi_status CreateTorrent::Init(napi_env env, napi_value exports)
{
    std::vector<napi_property_descriptor> properties
    {
        PORLA_METHOD_DESCRIPTOR("generate", Generate),
        PORLA_METHOD_DESCRIPTOR("generate_buf", GenerateBuf)
    };

    napi_status status;
    napi_value cons;

    status = napi_define_class(env, "CreateTorrent", NAPI_AUTO_LENGTH, New, nullptr, properties.size(), properties.data(), &cons);
    if (status != napi_ok) return status;

    status = napi_create_reference(env, cons, 1, &constructor);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env, exports, "create_torrent", cons);
    if (status != napi_ok) return status;

    return napi_ok;
}

napi_value CreateTorrent::New(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<CreateTorrent>(env, cbinfo);

    if (info.new_target == nullptr)
    {
        napi_throw_error(env, nullptr, "Not a construct (new) call");
        return nullptr;
    }

    if (info.args.size() != 1)
    {
        napi_throw_error(env, nullptr, "Expected 1 argument");
        return nullptr;
    }

    Value v(env, info.args[0]);
    auto ti = v.Unwrap<TorrentInfo>();

    CreateTorrent* obj = new CreateTorrent(*ti->Wrapped().get());

    napi_wrap(env, info.this_arg, obj, CreateTorrent::Destructor, nullptr, &obj->wrapper_);

    return info.this_arg;
}

napi_value CreateTorrent::Generate(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<CreateTorrent>(env, cbinfo);
    auto entry = info.wrap->ct_->generate();
    return Entry::ToJson(env, entry);
}

napi_value CreateTorrent::GenerateBuf(napi_env env, napi_callback_info cbinfo)
{
    auto info = UnwrapCallback<CreateTorrent>(env, cbinfo);
    auto entry = info.wrap->ct_->generate();

    std::vector<char> buffer;
    lt::bencode(std::back_inserter(buffer), entry);

    return Napi::Buffer<char>::Copy(env, buffer.data(), buffer.size());
}
