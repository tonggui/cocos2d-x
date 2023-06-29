import hilog from '@ohos.hilog'
import web_webview from '@ohos.web.webview'

export class WebViewInfo {
    // position
    public x: number = 0;
    public y: number = 0;
    // size
    public w: number = 0;
    public h: number = 0;
    // url
    public url: string = '';
    // tag
    public viewTag: number = 0
    // Whether zoom is supported
    public zoomAccess: boolean = true
    // Whether to display
    public visible: boolean = true
    /*
     * doc : https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/arkui-ts/ts-basic-components-web.md#webcontroller
     */
    public controller: web_webview.WebviewController = new web_webview.WebviewController()

    constructor(x: number, y: number, w: number, h: number, viewTag: number) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.viewTag = viewTag
    }
}

export function copyWebViewInfo(viewInfo: WebViewInfo) {
    let newViewInfo = new WebViewInfo(viewInfo.x, viewInfo.y, viewInfo.w, viewInfo.h, viewInfo.viewTag);
    newViewInfo.url = viewInfo.url;
    newViewInfo.zoomAccess = viewInfo.zoomAccess;
    newViewInfo.visible = viewInfo.visible;
    newViewInfo.controller = viewInfo.controller;
    return newViewInfo;
}

export default class WebView {
    static MODULE_NAME: string = 'WebView';

    private static parentPort;

    static init(parentPort) {
        WebView.parentPort = parentPort;
    }

    static postFunctionNameAndViewTag(functionName: string, viewTag: number) {
        WebView.parentPort.postMessage({
            'module': WebView.MODULE_NAME, 'function': functionName, 'viewTag': viewTag
        });
    }

    static postLoadData(viewTag: number, data: string, mimeType: string, encoding: string, baseURL: string) {
        hilog.debug(0x0001, "webView.ts", "postLoadData start");
        WebView.parentPort.postMessage({
            'module': WebView.MODULE_NAME,
            'function': 'loadData',
            'viewTag': viewTag,
            'data': data,
            'mimeType': mimeType,
            'encoding': encoding,
            'baseURL': baseURL
        });
        hilog.debug(0x0001, "webView.ts", "postLoadData end");
    }

    static postLoadURL(viewTag: number, url: string) {
        hilog.debug(0x0001, "webView.ts", "postLoadURL start");
        WebView.parentPort.postMessage({
            'module': WebView.MODULE_NAME, 'function': 'loadURL', 'viewTag': viewTag, 'url': url
        });
        hilog.debug(0x0001, "webView.ts", "postLoadURL end");
    }


    static postSetWebViewRect(viewTag: number, x: number, y: number, w: number, h: number) {
        hilog.debug(0x0001, "webView.ts", "setWebViewRect start, x=%{public}d, y=%{public}d, w=%{public}d, h=%{public}d", x, y, w, h);
        WebView.parentPort.postMessage({
            'module': WebView.MODULE_NAME,
            'function': 'setWebViewRect',
            'viewTag': viewTag,
            'x': x,
            'y': y,
            'w': w,
            'h': h
        });
        hilog.debug(0x0001, "webView.ts", "setWebViewRect end");
    }

    static postSetVisible(viewTag: number, visible: boolean) {
        hilog.debug(0x0001, "webView.ts", "setVisible start");
        WebView.parentPort.postMessage({
            'module': WebView.MODULE_NAME, 'function': 'setVisible', 'viewTag': viewTag, 'visible': visible
        });
        hilog.debug(0x0001, "webView.ts", "setVisible end");
    }

    static postEvaluateJS(viewTag: number, js: string) {
        hilog.debug(0x0001, "webView.ts", "evaluateJS start");
        WebView.parentPort.postMessage({
            'module': WebView.MODULE_NAME, 'function': 'evaluateJS', 'viewTag': viewTag, 'js': js
        });
        hilog.debug(0x0001, "webView.ts", "evaluateJS end");
    }

    static postSetScalesPageToFit(viewTag: number, scalesPageToFit: boolean) {
        hilog.debug(0x0001, "webView.ts", "setScalesPageToFit start");
        WebView.parentPort.postMessage({
            'module': WebView.MODULE_NAME,
            'function': 'setScalesPageToFit',
            'viewTag': viewTag,
            'zoomAccess': scalesPageToFit
        });
        hilog.debug(0x0001, "webView.ts", "setScalesPageToFit end");
    }
}

globalThis.WebView = {};
globalThis.WebView.functionNameAndViewTag = WebView.postFunctionNameAndViewTag;
globalThis.WebView.loadData = WebView.postLoadData;
globalThis.WebView.loadURL = WebView.postLoadURL;
globalThis.WebView.setWebViewRect = WebView.postSetWebViewRect;
globalThis.WebView.setVisible = WebView.postSetVisible;
globalThis.WebView.evaluateJS = WebView.postEvaluateJS;
globalThis.WebView.setScalesPageToFit = WebView.postSetScalesPageToFit;