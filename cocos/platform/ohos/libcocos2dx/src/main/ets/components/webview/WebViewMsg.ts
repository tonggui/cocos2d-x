import hilog from '@ohos.hilog';
import { WebViewInfo, copyWebViewInfo } from './WebView'

export function handleWebViewMsg(eventData: any) {
    let index;
    switch (eventData.function) {
        case "createWebView":
            hilog.debug(0x0001, "index.ts", "createWebView start, viewTag:%{public}d", eventData.viewTag);
            globalThis.webViewArray.push(new WebViewInfo(0, 0, 0, 0, eventData.viewTag));
            globalThis.webViewIndexMap.set(eventData.viewTag, globalThis.webViewArray.length - 1);
            break;
        case "removeWebView": {
            hilog.debug(0x0001, "index.ts", "removeWebView start, viewTag:%{public}d", eventData.viewTag);
            if (globalThis.webViewArray.length > 0) {
                index = globalThis.webViewIndexMap.get(eventData.viewTag);
                globalThis.webViewArray.splice(index, 1);
                // 不可假定 removeWebView 的调用时机，在删除某元素后，其后面的元素，位置需要前进1位
                globalThis.webViewIndexMap.forEach((value: number, key: number, map: Map<number, number>) => {
                    if (value > index) {
                        globalThis.webViewIndexMap.set(key, value - 1);
                    }
                })
                // 删除被 remove 的 webView 的下标映射
                globalThis.webViewIndexMap.delete(eventData.viewTag);
            }
            hilog.debug(0x0001, "index.ts", "removeWebView end");
            break;
        }
        case "loadData":
            hilog.debug(0x0001, "index.ts", "loadData start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            globalThis.webViewArray[index].controller.loadData(eventData.data, eventData.mimeType, eventData.encoding, eventData.baseURL)
            break;
        case "loadURL":
            hilog.debug(0x0001, "index.ts", "viewTag:%{public}d, loadURL:%{public}s start", eventData.viewTag, eventData.url);
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            globalThis.webViewArray[index].url = eventData.url;
            globalThis.webViewArray[index].controller.loadUrl(eventData.url);
            break;
        case "stopLoading":
            hilog.debug(0x0001, "index.ts", "stopLoading start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            globalThis.webViewArray[index].controller.stop();
            break;
        case "reload":
            hilog.debug(0x0001, "index.ts", "reload start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            globalThis.webViewArray[index].controller.refresh();
            break;
        case "canGoBack":
            hilog.debug(0x0001, "index.ts", "canGoBack start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            let result = globalThis.webViewArray[index].controller.accessBackward();
        // todo 需要将该值回传 worker 线程
            break;
        case "canGoForward":
            hilog.debug(0x0001, "index.ts", "canGoForward start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            result = globalThis.webViewArray[index].controller.accessForward();
        // todo 需要将该值回传 worker 线程
            break;
        case "goBack":
            hilog.debug(0x0001, "index.ts", "goBack start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            globalThis.webViewArray[index].controller.backward();
            break;
        case "goForward":
            hilog.debug(0x0001, "index.ts", "goForward start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            globalThis.webViewArray[index].controller.forward();
            break;
        case "setWebViewRect": {
            hilog.debug(0x0001, "index.ts", "setWebViewRect start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            globalThis.webViewArray[index].x = px2vp(eventData.x);
            globalThis.webViewArray[index].y = px2vp(eventData.y);
            globalThis.webViewArray[index].w = px2vp(eventData.w);
            globalThis.webViewArray[index].h = px2vp(eventData.h);
            let newViewInfo = copyWebViewInfo(globalThis.webViewArray[index]);
            globalThis.webViewArray[index] = newViewInfo;
            hilog.debug(0x0001, "index.ts", "setWebViewRect end, x=%{public}d, y=%{public}d, w=%{public}d, h=%{public}d", globalThis.webViewArray[index].x, globalThis.webViewArray[index].y, globalThis.webViewArray[index].w, globalThis.webViewArray[index].h);
            break;
        }
        case "setVisible": {
            hilog.debug(0x0001, "index.ts", "setVisible:%{public}s start, viewTag:%{public}d", eventData.visible, eventData.viewTag);
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            if (globalThis.webViewArray[index].visible == eventData.visible) {
                return;
            }
            globalThis.webViewArray[index].visible == eventData.visible
            let newViewInfo = copyWebViewInfo(globalThis.webViewArray[index]);
            globalThis.webViewArray[index] = newViewInfo;
            break;
        }
        case "evaluateJS": {
            hilog.debug(0x0001, "index.ts", "evaluateJS start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            globalThis.webViewArray[index].controller.runJavaScript(eventData.js, (error, result) => {
                if (error) {
                    hilog.warn(0x0001, "index.ts", "webView run JavaScript error:%{public}s", JSON.stringify(error));
                    return;
                }
                if (result) {
                    globalThis.webResult = result;
                    hilog.debug(0x0001, "index.ts", "webView run JavaScript result is %{public}d:", result);
                }
            })
            break;
        }
        case "setScalesPageToFit": {
            hilog.debug(0x0001, "index.ts", "setScalesPageToFit start");
            index = globalThis.webViewIndexMap.get(eventData.viewTag);
            if (globalThis.webViewArray[index].zoomAccess == eventData.zoomAccess) {
                return;
            }
            globalThis.webViewArray[index].zoomAccess == eventData.zoomAccess
            let newViewInfo = copyWebViewInfo(globalThis.webViewArray[index]);
            globalThis.webViewArray[index] = newViewInfo;
        }
            break;
    }
}