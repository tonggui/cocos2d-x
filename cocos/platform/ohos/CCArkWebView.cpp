//
// Created on 2023/5/12.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include <js_native_api.h>
#include <js_native_api_types.h>
#include <vector>
#include <string>

#include "CCArkWebView.h"
#include "napi/common/native_common.h"

NS_CC_BEGIN
napi_env CCArkWebView::_env = nullptr;

const std::string CCArkWebView::CREATE_WEBVIEW = "createWebView";
const std::string CCArkWebView::REMOVE_WEBVIEW = "removeWebView";
const std::string CCArkWebView::STOP_LOADING = "stopLoading";
const std::string CCArkWebView::RELOAD = "reload";
const std::string CCArkWebView::CAN_GO_BACK = "canGoBack";
const std::string CCArkWebView::CAN_GO_FORWARD = "canGoForward";
const std::string CCArkWebView::GO_BACK = "goBack";
const std::string CCArkWebView::GO_FORWARD = "goForward";

napi_value CCArkWebView::initCCArkWebView(napi_env env, napi_callback_info info)
{
    _env = env;
    return 0;
}

napi_value CCArkWebView::getEngineFunc(napi_value global, const char* funcName)
{    
    napi_value cocosNs;
    napi_status status = napi_get_named_property(_env, global, "WebView", &cocosNs);
    if (status != napi_ok) {
        OHOS_LOGE("get WebView namespace failed");
        return nullptr;
    }

    napi_value func;
    status = napi_get_named_property(_env, cocosNs, funcName, &func);
    if (status != napi_ok) {
        OHOS_LOGE("get ts function failed");
        return nullptr;
    }

    napi_valuetype funcType;
    napi_typeof(_env, func, &funcType);
    if (funcType != napi_function) {
        OHOS_LOGE("ts function check failed");
        return nullptr;
    }
    return func;
}

void CCArkWebView::callFunction(const char* funcName, std::vector<napi_value> args) {
    OHOS_LOGD("enter CCArkWebView.%{public}s funtion", funcName);
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("execute CCArkWebView.%{public}s failed for get ts global failed", funcName);
        return;
    }

    napi_value napiFunction = CCArkWebView::getEngineFunc(global, funcName);
    if (napiFunction == nullptr) {
        const napi_extended_error_info* error_info;
        napi_get_last_error_info((_env), &error_info);
        const char* err_message = error_info->error_message;
        OHOS_LOGE("execute CCArkWebView.%{public}s failed for get ts function failed for %{public}s", funcName, err_message);
        return;
    }

    napi_value return_val;
    status = napi_call_function(_env, global, napiFunction, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        const napi_extended_error_info* error_info;
        napi_get_last_error_info((_env), &error_info);
        const char* err_message = error_info->error_message;
        OHOS_LOGE("execute CCArkWebView.%{public}s failed for call ts function failed for %{public}s", funcName, err_message);
        return;
    }
    OHOS_LOGD("execute CCArkWebView.%{public}s success", funcName);
}

void CCArkWebView::generalFuncParamOnlyViewTagWithoutReturn(std::string functionName, int viewTag)
{
    std::vector<napi_value> args;
    const char* functionNameChar = functionName.c_str();
    napi_value argFunctionName;
    napi_create_string_utf8(_env, functionNameChar, strlen(functionNameChar), &argFunctionName);
    args.push_back(argFunctionName);
    napi_value argViewTag;
    napi_create_int32(_env, viewTag, &argViewTag);
    args.push_back(argViewTag);
    CCArkWebView::callFunction("functionNameAndViewTag", args);
}

void CCArkWebView::loadData(int viewTag, const char* data, const char* mimeType, const char* encoding, const char* baseURL) {
    std::vector<napi_value> args;
    napi_value argviewTag;
    napi_create_int32(_env, viewTag, &argviewTag);
    args.push_back(argviewTag);
    napi_value arg1;
    napi_create_string_utf8(_env, data, strlen(data), &arg1);
    args.push_back(arg1);
    napi_value arg2;
    napi_create_string_utf8(_env, mimeType, strlen(mimeType), &arg2);
    args.push_back(arg2);
    napi_value arg3;
    napi_create_string_utf8(_env, encoding, strlen(encoding), &arg3);
    args.push_back(arg3);
    napi_value arg4;
    napi_create_string_utf8(_env, baseURL, strlen(baseURL), &arg4);
    args.push_back(arg4);
    CCArkWebView::callFunction("loadData", args);
}

