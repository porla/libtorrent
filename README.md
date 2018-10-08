# Node.js bindings for Rasterbar-libtorrent

This library provides (mostly) complete bindings against Rasterbar-libtorrent
compiled with SSL support. It tries to map one-to-one against the Rastebar-
libtorrent API.

***Warning:** The library is currently under development and should not be used
in a production environment.*


## Building

The bindings *should* build on most platforms when you run `npm install`. Make
sure you run `git submodule update --init` first to get the vendor dependencies
installed.

There is a *Dockerfile* to build against the `node:10` image.
