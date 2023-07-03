// @ts-nocheck
import hilog from '@ohos.hilog';
import nativerender from "libnativerender.so";
import { ContextType } from "../common/Constants"
import { WorkerManager } from "../workers/WorkerManager"
import { TextInputDialog} from "@ohos/libcocos2dx/src/main/ets/components/editbox/TextInputDialogUtils"
import ThreadUtils from "@ohos/libcocos2dx/src/main/ets/components/thread/ThreadUtils"
import { CocosWebView } from "../components/CocosWebview"
import { CocosVideoPlayer } from "../components/CocosVideoPlayer"
import { WebViewInfo } from "@ohos/libcocos2dx/src/main/ets/components/webview/WebView"
import {VideoPlayerInfo} from '@ohos/libcocos2dx/src/main/ets/components/videoplayer/VideoPlayerInfo'
const nativePageLifecycle = nativerender.getContext(ContextType.JSPAGE_LIFECYCLE);

@Entry
@Component
struct Index {
  private context = null;
  cocosWorker = WorkerManager.getInstance().getWorker();

  // WebView
  @State webViewArray: WebViewInfo[] = [];
  private webViewIndexMap: Map<number, number> = new Map;

  // videoPlayerInfo Array
  @State videoPlayerInfoArray: VideoPlayerInfo[] = [];
  private videoPlayerIndexMap: Map<number, number> = new Map;
  // VideoPlay
  private surfaceId: string = '';
  xcomponentController: XComponentController = new XComponentController();
  
  //showMessage: string = ''
  @State showMessage: object = {message : ""}
  dialogController: CustomDialogController = new CustomDialogController({
    builder: TextInputDialog({
      showMessage: this.showMessage,
      accept: (msg: string) => {
        this.showMessage["message"] = msg;
        this.cocosWorker.postMessage({type: "onComplete", text: msg})
      },
    }),
    cancel: () => {
     this.cocosWorker.postMessage({type: "onComplete", text: this.showMessage["message"]})
    },
    autoCancel: true,
    alignment: DialogAlignment.Bottom,
    customStyle: true,
  })

  onPageShow() {
    console.log('[LIFECYCLE-Page] onPageShow');
    globalThis.dialogController = this.dialogController;
    globalThis.showMessage = this.showMessage;
    globalThis.webViewArray = this.webViewArray;
    globalThis.webViewIndexMap = this.webViewIndexMap;
    globalThis.videoPlayerInfoArray = this.videoPlayerInfoArray;
    globalThis.videoPlayerIndexMap = this.videoPlayerIndexMap;
    nativePageLifecycle.onPageShow();
  }

  onPageHide() {
    console.log('[LIFECYCLE-Page] onPageHide');
    nativePageLifecycle.onPageHide();
  }
  
  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      XComponent({ id: 'xcomponentId', type: 'surface', libraryname: 'nativerender'})
        .onLoad((context) => {
          console.log('[cocos] XComponent.onLoad Callback');
          this.context = context;
          this.surfaceId = this.xcomponentController.getXComponentSurfaceId()
          this.cocosWorker.postMessage({ type: "onXCLoad", data: globalThis.abilityContext });
          this.cocosWorker.postMessage({ type: "avPlayVideoInit", data: this.surfaceId });
          this.cocosWorker.onmessage = ThreadUtils.recvWorkerThreadMessage;
        })
        .onDestroy(() => {
        })
      ForEach(this.webViewArray, (item) => {
        CocosWebView({ viewInfo: item, cocosWorker: this.cocosWorker })
      }, item => item.x + item.y + item.w + item.h + item.url + item.viewTag + item.zoomAccess + item.visible)

      ForEach(this.videoPlayerInfoArray, (item) => {
        CocosVideoPlayer({ videoPlayerInfo: item, cocosWorker: this.cocosWorker })
      }, item => item.x + item.y + item.w + item.h + item.url + item.viewTag+item.visible)
    }
    .width('100%')
    .height('100%')
  }
}
