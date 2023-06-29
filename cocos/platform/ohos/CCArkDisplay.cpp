#include "CCArkDisplay.h"
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <vector>

NS_CC_BEGIN
napi_env CCArkDisplay::_env = nullptr;

napi_value CCArkDisplay::initCCArkDisplay(napi_env env, napi_callback_info info)
{
    _env = env;
    return 0;
}

int CCArkDisplay::getDpi()
{
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        return -1;
    }
    napi_value getDpi = CCArkDisplay::getEngineFunc("getDpi");
    if (getDpi == nullptr) {
        return -1;
    }

    std::vector<napi_value> args;

    napi_value return_val;
    status = napi_call_function(_env, global, getDpi, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        return -1;
    }

    int32_t result;
    napi_get_value_int32(_env, return_val, &result);
    return result;
}

napi_value CCArkDisplay::getEngineFunc(const char* funcName)
{
    // Get the function named "AddTwo" on the global object
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        return nullptr;
    }

    napi_value cocosNs;
    status = napi_get_named_property(_env, global, "CCDisplayUtils", &cocosNs);
    if (status != napi_ok) {
        return nullptr;
    }

    napi_value func;
    status = napi_get_named_property(_env, cocosNs, funcName, &func);
    if (status != napi_ok) {
        return nullptr;
    }

    napi_valuetype functype;
    napi_typeof(_env, func, &functype);
    if (functype != napi_function) {
        return nullptr;
    }
    return func;
}
NS_CC_END