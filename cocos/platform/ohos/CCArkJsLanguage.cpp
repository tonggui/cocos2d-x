#include "CCArkJsLanguage.h"
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <string>
#include <vector>

NS_CC_BEGIN
napi_env CCArkJsLanguage::_env = nullptr;

napi_value CCArkJsLanguage::initCCArkJsLanguage(napi_env env, napi_callback_info info)
{
    _env = env;
    return 0;
}

std::string CCArkJsLanguage::getSystemLanguage()
{
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        return nullptr;
    }
    napi_value getSystemLanguage = CCArkJsLanguage::getEngineFunc("getSystemLanguage");
    if (getSystemLanguage == nullptr) {
        return nullptr;
    }    
    
    std::vector<napi_value> args;
    
    napi_value return_val;
    status = napi_call_function(_env, global, getSystemLanguage, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        return nullptr;
    }
    size_t pInt;
    char result[256];
    napi_get_value_string_utf8(_env, return_val, result, 256, &pInt);
    return result;
}

napi_value CCArkJsLanguage::getEngineFunc(const char* funcName)
{
    // Get the function named "AddTwo" on the global object
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        return nullptr;
    }
    
    napi_value cocosNs;
    status = napi_get_named_property(_env, global, "languageUtils", &cocosNs);
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