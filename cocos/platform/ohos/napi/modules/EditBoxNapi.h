//
// Created on 2023/4/19.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef MyApplication_EditBoxNapi_H
#define MyApplication_EditBoxNapi_H


#endif //MyApplication_EditBoxNapi_H

#include <string>
#include <napi/native_api.h>

class EditBoxNapi {
public:
    static napi_value onChangeCallBack(napi_env env, napi_callback_info info);
    static napi_value onEnterCallBack(napi_env env, napi_callback_info info);
};