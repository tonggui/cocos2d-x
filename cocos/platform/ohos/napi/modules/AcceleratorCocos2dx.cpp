//
// Created by s00831826 on 2023/5/27.
//
#include "AcceleratorCocos2dx.h"
#include "../../CCLogOhos.h"
#include <js_native_api.h>
#include <js_native_api_types.h>
#include "platform/ohos/napi/plugin_manager.h"

#include "napi/modules/Cocos2dxHelper.h"
#include "cocos2d.h"
// #include "base/ccTypes.h"
#include "base/CCEventAcceleration.h"

#define TG3_GRAVITY_EARTH                    (9.80665f)
using namespace cocos2d;

static void dispatchAccelerometer(double x, double y, double z, long timeStamp) {
    Acceleration a;
    a.x = -(x / TG3_GRAVITY_EARTH);
    a.y = -(y / TG3_GRAVITY_EARTH);
    a.z = -(z / TG3_GRAVITY_EARTH);
    a.timestamp = (double)timeStamp;

    EventAcceleration event(a);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

napi_value AcceleratorCocos2dx::onSensorChangedCallBack(napi_env env, napi_callback_info info){
    napi_status status;
    size_t argc = 4;
    napi_value args[4];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    if (argc != 4) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    status = napi_typeof(env, args[0], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    status = napi_typeof(env, args[3], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    double x;
    NAPI_CALL(env, napi_get_value_double(env, args[0], &x));
    double y;
    NAPI_CALL(env, napi_get_value_double(env, args[1], &y));
    double z;
    NAPI_CALL(env, napi_get_value_double(env, args[2], &z));
    long timestamp;
    NAPI_CALL(env, napi_get_value_int64(env, args[3], &timestamp));
    
    dispatchAccelerometer(x, y, z, timestamp);
    return nullptr;
}