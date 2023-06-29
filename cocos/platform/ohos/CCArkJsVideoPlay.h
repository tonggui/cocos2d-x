//
// Created on 2023/05/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CCArkJsVideoPlay_H
#define CCArkJsVideoPlay_H

#include <napi/native_api.h>
#include <string>
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN
class CCArkJsVideoPlay {
public:
    constexpr static const float DEFAULT_VOLUME = 0.5f;

    static napi_value initJsVideoPlay(napi_env env, napi_callback_info info);

    static void createVideoPlayer(int viewTag);

    static void removeVideoPlayer(int viewTag);

    static void play(int viewTag);

    static void pause(int viewTag);

    static void stop(int viewTag);

    static void requestFullscreen(int viewTag, bool isFullscreen);

    static void setVisible(int viewTag, bool isVisible);

    static void setVideoPlayRect(int viewTag, int x, int y, int w, int h);

    static void seekTo(int viewTag, int seekTo);

    static void setURL(int viewTag, const std::string &_videoURL);

    static napi_value getEngineFunc(const char *funcName);

private:
    static napi_env _env;
};
#endif //CCArkJsVideoPlay_H
NS_CC_END