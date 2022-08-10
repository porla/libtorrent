# Node.js bindings for Rasterbar-libtorrent

This library provides (mostly) complete bindings against Rasterbar-libtorrent
compiled with SSL support. It tries to map one-to-one against the Rastebar-
libtorrent API.

## Getting started

```js
const lt = require("@porla/libtorrent");

const params = new lt.AddTorrentParams();
params.save_path = ".";
params.ti = new lt.TorrentInfo("/path/to/torrent");

const session = new lt.Session();
session.add_torrent(params);
session.on("add_torrent", () => console.log("Torrent added"));
session.on("state_update", () => console.log("State updated"));

setInterval(() => s.post_torrent_updates(), 1000);
```

## Building

`vcpkg` is used for native dependency management. You need CMake and a proper
C++ toolchain.

Running `yarn` should build everything.
