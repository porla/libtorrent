project (porla_libtorrent)
cmake_minimum_required(VERSION 3.10)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system)

if (APPLE)
    set (OUTPUT_DIR "darwin-x64")
    set (PLATFORM_LIBS
        "/usr/local/opt/openssl/lib/libcrypto.a"
        "/usr/local/opt/openssl/lib/libssl.a"
        "-framework System"
        "-framework SystemConfiguration")
elseif(UNIX)
    set (OPENSSL_USE_STATIC_LIBS TRUE)
    set (OUTPUT_DIR "linux-x64")
    find_package(OpenSSL)
    set (PLATFORM_LIBS
        "${OPENSSL_CRYPTO_LIBRARY}"
        "${OPENSSL_SSL_LIBRARY}")
elseif(WIN32)
    set (OPENSSL_USE_STATIC_LIBS TRUE)
    set (OUTPUT_DIR "win32-x64")
    find_package(OpenSSL)
    set (PLATFORM_LIBS
        "${OPENSSL_CRYPTO_LIBRARY}"
        "${OPENSSL_SSL_LIBRARY}"
        crypt32
        iphlpapi
        legacy_stdio_definitions)
endif()

set (CMAKE_CXX_STANDARD 11)

include("cmake/libtorrent.cmake")

file(GLOB SOURCE_FILES "src/*")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    PREFIX ""
    SUFFIX ".node"
    OUTPUT_NAME "node-napi"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/prebuilds/${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/prebuilds/${OUTPUT_DIR}")

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    -DBOOST_ALL_NO_LIB
    -DTORRENT_NO_DEPRECATE
    -DTORRENT_USE_OPENSSL
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${CMAKE_JS_INC}"
    "${Boost_INCLUDE_DIRS}"
    "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api"
    "${CMAKE_SOURCE_DIR}/vendor/libtorrent/include")

target_link_libraries(
    ${PROJECT_NAME}

    ${PLATFORM_LIBS}

    ${Boost_LIBRARIES}
    ${CMAKE_JS_LIB}

    libtorrent-rasterbar)
