//
// Created on 2023/4/19.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef _WEB_VIEW_NAPI_H
#define _WEB_VIEW_NAPI_H

#include <string>
#include <napi/native_api.h>

class WebViewNapi {
public:
    static napi_value shouldStartLoading(napi_env env, napi_callback_info info);
    static napi_value finishLoading(napi_env env, napi_callback_info info);
    static napi_value failLoading(napi_env env, napi_callback_info info);
    static napi_value jsCallback(napi_env env, napi_callback_info info);
};

#endif //_WEB_VIEW_NAPI_H