#include "platform/CCPlatformMacros.h"
#include <napi/native_api.h>

NS_CC_BEGIN
class CCArkDisplay {
public:
    static napi_value initCCArkDisplay(napi_env env, napi_callback_info info);
    static int getDpi();
    static napi_value getEngineFunc(const char* funcName);

private:
    static napi_env _env;
};
NS_CC_END
