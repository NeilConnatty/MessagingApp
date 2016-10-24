cmake_minimum_required(VERSION 3.6)
project(Florie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++")

set(C-CORE "libs/c-core")

set(SOURCE_FILES samples/pubnub_sample.cpp)

set(PUBNUB_FILES
        libs/c-core/core/pubnub_coreapi.c
        libs/c-core/core/pubnub_coreapi_ex.c
        libs/c-core/core/pubnub_ccore.c
        libs/c-core/core/pubnub_netcore.c
        libs/c-core/lib/sockets/pbpal_sockets.c
        libs/c-core/lib/sockets/pbpal_resolv_and_connect_sockets.c
        libs/c-core/core/pubnub_alloc_std.c
        libs/c-core/core/pubnub_alloc_std.c
        libs/c-core/core/pubnub_assert_std.c
        libs/c-core/core/pubnub_generate_uuid.c
        libs/c-core/core/pubnub_blocking_io.c
        libs/c-core/core/pubnub_timers.c
        libs/c-core/core/pubnub_json_parse.c
        libs/c-core/core/pubnub_helper.c
        libs/c-core/posix/pubnub_version_posix.c
        libs/c-core/posix/pubnub_generate_uuid_posix.c
        libs/c-core/posix/pbpal_posix_blocking_io.c
        libs/c-core/posix/monotonic_clock_get_time_posix.c
        libs/c-core/core/pubnub_ntf_sync.c
        libs/c-core/cpp/pubnub_futres_sync.cpp
        )


include_directories(libs/c-core/cpp)
include_directories(libs/c-core/posix)
include_directories(libs/c-core/core)

add_definitions(
        -D PUBNUB_THREADSAFE
        -D PUBNUB_CALLBACK_API
)

add_executable(Florie ${SOURCE_FILES} ${PUBNUB_FILES})
link_libraries(Florie pthread rt)
