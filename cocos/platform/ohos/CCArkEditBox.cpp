//
// Created on 2023/4/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "CCArkEditBox.h"
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <vector>
#include <string>

NS_CC_BEGIN
napi_env CCArkEditBox::_env = nullptr;

napi_value CCArkEditBox::initCCArkEditBox(napi_env env, napi_callback_info info)
{
    _env = env;
    return 0;
}

std::string CCArkEditBox::getNativeText()
{
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        return nullptr;
    }
    napi_value getNativeText = CCArkEditBox::getEngineFunc("getNativeText");
    if (getNativeText == nullptr) {
        return nullptr;
    }
    
    std::vector<napi_value> args;
    
    napi_value return_val;
    status = napi_call_function(_env, global, getNativeText, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        return nullptr;
    }
    size_t pInt;
    char result[256];
    napi_get_value_string_utf8(_env, return_val, result, 256, &pInt);
    return result;
}

void CCArkEditBox::setEditBoxViewRect(int x, int y, int w, int h)
{
    OHOS_LOGD("CCArkEditBox setEditBoxViewRect start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxViewRect get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxViewRect = getEngineFunc("setEditBoxViewRect");
    if (setEditBoxViewRect == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxViewRect get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argx;
    napi_create_int32(_env, x, &argx);
    args.push_back(argx);
    napi_value argy;
    napi_create_int32(_env, y, &argy);
    args.push_back(argy);
    napi_value argw;
    napi_create_int32(_env, w, &argw);
    args.push_back(argw);
    napi_value argh;
    napi_create_int32(_env, h, &argh);
    args.push_back(argh);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxViewRect, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxViewRect napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxViewRect call success");
}

void CCArkEditBox::setEditBoxPadding(int paddingW, int paddingH)
{
    OHOS_LOGD("CCArkEditBox setEditBoxPadding start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPadding get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxPadding = getEngineFunc("setEditBoxPadding");
    if (setEditBoxPadding == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPadding get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argpaddingW;
    napi_create_int32(_env, paddingW, &argpaddingW);
    args.push_back(argpaddingW);
    napi_value argPaddingH;
    napi_create_int32(_env, paddingH, &argPaddingH);
    args.push_back(argPaddingH);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxPadding, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPadding napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxPadding call success");
}

void CCArkEditBox::setEditBoxVisable(int x)
{
    OHOS_LOGD("CCArkEditBox setEditBoxVisable start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxVisable get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxVisable = getEngineFunc("setEditBoxVisable");
    if (setEditBoxVisable == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxVisable get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argx;
    napi_create_int32(_env, x, &argx);
    args.push_back(argx);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxVisable, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxVisable napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxVisable call success");
}

void CCArkEditBox::setCurrentIndex(int index)
{
    OHOS_LOGD("CCArkEditBox setCurrentIndex start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setCurrentIndex get global failed! status:%d", status);
        return;
    }
    napi_value setCurrentIndex = getEngineFunc("setCurrentIndex");
    if (setCurrentIndex == nullptr) {
        OHOS_LOGE("CCArkEditBox::setCurrentIndex get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argIndex;
    napi_create_int32(_env, index, &argIndex);
    args.push_back(argIndex);

    napi_value return_val;
    status = napi_call_function(_env, global, setCurrentIndex, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setCurrentIndex napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setCurrentIndex call success");
}

void CCArkEditBox::setCurrentText(const char* text)
{
    OHOS_LOGD("CCArkEditBox setCurrentText start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setCurrentText get global failed! status:%d", status);
        return;
    }
    napi_value setCurrentText = getEngineFunc("setCurrentText");
    if (setCurrentText == nullptr) {
        OHOS_LOGE("CCArkEditBox::setCurrentText get global failed!");
        return;
    }
    OHOS_LOGE("CCArkEditBox::setCurrentText text:%{public}s", text);
    std::vector<napi_value> args;
    napi_value argText;
    napi_create_string_utf8(_env, text, strlen(text), &argText);
    args.push_back(argText);

    napi_value return_val;
    status = napi_call_function(_env, global, setCurrentText, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setCurrentText napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setCurrentText call success");
}

void CCArkEditBox::setEditBoxPlaceHolder(const char* text)
{
    OHOS_LOGD("CCArkEditBox setEditBoxPlaceHolder start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolder get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxPlaceHolder = getEngineFunc("setEditBoxPlaceHolder");
    if (setEditBoxPlaceHolder == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolder get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argText;
    napi_create_string_utf8(_env, text, strlen(text), &argText);
    args.push_back(argText);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxPlaceHolder, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolder napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolder call success");
}

void CCArkEditBox::createCocosEditBox(int index, int x, int y, int w, int h)
{
    OHOS_LOGD("CCArkEditBox createCocosEditBox start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::createCocosEditBox get global failed! status:%d", status);
        return;
    }
    napi_value createCocosEditBox = getEngineFunc("createCocosEditBox");
    if (createCocosEditBox == nullptr) {
        OHOS_LOGE("CCArkEditBox::createCocosEditBox get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argIndex;
    napi_create_int32(_env, index ,&argIndex);
    args.push_back(argIndex);
    napi_value argx;
    napi_create_int32(_env, x ,&argx);
    args.push_back(argx);
    napi_value argy;
    napi_create_int32(_env, y ,&argy);
    args.push_back(argy);
    napi_value argw;
    napi_create_int32(_env, w ,&argw);
    args.push_back(argw);
    napi_value argh;
    napi_create_int32(_env, h ,&argh);
    args.push_back(argh);

    napi_value return_val;
    status = napi_call_function(_env, global, createCocosEditBox, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::createCocosEditBox napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::createCocosEditBox call success");
}

void CCArkEditBox::setEditBoxFontColor(int r, int g, int b, int a)
{
    OHOS_LOGD("CCArkEditBox setEditBoxFontColor start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontColor get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxFontColor = getEngineFunc("setEditBoxFontColor");
    if (setEditBoxFontColor == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontColor get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argr;
    napi_create_int32(_env, r, &argr);
    args.push_back(argr);
    napi_value argg;
    napi_create_int32(_env, g, &argg);
    args.push_back(argg);
    napi_value argb;
    napi_create_int32(_env, b, &argb);
    args.push_back(argb);
    napi_value arga;
    napi_create_int32(_env, a, &arga);
    args.push_back(arga);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxFontColor, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontColor napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxFontColor call success");
}

void CCArkEditBox::setEditBoxFontSize(int fontSize)
{
    OHOS_LOGD("CCArkEditBox setEditBoxFontSize start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontSize get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxFontSize = getEngineFunc("setEditBoxFontSize");
    if (setEditBoxFontSize == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontSize get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argFontSize;
    napi_create_int32(_env, fontSize, &argFontSize);
    args.push_back(argFontSize);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxFontSize, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontSize napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxFontSize call success");
}

void CCArkEditBox::setEditBoxPlaceHolderFontSize(int fontSize)
{
    OHOS_LOGD("CCArkEditBox setEditBoxPlaceHolderFontSize start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontSize get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxPlaceHolderFontSize = getEngineFunc("setEditBoxPlaceHolderFontSize");
    if (setEditBoxPlaceHolderFontSize == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontSize get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argFontSize;
    napi_create_int32(_env, fontSize, &argFontSize);
    args.push_back(argFontSize);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxPlaceHolderFontSize, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontSize napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontSize call success");
}

void CCArkEditBox::setEditBoxPlaceHolderFontColor(int r, int g, int b, int a)
{
    OHOS_LOGD("CCArkEditBox setEditBoxPlaceHolderFontColor start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontColor get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxPlaceHolderFontColor = getEngineFunc("setEditBoxPlaceHolderFontColor");
    if (setEditBoxPlaceHolderFontColor == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontColor get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argr;
    napi_create_int32(_env, r, &argr);
    args.push_back(argr);
    napi_value argg;
    napi_create_int32(_env, g, &argg);
    args.push_back(argg);
    napi_value argb;
    napi_create_int32(_env, b, &argb);
    args.push_back(argb);
    napi_value arga;
    napi_create_int32(_env, a, &arga);
    args.push_back(arga);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxPlaceHolderFontColor, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontColor napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontColor call success");
}

void CCArkEditBox::setEditBoxMaxLength(int maxLength)
{
    OHOS_LOGD("CCArkEditBox setEditBoxMaxLength start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxMaxLength get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxMaxLength = getEngineFunc("setEditBoxMaxLength");
    if (setEditBoxMaxLength == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxMaxLength get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argMaxLength;
    napi_create_int32(_env, maxLength, &argMaxLength);
    args.push_back(argMaxLength);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxMaxLength, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxMaxLength napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxMaxLength call success");
}

void CCArkEditBox::setNativeInputFlag(int inputFlag)
{
    OHOS_LOGD("CCArkEditBox setNativeInputFlag start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setNativeInputFlag get global failed! status:%d", status);
        return;
    }
    napi_value setNativeInputFlag = getEngineFunc("setNativeInputFlag");
    if (setNativeInputFlag == nullptr) {
        OHOS_LOGE("CCArkEditBox::setNativeInputFlag get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argInputFlag;
    napi_create_int32(_env, inputFlag, &argInputFlag);
    args.push_back(argInputFlag);

    napi_value return_val;
    status = napi_call_function(_env, global, setNativeInputFlag, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setNativeInputFlag napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setNativeInputFlag call success");
}

void CCArkEditBox::setNativeInputMode(int inputMode)
{
    OHOS_LOGD("CCArkEditBox setNativeInputMode start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setNativeInputMode get global failed! status:%d", status);
        return;
    }
    napi_value setNativeInputMode = getEngineFunc("setNativeInputMode");
    if (setNativeInputMode == nullptr) {
        OHOS_LOGE("CCArkEditBox::setNativeInputMode get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argInputMode;
    napi_create_int32(_env, inputMode, &argInputMode);
    args.push_back(argInputMode);

    napi_value return_val;
    status = napi_call_function(_env, global, setNativeInputMode, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setNativeInputMode napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setNativeInputMode call success");
}

void CCArkEditBox::setEditBoxFontPath(const char* fontPath)
{
    OHOS_LOGD("CCArkEditBox setEditBoxFontPath start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontPath get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxFontPath = getEngineFunc("setEditBoxFontPath");
    if (setEditBoxFontPath == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontPath get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argFontPath;
    napi_create_string_utf8(_env, fontPath, strlen(fontPath), &argFontPath);
    args.push_back(argFontPath);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxFontPath, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxFontPath napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxFontPath call success");
}

void CCArkEditBox::setEditBoxPlaceHolderFontPath(const char* fontPath)
{
    OHOS_LOGD("CCArkEditBox setEditBoxPlaceHolderFontPath start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontPath get global failed! status:%d", status);
        return;
    }
    napi_value setEditBoxPlaceHolderFontPath = getEngineFunc("setEditBoxPlaceHolderFontPath");
    if (setEditBoxPlaceHolderFontPath == nullptr) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontPath get global failed!");
        return;
    }

    std::vector<napi_value> args;
    napi_value argFontPath;
    napi_create_string_utf8(_env, fontPath, strlen(fontPath), &argFontPath);
    args.push_back(argFontPath);

    napi_value return_val;
    status = napi_call_function(_env, global, setEditBoxPlaceHolderFontPath, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontPath napi_call_function failed! status:%d", status);
        return;
    }
    OHOS_LOGE("CCArkEditBox::setEditBoxPlaceHolderFontPath call success");
}

napi_value CCArkEditBox::getEngineFunc(const char* funcName)
{
    // Get the function named "AddTwo" on the global object
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        return nullptr;
    }

    napi_value cocosNs;
    status = napi_get_named_property(_env, global, "CocosEditBox", &cocosNs);
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