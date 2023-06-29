/****************************************************************************
 Copyright (c) 2022-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/
#include "ui/UIWebViewImpl-ohos.h"

#include <cstdlib>
#include <string>
#include <unordered_map>

#include "ui/UIWebView.h"
#include "ui/UIHelper.h"
#include "platform/CCFileUtils.h"
#include "platform/ohos/CCLogOhos.h"
#include "platform/ohos/CCArkWebView.h"

static const std::string S_DEFAULT_BASE_URL = "file:///openharmony_asset/";
static const std::string S_SD_ROOT_BASE_URL = "file://";
static const char S_MIME_TYPE_TEXT[] = "text/html";
static const char S_ENCODING_UTF8[] = "UTF-8";

// TODO 暂不知道有什么用处
static std::string getFixedBaseUrl(const std::string &baseUrl) {

    std::string fixedBaseUrl;
    if (baseUrl.empty()) {
        fixedBaseUrl = S_DEFAULT_BASE_URL;
    } else if (baseUrl.find(S_SD_ROOT_BASE_URL) != std::string::npos) {
        fixedBaseUrl = baseUrl;
    } else if (baseUrl.c_str()[0] != '/') {
        if (baseUrl.find("assets/") == 0) {
            fixedBaseUrl = S_DEFAULT_BASE_URL + baseUrl.c_str()[7];
        } else {
            fixedBaseUrl = S_DEFAULT_BASE_URL + baseUrl;
        }
    } else {
        fixedBaseUrl = S_SD_ROOT_BASE_URL + baseUrl;
    }

    if (fixedBaseUrl.c_str()[fixedBaseUrl.length() - 1] != '/') {
        fixedBaseUrl += "/";
    }

    return fixedBaseUrl;
}

static std::string getUrlStringByFileName(const std::string &fileName) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    const std::string basePath(S_DEFAULT_BASE_URL);
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
    const std::string assetsPath("assets/");

    std::string urlString;
    if (fullPath.find(assetsPath) != std::string::npos) {
        urlString = fullPath.replace(fullPath.find_first_of(assetsPath), assetsPath.length(), basePath);
    } else {
        urlString = fullPath;
    }

    return urlString;
}

namespace cocos2d {
    namespace experimental {
        namespace ui{
static int32_t kWebViewTag = 0;
static std::unordered_map<int, WebViewImpl*> sWebViewImpls;

WebViewImpl::WebViewImpl(WebView *webView) : _viewTag(-1), _webView(webView) {
    _viewTag = kWebViewTag++;
    CCArkWebView::generalFuncParamOnlyViewTagWithoutReturn(CCArkWebView::CREATE_WEBVIEW, _viewTag);
    sWebViewImpls[_viewTag] = this;
    // TODO 当前 web 组件和 controller 的绑定有延时，此处睡眠避免错误，后续通过API10可能开放的回调函数onControllerAttached来控制
    OHOS_LOGD("webview will sleep for 2s");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    OHOS_LOGD("webview sleeped end");
}

WebViewImpl::~WebViewImpl() {
    if (_viewTag != -1) {
        CCArkWebView::generalFuncParamOnlyViewTagWithoutReturn(CCArkWebView::REMOVE_WEBVIEW, _viewTag);
        auto iter = sWebViewImpls.find(_viewTag);
            if (iter != sWebViewImpls.end()) {
                sWebViewImpls.erase(iter);
            }
        _viewTag = -1;
    }
}

void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme) {
    // TODO(qgh):OpenHarmony does not support this interface.
}

void WebViewImpl::loadData(const Data &data, const std::string &mimeType,
                           const std::string &encoding, const std::string &baseURL) {
    std::string dataString(reinterpret_cast<char *>(data.getBytes()), static_cast<unsigned int>(data.getSize()));
    CCArkWebView::loadData(_viewTag, dataString.c_str(), mimeType.c_str(), encoding.c_str(), baseURL.c_str());
}

void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL) {
    CCArkWebView::loadData(_viewTag, string.c_str(), S_MIME_TYPE_TEXT, S_ENCODING_UTF8, baseURL.c_str());
}

void WebViewImpl::loadURL(const std::string &url) {
    CCArkWebView::loadURL(_viewTag, url.c_str());
}

void WebViewImpl::loadURL(const std::string &url, bool cleanCachedData) {
    // 官网接口未提供缓存相关参数，故与上一个loadUrl实现一致
    CCArkWebView::loadURL(_viewTag, url.c_str());
}

// TODO 当前仅支持绝对路径或rawfile目录，待完善功能
void WebViewImpl::loadFile(const std::string &fileName) {
    std::string fullPath = getUrlStringByFileName(fileName);
    if(fullPath == fileName) {
        fullPath = "resource://rawfile/" + fileName;
    }
    CCArkWebView::loadURL(_viewTag, fullPath.c_str());
}

void WebViewImpl::stopLoading() {
    CCArkWebView::generalFuncParamOnlyViewTagWithoutReturn(CCArkWebView::STOP_LOADING, _viewTag);
}

void WebViewImpl::reload() {
    CCArkWebView::generalFuncParamOnlyViewTagWithoutReturn(CCArkWebView::RELOAD, _viewTag);
}

bool WebViewImpl::canGoBack() {
    return CCArkWebView::generalFuncParamOnlyViewTagReturnBool(CCArkWebView::CAN_GO_BACK, _viewTag);
}

bool WebViewImpl::canGoForward() {
    return CCArkWebView::generalFuncParamOnlyViewTagReturnBool(CCArkWebView::CAN_GO_FORWARD, _viewTag);
}

void WebViewImpl::goBack() {
   CCArkWebView::generalFuncParamOnlyViewTagWithoutReturn(CCArkWebView::GO_BACK, _viewTag);
}

void WebViewImpl::goForward() {
   CCArkWebView::generalFuncParamOnlyViewTagWithoutReturn(CCArkWebView::GO_FORWARD, _viewTag);
}

void WebViewImpl::evaluateJS(const std::string &js) {
    CCArkWebView::evaluateJS(_viewTag, js.c_str());
}

void WebViewImpl::setScalesPageToFit(bool scalesPageToFit) {
    CCArkWebView::setScalesPageToFit(_viewTag, scalesPageToFit);
}

void WebViewImpl::draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) {
    if (flags & cocos2d::Node::FLAGS_TRANSFORM_DIRTY) {
        auto uiRect = cocos2d::ui::Helper::convertBoundingBoxToScreen(_webView);
        CCArkWebView::setWebViewRect(_viewTag, (int)uiRect.origin.x, (int)uiRect.origin.y, (int)uiRect.size.width, (int)uiRect.size.height);
    }
}

void WebViewImpl::setVisible(bool visible) {
    CCArkWebView::setVisible(_viewTag, visible);
}



void WebViewImpl::setBounces(bool bounces) {
    // empty function as this was mainly a fix for iOS
}

void WebViewImpl::setOpacityWebView(const float opacity){
    // TODO 官网未有相关接口，https://docs.openharmony.cn/pages/v3.2/zh-cn/application-dev/reference/arkui-ts/ts-basic-components-web.md/#web
}
            
            
float WebViewImpl::getOpacityWebView()const{
         return 0.1f;       
}
            
void WebViewImpl::setBackgroundTransparent(){
    // TODO 官网未有相关接口，https://docs.openharmony.cn/pages/v3.2/zh-cn/application-dev/reference/apis/js-apis-webview.md/#initializewebengine
}

bool WebViewImpl::shouldStartLoading(int viewTag, const std::string& url) {
    bool allowLoad = true;
    auto it = sWebViewImpls.find(viewTag);
    if (it != sWebViewImpls.end()) {
        auto webView = it->second->_webView;
        if (webView->getOnShouldStartLoading()) {
            std::function<bool(WebView *sender, const std::string &url)> fun = webView->getOnShouldStartLoading();
            allowLoad = fun(webView, url);
        }
    }
    return allowLoad;
}
                
void WebViewImpl::finishLoading(int viewTag, const std::string& url) {
    auto it = sWebViewImpls.find(viewTag);
    if (it != sWebViewImpls.end()) {
        auto webView = it->second->_webView;
        if (webView->getOnDidFinishLoading()) {
            WebView::ccWebViewCallback fun = webView->getOnDidFinishLoading();
            fun(webView, url);
        }
    }
}

void WebViewImpl::failLoading(int viewTag, const std::string& url) {
    auto it = sWebViewImpls.find(viewTag);
    if (it != sWebViewImpls.end()) {
        auto webView = it->second->_webView;
        if (webView->getOnDidFailLoading()) {
            WebView::ccWebViewCallback fun = webView->getOnDidFailLoading();
            fun(webView, url);
        }
    }
}
                
void WebViewImpl::jsCallback(int viewTag, const std::string& message) {
    auto it = sWebViewImpls.find(viewTag);
    if (it != sWebViewImpls.end()) {
        auto webView = it->second->_webView;
        if (webView->getOnJSCallback()) {
            WebView::ccWebViewCallback fun = webView->getOnJSCallback();
            fun(webView, message);
        }
    }
}

} //namespace ui
}//namespace experimental
}//namespace cocos2d
