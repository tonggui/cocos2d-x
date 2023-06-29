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
import { WebViewInfo } from "@ohos/libcocos2dx/src/main/ets/components/webview/WebView"
import worker from '@ohos.worker';

@Component
export struct CocosWebView {
  viewInfo: WebViewInfo;
  cocosWorker: worker.Worker;

  build() {
    Web({ src: this.viewInfo.url, controller: this.viewInfo.controller })
      .position({ x: this.viewInfo.x, y: this.viewInfo.y })
      .width(this.viewInfo.w)
      .height(this.viewInfo.h)
      .border({ width: 1 })
      .domStorageAccess(true)
      .databaseAccess(true)
      .imageAccess(true) // 默认允许
      .onlineImageAccess(true) // 默认允许
      .zoomAccess(this.viewInfo.zoomAccess) // 默认允许
      .javaScriptAccess(true) // 默认允许
      .visibility(this.viewInfo.visible ? Visibility.Visible : Visibility.None)
      .onPageBegin((event) => {
        console.log("webview onPageBegin");
        this.cocosWorker.postMessage({ type: "onPageBegin", viewTag: this.viewInfo.viewTag, url: event.url });
      })
      .onPageEnd((event) => {
        console.log("webview onPageEnd");
        this.cocosWorker.postMessage({ type: "onPageEnd", viewTag: this.viewInfo.viewTag, url: event.url })
      })
      .onErrorReceive((event) => {
        onErrorReceive(event);
        this.cocosWorker.postMessage({ type: "onErrorReceive", viewTag: this.viewInfo.viewTag, url: this.viewInfo.url })
      })
      .onHttpErrorReceive((event) => {
        onHttpErrorReceive(event);
        this.cocosWorker.postMessage({ type: "onErrorReceive", viewTag: this.viewInfo.viewTag, url: this.viewInfo.url })
      })
  }
}

function onErrorReceive(event: any): void {
  console.log('getErrorInfo:' + event.error.getErrorInfo())
  console.log('getErrorCode:' + event.error.getErrorCode())
  console.log('url:' + event.request.getRequestUrl())
  console.log('isMainFrame:' + event.request.isMainFrame())
  console.log('isRedirect:' + event.request.isRedirect())
  console.log('isRequestGesture:' + event.request.isRequestGesture())
  console.log('getRequestHeader_headerKey:' + event.request.getRequestHeader().toString())
  let result = event.request.getRequestHeader()
  console.log('The request header result size is ' + result.length)
  for (let i of result) {
    console.log('The request header key is : ' + i.headerKey + ', value is : ' + i.headerValue)
  }
}

function onHttpErrorReceive(event: any): void {
  console.log('url:' + event.request.getRequestUrl())
  console.log('isMainFrame:' + event.request.isMainFrame())
  console.log('isRedirect:' + event.request.isRedirect())
  console.log('isRequestGesture:' + event.request.isRequestGesture())
  console.log('getResponseData:' + event.response.getResponseData())
  console.log('getResponseEncoding:' + event.response.getResponseEncoding())
  console.log('getResponseMimeType:' + event.response.getResponseMimeType())
  console.log('getResponseCode:' + event.response.getResponseCode())
  console.log('getReasonMessage:' + event.response.getReasonMessage())
  let result = event.request.getRequestHeader()
  console.log('The request header result size is ' + result.length)
  for (let i of result) {
    console.log('The request header key is : ' + i.headerKey + ' , value is : ' + i.headerValue)
  }
  let resph = event.response.getResponseHeader()
  console.log('The response header result size is ' + resph.length)
  for (let i of resph) {
    console.log('The response header key is : ' + i.headerKey + ' , value is : ' + i.headerValue)
  }
}