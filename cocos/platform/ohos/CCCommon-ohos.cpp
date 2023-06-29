/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/CCCommon.h"
// #include "napi/modules/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "CCArkJsDialog.h"
#include "CCLogOhos.h"
#include <stdio.h>
// #include <jni.h>

NS_CC_BEGIN

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

void MessageBox(const char * pszMsg, const char * pszTitle)
{
    std::string msg(pszMsg);
    std::string title(pszTitle);
    CCArkJsDialog::showDialog(msg, title);
}

void LuaLog(const char * pszFormat)
{
    OHOS_LOGI("cocos2d-x debug info %s", pszFormat);
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS