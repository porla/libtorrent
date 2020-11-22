cmake_minimum_required(VERSION 3.12)

project(porla_libtorrent)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# if we run OSX, set the OPENSSL_ROOT_DIR to the one where homebrew installed
# openssl, otherwise CMake will throw an err.
if(APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
endif()

# libtorrent -----------------------------------------------------------------
add_subdirectory(vendor/libtorrent)


# ----------------------------------------------------------------------------

if(APPLE)
    set(OUTPUT_DIR "darwin-x64")
    set(PLATFORM_LIBS
        "-framework System"
        "-framework SystemConfiguration")
elseif(UNIX)
    set(OUTPUT_DIR "linux-x64")

    # hack to detect r-pi
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l")
        set(OUTPUT_DIR "linux-arm")
        set(PLATFORM_LIBS
            atomic)
    endif()
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
    -DNAPI_VERSION=6
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