void CCArkWebView::loadURL(int viewTag, const char* url)
{
    std::vector<napi_value> args;
    napi_value argviewTag;
    napi_create_int32(_env, viewTag, &argviewTag);
    args.push_back(argviewTag);
    napi_value arg1;
    napi_create_string_utf8(_env, url, strlen(url), &arg1);
    args.push_back(arg1);
    CCArkWebView::callFunction("loadURL", args);
}

bool CCArkWebView::generalFuncParamOnlyViewTagReturnBool(std::string functionName, int viewTag)
{
    const char* functionNameChar = functionName.c_str();
    OHOS_LOGD("enter CCArkWebView.%{public}s funtion", functionNameChar);
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("execute CCArkWebView.%{public}s failed for get ts global failed", functionNameChar);
        return false;
    }

    napi_value napiFunction = CCArkWebView::getEngineFunc(global, "functionNameAndViewTag");
    if (napiFunction == nullptr) {
        const napi_extended_error_info* error_info;
        napi_get_last_error_info((_env), &error_info);
        const char* err_message = error_info->error_message;
        OHOS_LOGE("execute CCArkWebView.%{public}s failed for get ts function failed for %{public}s", functionNameChar, err_message);
        return false;
    }

    std::vector<napi_value> args;
    napi_value argFunctionName;
    napi_create_string_utf8(_env, functionNameChar, strlen(functionNameChar), &argFunctionName);
    args.push_back(argFunctionName);
    napi_value argViewTag;
    napi_create_int32(_env, viewTag, &argViewTag);
    args.push_back(argViewTag);

    napi_value return_val;
    status = napi_call_function(_env, global, napiFunction, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        const napi_extended_error_info* error_info;
        napi_get_last_error_info((_env), &error_info);
        const char* err_message = error_info->error_message;
        OHOS_LOGE("execute CCArkWebView.%{public}s failed for call ts function failed for %{public}s", functionNameChar, err_message);
        return false;
    }
    OHOS_LOGD("execute CCArkWebView.%{public}s success", functionNameChar);
    
    bool result;
    status = napi_get_value_bool(_env, return_val, &result);
    if(status != napi_ok){
        OHOS_LOGE("parse CCArkWebView.%{public}s result to bool failed", functionNameChar);
        return false;
    }
    OHOS_LOGD("parse CCArkWebView.%{public}s result to bool success", functionNameChar);
    return result;
}

void CCArkWebView::setWebViewRect(int viewTag, int x, int y, int w, int h) {
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
    CCArkWebView::callFunction("setWebViewRect", args);
}

void CCArkWebView::setVisible(int viewTag, bool visible) {
    std::vector<napi_value> args;
    napi_value argViewTag;
    napi_create_int32(_env, viewTag, &argViewTag);
    args.push_back(argViewTag);
    napi_value arg1;
    napi_get_boolean(_env, visible, &arg1);
    args.push_back(arg1);
    CCArkWebView::callFunction("setVisible", args);
}

void CCArkWebView::evaluateJS(int viewTag, const char* js) {
    std::vector<napi_value> args;
    napi_value argViewTag;
    napi_create_int32(_env, viewTag, &argViewTag);
    args.push_back(argViewTag);
    napi_value arg1;
    napi_create_string_utf8(_env, js, strlen(js), &arg1);
    args.push_back(arg1);
    CCArkWebView::callFunction("evaluateJS", args);
}

void CCArkWebView::setScalesPageToFit(int viewTag, bool scalesPageToFit) {
    std::vector<napi_value> args;
    napi_value argViewTag;
    napi_create_int32(_env, viewTag, &argViewTag);
    args.push_back(argViewTag);
    napi_value arg1;
    napi_get_boolean(_env, scalesPageToFit, &arg1);
    args.push_back(arg1);
    CCArkWebView::callFunction("setScalesPageToFit", args);
}

NS_CC_END