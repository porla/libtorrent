cmake_minimum_required(VERSION 3.12)

project(porla_libtorrent)

set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS system)

# libtorrent -----------------------------------------------------------------
add_subdirectory(vendor/libtorrent)

if(UNIX)
    set_target_properties(
        "torrent-rasterbar"
        PROPERTIES
            COMPILE_FLAGS "-fPIC")
endif()
# ----------------------------------------------------------------------------

if(APPLE)
    set(OUTPUT_DIR "darwin-x64")
    set(PLATFORM_LIBS
        "/usr/local/opt/openssl/lib/libcrypto.a"
        "/usr/local/opt/openssl/lib/libssl.a"
        "-framework System"
        "-framework SystemConfiguration")
elseif(UNIX)
    set(OPENSSL_USE_STATIC_LIBS TRUE)
    set(OUTPUT_DIR "linux-x64")
    find_package(OpenSSL)
    set(PLATFORM_LIBS
        "${OPENSSL_CRYPTO_LIBRARY}"
        "${OPENSSL_SSL_LIBRARY}")
elseif(WIN32)
    set(OUTPUT_DIR "win32-x64")

    set(PLATFORM_DEFINES
        -D_WIN32_WINNT=0x0601
        -DWIN32)

    set(PLATFORM_LIBS
        crypt32)
endif()

file(GLOB SOURCE_FILES "src/*")

add_library(
    ${PROJECT_NAME}
    SHARED
    ${SOURCE_FILES})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        PREFIX                           ""
        SUFFIX                           ".node"
        OUTPUT_NAME                      "node-napi"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/prebuilds/${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/prebuilds/${OUTPUT_DIR}")

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    ${PLATFORM_DEFINES}
    -DNAPI_VERSION=3
    -DTORRENT_NO_DEPRECATE
    -DTORRENT_USE_LIBCRYPTO
    -DTORRENT_USE_OPENSSL)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${CMAKE_JS_INC}"
    "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api")

target_link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_JS_LIB}
    ${PLATFORM_LIBS}
    "torrent-rasterbar")
