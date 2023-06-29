#include "CCArkJsDialog.h"
#include "platform/CCPlatformMacros.h"
#include "CCLogOhos.h"

#include <vector>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include "platform/ohos/napi/plugin_manager.h"
#include "ui/UIEditBox/UIEditBoxImpl-ohos.h"

NS_CC_BEGIN

napi_env CCArkJsDialog::_env = nullptr;
int CCArkJsDialog::currentIndex = -1;
napi_value CCArkJsDialog::initCCArkJsDialog(napi_env env, napi_value exports)
{
    OHOS_LOGD("initCCArkJsDialog start!");
    _env = env;
    return 0;
}

void CCArkJsDialog::showDialog(std::string& pszMsg, std::string& pszTitle)
{
    OHOS_LOGD("CCArkJsDialog showDialog start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsDialog::showDialog get global failed! status:%d", status);
        return;
    }
    napi_value preloadMusicFunc = getEngineFunc("showDialog");
    if (preloadMusicFunc == nullptr) {
        return;
    }

    std::vector<napi_value> args;
    napi_value argMsg;
    napi_create_string_utf8(_env, pszMsg.data(), pszMsg.length() ,&argMsg);
    args.push_back(argMsg);
    napi_value argTitle;
    napi_create_string_utf8(_env, pszTitle.data(), pszTitle.length() ,&argTitle);
    args.push_back(argTitle);

    napi_value return_val;
    status = napi_call_function(_env, global, preloadMusicFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsDialog::showDialog napi_call_function failed! status:%d", status);
        return;
    }
}

void CCArkJsDialog::showTextInputDialog(std::string& msg, int idx)
{
    currentIndex = idx;
    OHOS_LOGD("CCArkJsDialog showTextInputDialog start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsDialog::showTextInputDialog get global failed! status:%d", status);
        return;
    }
    napi_value showTextInputDialog = getEngineFunc("showTextInputDialog");
    if (showTextInputDialog == nullptr) {
        return;
    }

    std::vector<napi_value> args;
    napi_value argMsg;
    napi_create_string_utf8(_env, msg.data(), msg.length(), &argMsg);
    args.push_back(argMsg);

    napi_value return_val;
    status = napi_call_function(_env, global, showTextInputDialog, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsDialog::showTextInputDialog napi_call_function failed! status:%d", status);
        return;
    }
}

void CCArkJsDialog::hideTextInputDialog()
{
    OHOS_LOGD("CCArkJsDialog hideTextInputDialog start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsDialog::hideTextInputDialog get global failed! status:%d", status);
        return;
    }
    napi_value hideTextInputDialog = getEngineFunc("hideTextInputDialog");
    if (hideTextInputDialog == nullptr) {
        return;
    }

    std::vector<napi_value> args;

    napi_value return_val;
    status = napi_call_function(_env, global, hideTextInputDialog, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkJsDialog::hideTextInputDialog napi_call_function failed! status:%d", status);
        return;
    }
}

napi_value CCArkJsDialog::getEngineFunc(const char* funcName)
{
    // Get the function named "AddTwo" on the global object
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("%s get global failed!", funcName);
        return nullptr;
    }

    napi_value cocosNs;
    status = napi_get_named_property(_env, global, "ccDialogUtils", &cocosNs);
    if (status != napi_ok) {
        OHOS_LOGE("%s get cocosNs failed!", funcName);
        return nullptr;
    }

    napi_value func;
    status = napi_get_named_property(_env, cocosNs, funcName, &func);
    if (status != napi_ok) {
        OHOS_LOGE("%s get func failed!", funcName);
        return nullptr;
    }

    napi_valuetype functype;
    napi_typeof(_env, func, &functype);
    if (functype != napi_function) {
        OHOS_LOGE("%s get func but is not a function", funcName);
        return nullptr;
    }
    return func;
}


napi_value CCArkJsDialog::onInsertCallBack(napi_env env, napi_callback_info info) {
    napi_status status;
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
    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    size_t pInt;
    char text[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[0], text, 256, &pInt));

    cocos2d::log("[hsun editbox]current text is %s/n", text);
    cocos2d::ui::EditBoxImplOhos::onInsertCallBack(currentIndex, text);
    return nullptr;
}

napi_value CCArkJsDialog::onDeleteCallBack(napi_env env, napi_callback_info info) {

    cocos2d::ui::EditBoxImplOhos::onDeleteCallBack(currentIndex);
    return nullptr;
}

napi_value CCArkJsDialog::onCompleteCallBack(napi_env env, napi_callback_info info) {
    napi_status status;
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
    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    size_t pInt;
    char text[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[0], text, 256, &pInt));

    cocos2d::log("[hsun editbox]current text is \"%s\"/n", text);
    cocos2d::ui::EditBoxImplOhos::onCompleteCallBack(currentIndex, text);
    return nullptr;
}

NS_CC_END