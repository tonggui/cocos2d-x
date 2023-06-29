#include <stdlib.h>
#include "CCLogOhos.h"
#include <string>
#include "CCArkJsLanguage.h"
#include "CCArkJSWant.h"
#include "base/CCEvent.h"
#include "base/ccTypes.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

// #include "cocoa/CCString.h"
#include "Cocos2dxHelper.h"

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

using namespace cocos2d;

void terminateProcess() {
    OHOS_LOGI("terminateProcess - exit");
    exit(0);
}

std::string getLanguage() {
    std::string ret = cocos2d::CCArkJsLanguage::getSystemLanguage();
    return ret;
}

void enableAccelerometer() {
}

void setAccelerometerInterval(float interval) {
}

void disableAccelerometer() {
}

bool implicitStartAbility(const char* url){
    return  cocos2d::CCArkJsWant::implicitStartAbility(url);
}



