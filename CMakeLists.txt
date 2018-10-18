project (porla_libtorrent)
cmake_minimum_required(VERSION 3.12)

# Set C++11
set (CMAKE_CXX_STANDARD 11)

include("cmake/boost.cmake")
include("cmake/libtorrent.cmake")

file(GLOB SOURCE_FILES "src/*")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    PREFIX ""
    SUFFIX ".node"
    OUTPUT_NAME "node-napi"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/prebuilds/darwin-x64")

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    -DTORRENT_NO_DEPRECATE
    -DTORRENT_USE_OPENSSL
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${CMAKE_JS_INC}"
    ${BOOST_INCLUDE_DIRS}
    "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api"
    "${CMAKE_SOURCE_DIR}/vendor/libtorrent/include")

target_link_libraries(
    ${PROJECT_NAME}

    # Link against static OpenSSL (for electron)
    # TODO: adjust for all platforms. OSX specific code here.
    "/usr/local/opt/openssl/lib/libcrypto.a"
    "/usr/local/opt/openssl/lib/libssl.a"

    ${CMAKE_JS_LIB}
    "-framework System"
    "-framework SystemConfiguration"
    libtorrent-rasterbar
    boost-system)
