#include "platform/CCPlatformMacros.h"
#include <napi/native_api.h>
#include <string>

NS_CC_BEGIN
class CCArkJsLanguage{
public:
    static napi_value initCCArkJsLanguage(napi_env env, napi_callback_info info);
    static std::string getSystemLanguage();
    static napi_value getEngineFunc(const char* funcName);
    
private:
    static napi_env _env;
};
NS_CC_END