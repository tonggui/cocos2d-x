//
// Created on 2022/11/29.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CC_ARKJS_DIALOG_H
#define CC_ARKJS_DIALOG_H

#include <napi/native_api.h>
#include <string>
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN
class CCArkJsDialog{
public:
    constexpr static const float DEFAULT_VOLUME = 0.5f;
    static napi_value initCCArkJsDialog(napi_env env, napi_value exports);


    static void showDialog(std::string& pszMsg, std::string& pszTitle);
    static void showTextInputDialog(std::string& msg, int idx);
    static void hideTextInputDialog();

    static napi_value getEngineFunc(const char* funcName);

    static napi_value onInsertCallBack(napi_env env, napi_callback_info info);
    static napi_value onDeleteCallBack(napi_env env, napi_callback_info info);
    static napi_value onCompleteCallBack(napi_env env, napi_callback_info info);
private:
    static int currentIndex;
    static napi_env _env;
};
NS_CC_END

#endif //CCDialog_H