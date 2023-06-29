/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <string>
#include <stdio.h>

#include <ace/xcomponent/native_interface_xcomponent.h>

#include "modules/RawFileUtils.h"
#include "modules/EditBoxNapi.h"
#include "modules/WebViewNapi.h"
#include "modules/AcceleratorCocos2dx.h"
#include "plugin_manager.h"
#include "plugin_common.h"
#include "cocos2d.h"
#include "JsAudioEngine.h"
#include "CCArkJsDialog.h"
#include "CCApplication.h"
#include "CCArkDisplay.h"
#include "CCArkEditBox.h"
#include "CCArkJsLanguage.h"
#include "CCArkWebView.h"
#include "CCArkJsVideoPlay.h"
#include "CCFileUtils-ohos.h"
#include "CCArkJsWant.h"

#define kMaxStringLen 512

enum ContextType {
    APP_LIFECYCLE = 0,
    JS_PAGE_LIFECYCLE,
    RAW_FILE_UTILS,
    WORKER_INIT,
    NATIVE_RENDER_API,
    EDITBOX_NAPI,
    ACCELERATOR_API,
    WEBVIEW_NAPI
};

NapiManager NapiManager::manager_;

napi_value NapiManager::GetContext(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value exports;
    size_t argc = 1;
    napi_value args[1];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));

    if (argc != 1) {
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

    int64_t value;
    NAPI_CALL(env, napi_get_value_int64(env, args[0], &value));

    NAPI_CALL(env, napi_create_object(env, &exports));

    switch (value) {
        case APP_LIFECYCLE:
            {
                /**** AppInit 对应 app.ets中的应用生命周期 onCreate, onShow, onHide, onDestroy ******/
                LOGD("GetContext APP_LIFECYCLE");
                /**** Register App Lifecycle  ******/
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("onCreate", NapiManager::NapiOnCreate),
                    DECLARE_NAPI_FUNCTION("onShow", NapiManager::NapiOnShow),
                    DECLARE_NAPI_FUNCTION("onHide", NapiManager::NapiOnHide),
                    DECLARE_NAPI_FUNCTION("onDestroy", NapiManager::NapiOnDestroy),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case JS_PAGE_LIFECYCLE:
            {
                /****************  声明式开发范式 JS Page 生命周期注册 ****************************/
                LOGD("GetContext JS_PAGE_LIFECYCLE");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("onPageShow", NapiManager::NapiOnPageShow),
                    DECLARE_NAPI_FUNCTION("onPageHide", NapiManager::NapiOnPageHide),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case RAW_FILE_UTILS:
            #if 1
            {
                /****************  声明式开发范式 JS Page 生命周期注册 ****************************/
                LOGD("GetContext RAW_FILE_UTILS");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("nativeResourceManagerInit", RawFileUtils::nativeResourceManagerInit),
                    DECLARE_NAPI_FUNCTION("writablePathInit", NapiManager::napiWritablePathInit),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));

            }
            #endif 
            break;
        case WORKER_INIT:
            {
                LOGD("NapiManager::GetContext WORKER_INIT");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("workerInit", NapiManager::napiWorkerInit),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case NATIVE_RENDER_API:
        {
            LOGD("NapiManager::GetContext NATIVE_RENDER_API");
            napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("nativeEngineStart", NapiManager::napiNativeEngineStart),
            };
            NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
        }
            break;
        case EDITBOX_NAPI:
        {
            OHOS_LOGE("EditBoxNapi::Export");
            napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("onTextInsert", cocos2d::CCArkJsDialog::onInsertCallBack),
                    DECLARE_NAPI_FUNCTION("onTextDelete", cocos2d::CCArkJsDialog::onDeleteCallBack),
                    DECLARE_NAPI_FUNCTION("onComplete", cocos2d::CCArkJsDialog::onCompleteCallBack),
            };
            NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            OHOS_LOGE("EditBoxNapi::Export finish");
        }
            break;
        case ACCELERATOR_API:
        {
            LOGD("ACCELERATOR_API exporting");
            napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("onSensorChangedCallBack", AcceleratorCocos2dx::onSensorChangedCallBack),
            };
            NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
        }
            break;
        case WEBVIEW_NAPI:
        {
            OHOS_LOGE("WebViewNapi::Export");
            napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("shouldStartLoading", WebViewNapi::shouldStartLoading),
                    DECLARE_NAPI_FUNCTION("finishLoading", WebViewNapi::finishLoading),
                    DECLARE_NAPI_FUNCTION("failLoading", WebViewNapi::failLoading),
                    DECLARE_NAPI_FUNCTION("jsCallback", WebViewNapi::jsCallback),
            };
            NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            OHOS_LOGE("WebViewNapi::Export finish");
        }
            break;
        default:
            LOGE("unknown type");
    }
    return exports;
}

