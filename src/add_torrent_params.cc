#include "add_torrent_params.h"

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_info.hpp>

#include "common.h"
#include "torrent_info.h"

using porla::AddTorrentParams;

libtorrent::add_torrent_params AddTorrentParams::Parse(napi_env env, napi_value value)
{
    libtorrent::add_torrent_params params;
    Value p(env, value);

    if (p.HasNamedProperty("dht_nodes"))
    {
        Value dht_nodes = p.GetNamedProperty("dht_nodes");

        for (uint32_t i = 0; i < dht_nodes.GetArrayLength(); i++)
        {
            Value node = dht_nodes.GetArrayItem(i);

            std::string host = node.GetArrayItem(0).ToString();
            int port = node.GetArrayItem(1).ToInt32();

            params.dht_nodes.push_back({ host, port });
        }
    }

    if (p.HasNamedProperty("file_priorities"))
    {
        Value file_priorities = p.GetNamedProperty("file_priorities");

        for (uint32_t i = 0; i < file_priorities.GetArrayLength(); i++)
        {
            Value prio = file_priorities.GetArrayItem(i);
            params.file_priorities.push_back(libtorrent::download_priority_t(prio.ToInt32()));
        }
    }

    if (p.HasNamedProperty("name"))
    {
        params.name = p.GetNamedProperty("name").ToString();
    }

    if (p.HasNamedProperty("save_path"))
    {
        params.save_path = p.GetNamedProperty("save_path").ToString();
    }

    if (p.HasNamedProperty("storage_mode"))
    {
        Value storage_mode = p.GetNamedProperty("storage_mode");
        params.storage_mode = static_cast<libtorrent::storage_mode_t>(storage_mode.ToInt32());
    }

    if (p.HasNamedProperty("ti"))
    {
        TorrentInfo* ti = p.GetNamedProperty("ti").Unwrap<TorrentInfo>();
        params.ti = std::make_shared<libtorrent::torrent_info>(ti->Wrapped());
    }

    if (p.HasNamedProperty("tracker_tiers"))
    {
        Value tracker_tiers = p.GetNamedProperty("tracker_tiers");

        for (uint32_t i = 0; i < tracker_tiers.GetArrayLength(); i++)
        {
            Value tier = tracker_tiers.GetArrayItem(i);
            params.tracker_tiers.push_back(tier.ToInt32());
        }
    }

    if (p.HasNamedProperty("trackers"))
    {
        Value trackers = p.GetNamedProperty("trackers");

        for (uint32_t i = 0; i < trackers.GetArrayLength(); i++)
        {
            Value tracker = trackers.GetArrayItem(i);
            params.trackers.push_back(tracker.ToString());
        }
    }

    return params;
}
