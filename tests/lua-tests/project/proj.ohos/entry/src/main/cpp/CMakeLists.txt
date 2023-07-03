cmake_minimum_required(VERSION 3.4.1)
project(nativerender)
message("====build nativerender is start===========")

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../..)
set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(OHOS true)
add_definitions(-DOHOS)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules)
include(CocosBuildHelpers)
ADD_DEFINITIONS(-DCOCOS2D_DEBUG=1)
set(CMAKE_CXX_STANDARD 14)
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

#if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
#    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../Resources/*")
#    file(COPY ${ALL_RESOURCES_FILES}
#        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
#endif()

include_directories(
        ${COCOS2DX_ROOT_PATH}/external/opengles/api
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos
)

add_library(${PROJECT_NAME} SHARED main.cpp napi_init.cpp)
message("====COCOS2DX_ROOT_PATH is ${COCOS2DX_ROOT_PATH}===========")

set(COCOS2DX_HEADER_PUBLIC
        ${CLASSES_PATH}
        ${COCOS2DX_ROOT_PATH}/cocos
        ${COCOS2DX_ROOT_PATH}/cocos/math
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/modules
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/common
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi
        ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/render
        ${COCOS2DX_ROOT_PATH}/external/opengles/api
        )

message("====build nativerender link cocos2d lua-tests===========")
target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_HEADER_PUBLIC})
target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH})
message("====build nativerender 2222 ===========")

add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/lua-tests/project lua-tests)
target_link_libraries(${PROJECT_NAME} PUBLIC luacocos2d lua-tests ${libnapi-lib} ${GLES-lib} ${hilog-lib} ${rawfile-lib})
message("***************  nativerender build end ****************")
