//
// Created by s00831826 on 2023/5/27.
//

#ifndef OPENHARMONYGAME_ACCELERATORCOCOS2DX_H
#define OPENHARMONYGAME_ACCELERATORCOCOS2DX_H

#include <string>
#include <napi/native_api.h>

class AcceleratorCocos2dx {
public:
    static napi_value onSensorChangedCallBack(napi_env env, napi_callback_info info);
};

#endif //OPENHARMONYGAME_ACCELERATORCOCOS2DX_H
