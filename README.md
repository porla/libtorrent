# Node.js bindings for Rasterbar-libtorrent

This library provides (mostly) complete bindings against Rasterbar-libtorrent
compiled with SSL support. It tries to map one-to-one against the Rastebar-
libtorrent API.

***Warning:** The library is currently under development and should not be used
in a production environment.*


## Building

*Until `node-pre-gyp` supports the Node.js N-API, every user of these bindings
will need to do the following. When support is established, these instructions
are for binding developers and contributors only.*

To successfully build the bindings you will need the following,

* Visual Studio 2015 (Community) with the C++ toolset.
* Boost 1.66 (x86 or x64) installed to `C:\Libraries\boost_1_66_0`.
* OpenSSL 1.02n (x86 or x64) installed to `C:\OpenSSL-Win*`.

Furthermore, you will need to clone and build Rasterbar-libtorrent. `b2` from
Boost should either be in your PATH or you have to type the full path to it.

*Remove `address-model=64` and adjust the `--prefix` and `include` path if
you are building x86 (32-bit) bindings.*

* `git clone https://github.com/arvidn/libtorrent`
* `cd libtorrent`
* `b2 install toolset=msvc-14.0 address-model=64 boost-link=static crypto=openssl deprecated-functions=off link=static runtime-link=static variant=release --prefix="C:\Libraries\Rasterbar-libtorrent\msvc-14.0\x64" include="C:\OpenSSL-Win64\include"`
