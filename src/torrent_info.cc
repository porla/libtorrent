#include "torrent_info.h"

#include <libtorrent/torrent_info.hpp>
#include <sstream>

#include "common.h"
#include "file_storage.h"
#include "info_hash.h"

namespace lt = libtorrent;
using porla::TorrentInfo;

Napi::FunctionReference TorrentInfo::constructor;

Napi::Object TorrentInfo::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "TorrentInfo", {
        /*InstanceMethod("add_http_seed", &TorrentInfo::AddHttpSeed),
        InstanceMethod("add_node", &TorrentInfo::AddNode),
        InstanceMethod("add_tracker", &TorrentInfo::AddTracker),
        InstanceMethod("add_url_seed", &TorrentInfo::AddUrlSeed),
        InstanceMethod("add_url_seed", &TorrentInfo::AddUrlSeed),
        InstanceMethod("collections", &TorrentInfo::Collections),*/
        InstanceMethod("comment", &TorrentInfo::Comment),
        InstanceMethod("creation_date", &TorrentInfo::CreationDate),
        InstanceMethod("creator", &TorrentInfo::Creator),
        InstanceMethod("files", &TorrentInfo::Files),
        InstanceMethod("hash_for_piece", &TorrentInfo::HashForPiece),
        /*InstanceMethod("http_seeds", &TorrentInfo::HttpSeeds),
        InstanceMethod("info", &TorrentInfo::Info),*/
        InstanceMethod("info_hash", &TorrentInfo::InfoHash),
        /*InstanceMethod("is_i2p", &TorrentInfo::IsI2P),
        InstanceMethod("is_loaded", &TorrentInfo::IsLoaded),
        InstanceMethod("is_merkle_torrent", &TorrentInfo::IsMerkleTorrent),
        InstanceMethod("is_valid", &TorrentInfo::IsValid),
        InstanceMethod("last_piece", &TorrentInfo::LastPiece),
        InstanceMethod("map_block", &TorrentInfo::MapBlock),
        InstanceMethod("map_file", &TorrentInfo::MapFile),
        InstanceMethod("merkle_tree", &TorrentInfo::MerkleTree),
        InstanceMethod("metadata", &TorrentInfo::Metadata),*/
        InstanceMethod("name", &TorrentInfo::Name),
        /*InstanceMethod("nodes", &TorrentInfo::Nodes),*/
        InstanceMethod("num_files", &TorrentInfo::NumFiles),
        InstanceMethod("num_pieces", &TorrentInfo::NumPieces),
        /*InstanceMethod("orig_files", &TorrentInfo::OrigFiles),
        InstanceMethod("parse_torrent_file", &TorrentInfo::ParseTorrentFile),*/
        InstanceMethod("piece_length", &TorrentInfo::PieceLength),
        InstanceMethod("piece_range", &TorrentInfo::PieceRange),
        InstanceMethod("piece_size", &TorrentInfo::PieceSize),
        InstanceMethod("priv", &TorrentInfo::Priv),
        /*InstanceMethod("remap_files", &TorrentInfo::RemapFiles),
        InstanceMethod("rename_file", &TorrentInfo::RenameFile),
        InstanceMethod("set_merkle_tree", &TorrentInfo::SetMerkleTree),
        InstanceMethod("set_web_seeds", &TorrentInfo::SetWebSeeds),
        InstanceMethod("similar_torrents", &TorrentInfo::SimilarTorrents),*/
        InstanceMethod("ssl_cert", &TorrentInfo::SslCert),
        InstanceMethod("total_size", &TorrentInfo::TotalSize),
        /*InstanceMethod("trackers", &TorrentInfo::Trackers),
        InstanceMethod("url_seeds", &TorrentInfo::UrlSeeds),
        InstanceMethod("web_seeds", &TorrentInfo::WebSeeds)*/
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("torrent_info", func);

    return exports;
}

Napi::Object TorrentInfo::NewInstance(Napi::Value arg)
{
    return constructor.New({ arg });
}

TorrentInfo::TorrentInfo(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<TorrentInfo>(info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
    }

    lt::error_code ec;

    if (info[0].IsString())
    {
        auto str = info[0].As<Napi::String>();
        ti_ = std::make_shared<lt::torrent_info>(str, ec);
    }
    else if (info[0].IsExternal())
    {
        auto ext = info[0].As<Napi::External<std::shared_ptr<lt::torrent_info>>>();
        ti_ = *ext.Data();
    }
    else if (info[0].IsBuffer())
    {
        auto buf = info[0].As<Napi::Buffer<char>>();
        libtorrent::span<const char> s(buf.Data(), buf.Length());
        ti_ = std::make_shared<lt::torrent_info>(s, ec, libtorrent::from_span);
    }

    if (ec)
    {
        Napi::Error::New(info.Env(), ec.message()).ThrowAsJavaScriptException();
    }
}

std::shared_ptr<lt::torrent_info> TorrentInfo::Wrapped()
{
    return ti_;
}

Napi::Value TorrentInfo::Comment(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), ti_->comment());
}

Napi::Value TorrentInfo::CreationDate(const Napi::CallbackInfo& info)
{
    napi_value result;
    napi_create_int64(info.Env(), ti_->creation_date(), &result);
    return Napi::Value(info.Env(), result);
}

Napi::Value TorrentInfo::Creator(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), ti_->creator());
}

Napi::Value TorrentInfo::Files(const Napi::CallbackInfo& info)
{
    auto files = ti_->files();
    auto arg = Napi::External<lt::file_storage>::New(info.Env(), &files);

    return FileStorage::NewInstance(arg);
}

Napi::Value TorrentInfo::HashForPiece(const Napi::CallbackInfo& info)
{
    auto idx = static_cast<lt::piece_index_t>(info[0].As<Napi::Number>().Int32Value());
    
    std::stringstream ss;
    ss << ti_->hash_for_piece(idx);

    return Napi::String::New(info.Env(), ss.str());
}

Napi::Value TorrentInfo::InfoHash(const Napi::CallbackInfo& info)
{
    return InfoHash::ToString(info.Env(), ti_->info_hashes());
}

Napi::Value TorrentInfo::Name(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), ti_->name());
}

Napi::Value TorrentInfo::NumFiles(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ti_->num_files());
}

Napi::Value TorrentInfo::NumPieces(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ti_->num_pieces());
}

Napi::Value TorrentInfo::PieceLength(const Napi::CallbackInfo& info)
{
    return Napi::Number::New(info.Env(), ti_->piece_length());
}

Napi::Value TorrentInfo::PieceRange(const Napi::CallbackInfo& info)
{
    Napi::Error::New(info.Env(), "Not implemented").ThrowAsJavaScriptException();
    return info.Env().Undefined();
}

Napi::Value TorrentInfo::PieceSize(const Napi::CallbackInfo& info)
{
    if (info.Length() < 1)
    {
        Napi::Error::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    lt::piece_index_t idx = static_cast<lt::piece_index_t>(info[0].As<Napi::Number>().Uint32Value());

    return Napi::Number::New(info.Env(), ti_->piece_size(idx));
}

Napi::Value TorrentInfo::Priv(const Napi::CallbackInfo& info)
{
    return Napi::Boolean::New(info.Env(), ti_->priv());
}

Napi::Value TorrentInfo::SslCert(const Napi::CallbackInfo& info)
{
    return Napi::String::New(info.Env(), ti_->ssl_cert().to_string());
}

Napi::Value TorrentInfo::TotalSize(const Napi::CallbackInfo& info)
{
    napi_value result;
    napi_create_int64(info.Env(), ti_->total_size(), &result);
    return Napi::Value(info.Env(), result);
}
