# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(XComponent)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DOHOS_PLATFORM)
include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/common
                    ${NATIVERENDER_ROOT_PATH}/napi
                    ${NATIVERENDER_ROOT_PATH}/render
                    ../../../../cocos/include
                    ../../../../cocos
                    ../../../../cocos/platform/ohos
                    ../../../../external/libpng
                    ../../../../external/libjepg
                    ../../../../external/zlib
                    ../../../../external/libxml2
                    ../../../../external/opengles/api
                    ../../../../samples/Cpp/HelloCpp/Classes
                    )

add_definitions(-DOpenHarmony)

add_library(nativerender SHARED
            render/egl_core.cpp
            render/plugin_render.cpp
            plugin_manager.cpp
            napi_init.cpp
            WorkerMessageQueue.cpp
            modules/RawFileUtils.cpp
            )

find_library( # Sets the name of the path variable.
              EGL-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              EGL )

find_library( # Sets the name of the path variable.
              GLES-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              GLESv3 )

find_library( # Sets the name of the path variable.
              hilog-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              hilog_ndk.z )

find_library( # Sets the name of the path variable.
              libace-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_ndk.z )

find_library( # Sets the name of the path variable.
              libnapi-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_napi.z )

find_library( # Sets the name of the path variable.
              libuv-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              uv )
find_library( # Sets the name of the path variable.
              rawfile-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              rawfile.z )
#add_subdirectory(../../../../cocos2d-x/cocos2dx cocos.bin)
#target_link_libraries(nativerender PUBLIC ${EGL-lib} ${GLES-lib} ${hilog-lib} ${libace-lib} ${libnapi-lib} ${libuv-lib} ${rawfile-lib} cocos_helo libc++.a)
#add_subdirectory(../../../../samples/Cpp/HelloCpp/proj.ohos cocosOut.bin)

target_link_libraries(nativerender PUBLIC ${EGL-lib} ${GLES-lib} ${hilog-lib} ${libace-lib} ${libnapi-lib} ${libuv-lib} ${rawfile-lib} cocos2dx_test libc++.a)
add_subdirectory(../../../../samples/Cpp/TestCpp/proj.ohos testOut.bin)