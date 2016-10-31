cmake_minimum_required(VERSION 3.6)
project(Nitty)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++")

set(C-CORE "libs/c-core")

set(SOURCE_FILES
#        samples/subscribe_publish_callback_sample.cpp
#        samples/pubnub_sample.cpp
        main.cpp
        src/pub_sub_helper.cpp
        src/formatting_helper.cpp
        )
set(TEST_SOURCE_FILES
        src/test_main.cpp
        src/formatting_helper.cpp
        src/messenger.cpp)


set(PUBNUB_FILES
        libs/c-core/core/pubnub_coreapi.c
        libs/c-core/core/pubnub_coreapi_ex.c
        libs/c-core/core/pubnub_ccore.c
        libs/c-core/core/pubnub_netcore.c

        libs/c-core/lib/sockets/pbpal_sockets.c
        libs/c-core/lib/sockets/pbpal_resolv_and_connect_sockets.c
        libs/c-core/lib/sockets/pbpal_adns_sockets.c
        libs/c-core/lib/base64/pbbase64.c

        libs/c-core/core/pubnub_alloc_std.c
        libs/c-core/core/pubnub_assert_std.c
        libs/c-core/core/pubnub_generate_uuid.c
        libs/c-core/core/pubnub_blocking_io.c
        libs/c-core/core/pubnub_timers.c
        libs/c-core/core/pubnub_json_parse.c
        libs/c-core/core/pubnub_helper.c
        )

set(POSIX_FILES
        libs/c-core/posix/pubnub_version_posix.c
        libs/c-core/posix/pubnub_generate_uuid_posix.c
        libs/c-core/posix/pbpal_posix_blocking_io.c
        libs/c-core/posix/monotonic_clock_get_time_posix.c
        )
set(WINDOWS_FILES
        libs/c-core/windows/pubnub_version_windows.c
        libs/c-core/windows/pubnub_generate_uuid_windows.c
        libs/c-core/windows/pbpal_windows_blocking_io.c
        libs/c-core/core/c99/snprintf.c
        )

set(CALLBACK_POSIX
        libs/c-core/cpp/pubnub_futres_posix.cpp
        libs/c-core/core/pubnub_timer_list.c
        libs/c-core/posix/pubnub_ntf_callback_posix.c
        libs/c-core/posix/pubnub_get_native_socket.c
        )
set(CALLBACK_WINDOWS
        libs/c-core/cpp/pubnub_futres_windows.cpp
        libs/c-core/core/pubnub_timer_list.c
        libs/c-core/windows/pubnub_ntf_callback_windows.c
        libs/c-core/windows/pubnub_get_native_socket.c
        )

set (SYNC_POSIX_WINDOWS
        libs/c-core/cpp/pubnub_futres_sync.cpp
        libs/c-core/core/pubnub_ntf_sync.c
        )

include_directories(libs/c-core/cpp)
include_directories(libs/c-core/posix)
include_directories(libs/c-core/core)
include_directories(libs/c-core/lib/base64)
include_directories(libs/c-core/lib/sockets)
include_directories(headers/)

add_definitions(
        -D PUBNUB_THREADSAFE
        -D PUBNUB_CALLBACK_API
)

add_library(pubnub_callback_posix SHARED ${PUBNUB_FILES} ${POSIX_FILES} ${CALLBACK_POSIX})
add_library(pubnub_sync_posix SHARED ${PUBNUB_FILES} ${POSIX_FILES} ${SYNC_POSIX_WINDOWS})
#add_library(pubnub_callback_windows SHARED ${PUBNUB_FILES} ${WINDOWS_FILES} ${CALLBACK_WINDOWS})
#add_library(pubnub_sync_windows SHARED ${PUBNUB_FILES} ${WINDOWS_FILES} ${SYNC_POSIX_WINDOWS})

add_executable(Nitty ${SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES})
target_link_libraries(Nitty pubnub_callback_posix)
target_link_libraries(Test pubnub_callback_posix)