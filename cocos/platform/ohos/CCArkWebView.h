//
// Created on 2023/5/12.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "platform/CCPlatformMacros.h"
#include <napi/native_api.h>
#include <string>

NS_CC_BEGIN
class CCArkWebView {
public:
    static const std::string CREATE_WEBVIEW;
    static const std::string REMOVE_WEBVIEW;
    static const std::string STOP_LOADING;
    static const std::string RELOAD;
    static const std::string CAN_GO_BACK;
    static const std::string CAN_GO_FORWARD;
    static const std::string GO_BACK;
    static const std::string GO_FORWARD;
    
    static napi_value initCCArkWebView(napi_env env, napi_callback_info info);
    static void generalFuncParamOnlyViewTagWithoutReturn(std::string functionName, int viewTag);
    static void loadData(int viewTag, const char* data, const char* mimeType, const char* encoding, const char* baseURL);
    static void loadURL(int viewTag, const char* url);
    static bool generalFuncParamOnlyViewTagReturnBool(std::string functionName, int viewTag);
    static void setWebViewRect(int viewTag, int x, int y, int w, int h);
    static void setVisible(int viewTag, bool visible);
    static void evaluateJS(int viewTag, const char* js);
    static void setScalesPageToFit(int viewTag, bool scalesPageToFit);

    static napi_value getEngineFunc(napi_value global, const char* funcName);
    static void callFunction(const char* funcName, std::vector<napi_value> args);

private:
    static napi_env _env;
    
    static std::string getFullGlobalPath();
};
NS_CC_END
