//
// Created on 2023/05/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once

#include <napi/native_api.h>
#include <string>
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN
class CCArkJsWant {
public:
public:
    static napi_value initCCArkJsWant(napi_env env, napi_callback_info info);
    static bool implicitStartAbility(const char* url);
    static napi_value getEngineFunc(const char* funcName);
private:
    static napi_env _env;
};
NS_CC_END