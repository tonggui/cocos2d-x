//
// Created on 2023/4/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "platform/CCPlatformMacros.h"
#include <napi/native_api.h>
#include <string>

NS_CC_BEGIN
class CCArkEditBox {
public:
    static napi_value initCCArkEditBox(napi_env env, napi_callback_info info);
    static void createCocosEditBox(int index, int x, int y, int w, int h);
    static void setEditBoxViewRect(int x, int y, int w, int h);
    static void setEditBoxVisable(int x);
    static void setCurrentIndex(int index);
    static void setCurrentText(const char* text);
    static void setEditBoxPadding(int paddingW, int paddingH);
    static void setEditBoxPlaceHolder(const char* text);
    static void setEditBoxFontSize(int fontSize);
    static void setEditBoxFontColor(int r, int g, int b, int a);
    static void setEditBoxPlaceHolderFontSize(int fontSize);
    static void setEditBoxPlaceHolderFontColor(int r, int g, int b, int a);
    static void setEditBoxMaxLength(int maxLength);
    static void setNativeInputMode(int inputMode);
    static void setNativeInputFlag(int inputFlag);
    static void setEditBoxFontPath(const char* fontPath);
    static void setEditBoxPlaceHolderFontPath(const char* fontPath);

    static std::string getNativeText();
    static napi_value getEngineFunc(const char* funcName);

private:
    static napi_env _env;
};
NS_CC_END
