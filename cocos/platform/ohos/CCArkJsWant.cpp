#include "CCArkJsWant.h"
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <string>
#include <vector>

NS_CC_BEGIN
napi_env CCArkJsWant::_env = nullptr;

napi_value CCArkJsWant::initCCArkJsWant(napi_env env, napi_callback_info info)
{
    _env = env;
    return 0;
}

bool CCArkJsWant::implicitStartAbility(const char* url)
{
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("execute CCArkJsWant.implicitStartAbility failed for get ts global failed");
        return false;
    }
    napi_value implicitStartAbility = CCArkJsWant::getEngineFunc("implicitStartAbility");
    if (implicitStartAbility == nullptr) {
        OHOS_LOGE("execute CCArkJsWant.implicitStartAbility failed for get ts method failed");
        return false;
    }    
    
    std::vector<napi_value> args;
    napi_value napi_url;
    napi_create_string_utf8(_env, url, strlen(url), &napi_url);
    args.push_back(napi_url);

    napi_value return_val;
    status = napi_call_function(_env, global, implicitStartAbility, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("execute CCArkJsWant.implicitStartAbility invoke failed with the url: %{public}s",url);
        return false;
    }
    return true;
}

napi_value CCArkJsWant::getEngineFunc(const char* funcName)
{
    // Get the function named "AddTwo" on the global object
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        return nullptr;
    }
    
    napi_value cocosNs;
    status = napi_get_named_property(_env, global, "wantUtils", &cocosNs);
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