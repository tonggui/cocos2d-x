//
// Created on 2022/11/29.
//
// Node APIs are not fully supported. To solve the compilation error of the
// interface cannot be found, please include "napi/native_api.h".
#include "CCArkJsVideoPlay.h"

#include <js_native_api.h>
#include <js_native_api_types.h>
#include <vector>

NS_CC_BEGIN
napi_env CCArkJsVideoPlay::_env = nullptr;

napi_value CCArkJsVideoPlay::initJsVideoPlay(napi_env
env,
napi_callback_info info
) {
OHOS_LOGE("initCCArkJsVideoPlay start!");
_env = env;
return 0;
}

void CCArkJsVideoPlay::createVideoPlayer(int viewTag) {
    OHOS_LOGD("CCArkJsVideoPlay createVideoPlayer start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::VideoPlayer get global failed! status:%d",status);
        return;
    }
    napi_value playFunc = getEngineFunc("createVideoPlayer");
    if (playFunc == nullptr) {
        OHOS_LOGE("CCArkJsVideoPlay:: get createVideoPlayer failed! status:%d",status);
        return;
    }

    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);
    
    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::VideoPlayer napi_call_function failed! "
                  "status:%d",
                  status);
        return;
    }
}


void CCArkJsVideoPlay::removeVideoPlayer(int viewTag) {
    OHOS_LOGD("CCArkJsVideoPlay removeVideoPlayer start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::VideoPlayer get global failed! status:%d",status);
        return;
    }
    napi_value playFunc = getEngineFunc("removeVideoPlayer");
    if (playFunc == nullptr) {
        OHOS_LOGE("CCArkJsVideoPlay:: get removeVideoPlayer failed! status:%d",status);
        return;
    }

    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::removeVideoPlayer napi_call_function failed! "
                  "status:%d",
                  status);
        return;
    }
    OHOS_LOGD("CCArkJsVideoPlay removeVideoPlayer end !");
}

void CCArkJsVideoPlay::play(int viewTag) {
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::play get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("play");
    if (playFunc == nullptr) {
        return;
    }

    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);
    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::play napi_call_function failed! status:%d",
                  status);
        return;
    }
    OHOS_LOGE("CCArkJsVideoPlay::play  end ");
}


void CCArkJsVideoPlay::setVideoPlayRect(int viewTag, int x, int y, int w, int h){
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::setVideoPlayRect get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("postSetVideoPlayerRect");
    if (playFunc == nullptr) {
        return;
    }

    std::vector<napi_value> args;
    napi_value argViewTag;
    napi_create_int32(_env, viewTag, &argViewTag);
    args.push_back(argViewTag);
    napi_value arg1;
    napi_create_int32(_env, x, &arg1);
    args.push_back(arg1);
    napi_value arg2;
    napi_create_int32(_env, y, &arg2);
    args.push_back(arg2);
    napi_value arg3;
    napi_create_int32(_env, w, &arg3);
    args.push_back(arg3);
    napi_value arg4;
    napi_create_int32(_env, h, &arg4);
    args.push_back(arg4);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::setVideoPlayRect napi_call_function failed! status:%d",
                  status);
        return;
    }
    OHOS_LOGE("CCArkJsVideoPlay::setVideoPlayRect  end ");
}

void CCArkJsVideoPlay::pause(int viewTag) {
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::pause get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("pause");
    if (playFunc == nullptr) {
        return;
    }

    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);
    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::pause napi_call_function failed! status:%d",
                  status);
        return;
    }
}

void CCArkJsVideoPlay::stop(int viewTag) {
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::stop get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("stop");
    if (playFunc == nullptr) {
        return;
    }

    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);
    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsVideoPlay::stop napi_call_function failed! status:%d",
                  status);
        return;
    }
}

void CCArkJsVideoPlay::seekTo(int viewTag, int seek) {
    OHOS_LOGD("CCArkJsVideoPlay seekTo start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCCCArkJsVideoPlay::seekTo get global failed! status:%d",
                  status);
        return;
    }
    napi_value playFunc = getEngineFunc("seekTo");
    if (playFunc == nullptr) {
        return;
    }
    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);

    napi_value argSeek;
    napi_create_int32(_env, seek, &argSeek);
    args.push_back(argSeek);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc,args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCCCArkJsVideoPlay::seekTo napi_call_function failed! status:%d",
                  status);
        return;
    }
}

void CCArkJsVideoPlay::setURL(int viewTag,const std::string &_videoURL) {
    OHOS_LOGD("CCArkJsVideoPlay setURL start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCCCArkJsVideoPlay::setURL get global failed! status:%d",
                  status);
        return;
    }
    napi_value playFunc = getEngineFunc("setURL");
    if (playFunc == nullptr) {
        return;
    }

    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);
    napi_value videoURL;
    napi_create_string_utf8(_env, _videoURL.c_str(), _videoURL.length(),
                            &videoURL);
    args.push_back(videoURL);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCCCArkJsVideoPlay::setURL napi_call_function failed! status:%d",
                  status);
        return;
    }
}

void CCArkJsVideoPlay::requestFullscreen(int viewTag, bool isFullscreen) {
    OHOS_LOGD("CCArkJsVideoPlay requestFullscreen start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCCCArkJsVideoPlay::requestFullscreen get global failed! status:%d",
                  status);
        return;
    }
    napi_value playFunc = getEngineFunc("requestFullscreen");
    if (playFunc == nullptr) {
        return;
    }

    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);

    napi_value isFullscreenArg;
    napi_get_boolean(_env, isFullscreen, &isFullscreenArg);
    args.push_back(isFullscreenArg);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCCCArkJsVideoPlay::requestFullscreen napi_call_function failed! status:%d",
                  status);
        return;
    }
}



void CCArkJsVideoPlay::setVisible(int viewTag, bool isVisible) {
    OHOS_LOGD("CCArkJsVideoPlay setVisible start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCCCArkJsVideoPlay::setVisible get global failed! status:%d",
                  status);
        return;
    }
    napi_value playFunc = getEngineFunc("setVideoPlayVisible");
    if (playFunc == nullptr) {
        return;
    }

    std::vector <napi_value> args;
    napi_value videoTag;
    napi_create_int32(_env, viewTag, &videoTag);
    args.push_back(videoTag);

    napi_value isVisibleArg;
    napi_get_boolean(_env, isVisible, &isVisibleArg);
    args.push_back(isVisibleArg);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(),
                                &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCCCArkJsVideoPlay::setVisible napi_call_function failed! status:%d",
                  status);
        return;
    }
}

napi_value CCArkJsVideoPlay::getEngineFunc(const char *funcName) {
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("%s get global failed!", funcName);
        return nullptr;
    }

    napi_value videoPlayer;
    status = napi_get_named_property(_env, global, "VideoPlayer",
                                     &videoPlayer);
    if (status != napi_ok) {
        OHOS_LOGE("%s get VideoPlayer failed!", funcName);
        return nullptr;
    }

    napi_value func;
    status = napi_get_named_property(_env, videoPlayer, funcName, &func);
    if (status != napi_ok) {
        OHOS_LOGE("%s get func failed!", funcName);
        return nullptr;
    }

    napi_valuetype functype;
    napi_typeof(_env, func, &functype);
    if (functype != napi_function) {
        OHOS_LOGE("%s get func but is not a function", funcName);
        return nullptr;
    }
    return func;
}

NS_CC_END