bool NapiManager::Export(napi_env env, napi_value exports)
{
    LOGD("NapiManager::Export");
    napi_status status;
    napi_value exportInstance = nullptr;
    OH_NativeXComponent *nativeXComponent = nullptr;
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;

    status = napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance);
    if (status != napi_ok) {
        return false;
    }

    status = napi_unwrap(env, exportInstance, reinterpret_cast<void**>(&nativeXComponent));
    if (status != napi_ok) {
        return false;
    }

    auto context = NapiManager::GetInstance();
    if (context) {
        context->SetNativeXComponent(nativeXComponent);
        PluginRender::GetInstance()->SetNativeXComponent(nativeXComponent);
        PluginRender::GetInstance()->Export(env, exports);
        return true;
    }
    return false;
}

void NapiManager::SetNativeXComponent(OH_NativeXComponent* nativeXComponent)
{
    nativeXComponent_ = nativeXComponent;
}

OH_NativeXComponent* NapiManager::GetNativeXComponent()
{
    return nativeXComponent_;
}

void NapiManager::MainOnMessage(const uv_async_t* req)
{
    LOGD("MainOnMessage Triggered");
}

napi_value NapiManager::NapiOnCreate(napi_env env, napi_callback_info info)
{
    LOGD("NapiManager::NapiOnCreate");
    return nullptr;
}

napi_value NapiManager::NapiOnShow(napi_env env, napi_callback_info info)
{
    LOGD("NapiManager::NapiOnShow");
    WorkerMessageData data{MessageType::WM_APP_SHOW, nullptr, nullptr};
    PluginRender::GetInstance()->enqueue(data);

    cocos2d::Application* app = cocos2d::Application::getInstance();
    if(app) {
        app->applicationWillEnterForeground();
    }
    cocos2d::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&foregroundEvent);

    return nullptr;
}

napi_value NapiManager::NapiOnHide(napi_env env, napi_callback_info info)
{
    LOGD("NapiManager::NapiOnHide");
    WorkerMessageData data{MessageType::WM_APP_HIDE, nullptr, nullptr};
    PluginRender::GetInstance()->enqueue(data);

    cocos2d::Application* app = cocos2d::Application::getInstance();
    if(app) {
        app->applicationDidEnterBackground();
    }
    cocos2d::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent);

    return nullptr;
}

napi_value NapiManager::NapiOnDestroy(napi_env env, napi_callback_info info)
{
    LOGD("NapiManager::NapiOnDestroy");
    WorkerMessageData data{MessageType::WM_APP_DESTROY, nullptr, nullptr};
    PluginRender::GetInstance()->enqueue(data);
    return nullptr;
}

napi_value NapiManager::napiWorkerInit(napi_env env, napi_callback_info info) {
    LOGD("NapiManager::napiWorkerInit");
    uv_loop_t* loop = nullptr;
    NAPI_CALL(env, napi_get_uv_event_loop(env, &loop));
    PluginRender::GetInstance()->workerInit(env, loop);
    return nullptr;
}

napi_value NapiManager::napiNativeEngineStart(napi_env env, napi_callback_info info) {
    LOGD("NapiManager::napiNativeEngineStart");
    PluginRender::GetInstance()->run();
	cocos2d::JsAudioEngine::initJsAudioEngine(env, nullptr);
    cocos2d::CCArkJsDialog::initCCArkJsDialog(env, nullptr);
    cocos2d::CCArkJsLanguage::initCCArkJsLanguage(env, nullptr);
    cocos2d::CCArkDisplay::initCCArkDisplay(env, nullptr);
    //cocos2d::CCArkEditBox::initCCArkEditBox(env, nullptr);
    cocos2d::CCArkWebView::initCCArkWebView(env, nullptr);
    cocos2d::CCArkJsVideoPlay::initJsVideoPlay(env, nullptr);
    cocos2d::CCArkJsWant::initCCArkJsWant(env, nullptr);
    return nullptr;
}

napi_value NapiManager::napiWritablePathInit(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value  args[1];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));

    char buffer[kMaxStringLen];
    size_t result = 0;
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[0], buffer, kMaxStringLen, &result));
    cocos2d::FileUtilsOhos::ohWritablePath = std::string(buffer) + '/';
    return nullptr;
}

napi_value NapiManager::NapiOnPageShow(napi_env env, napi_callback_info info)
{
    LOGD("NapiManager::NapiOnPageShow");
    return nullptr;
}

napi_value NapiManager::NapiOnPageHide(napi_env env, napi_callback_info info)
{
    LOGD("NapiManager::NapiOnPageHide");
    return nullptr;
}

void NapiManager::OnPageShowNative()
{
    LOGD("NapiManager::OnPageShowNative");
}

void NapiManager::OnPageHideNative()
{
    LOGD("NapiManager::OnPageHideNative");
}