cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(porla_libtorrent)

set(CMAKE_CXX_STANDARD 20)

# Include Node-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR)
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

find_package(LibtorrentRasterbar CONFIG REQUIRED)

add_library(
    ${PROJECT_NAME}
    SHARED
    src/addtorrentparams.cpp
    src/addtorrentparams.hpp
    src/alert.cpp
    src/alert.hpp
    src/infohash.cpp
    src/infohash.hpp
    src/porla-libtorrent.cpp
    src/session.cpp
    src/session.hpp
    src/torrenthandle.cpp
    src/torrenthandle.hpp
    src/torrentinfo.cpp
    src/torrentinfo.hpp
    src/torrentstatus.cpp
    src/torrentstatus.hpp)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        PREFIX                           ""
        SUFFIX                           ".node"
        OUTPUT_NAME                      "node-napi"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/prebuilds/${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/prebuilds/${OUTPUT_DIR}")

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_JS_INC}
    ${NODE_ADDON_API_DIR})

target_link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_JS_LIB}
    LibtorrentRasterbar::torrent-rasterbar)
