import hilog from '@ohos.hilog';
import DialogUtils from '../dialog/DialogUtils'
import { handleWebViewMsg } from '../webview/WebViewMsg'
import { handleVideoPlayMsg } from '../videoplayer/VideoPlayerMsg'


let logTag = 'ThreadUtils';

export default class ThreadUtils {
    static recvWorkerThreadMessage(event) {
        var eventData = event.data;
        hilog.debug(0x0000, logTag, 'mainThread receiveMsg, module:%{public}s, function:%{public}s', eventData.module, eventData.function);
        switch (eventData.module) {
            case 'WebView':
                handleWebViewMsg(eventData);
                break;
            case 'VideoPlay':
                handleVideoPlayMsg(eventData);
                break;
            default:
                // hilog.error(0x0000, logTag, '%{public}s has not implement yet', eventData.module);
        }

        // TODO 后面的switch待整合
        switch (eventData.function) {
            case "showDialog":
                let title = eventData.title;
                let message = eventData.message;
                DialogUtils.showDialog(title, message);
                break;
            case "showTextInputDialog":
                globalThis.showMessage["message"] = eventData.msg;
                globalThis.dialogController.open();
                break;
            case "hideTextInputDialog":
                globalThis.showMessage["message"] = '';
                globalThis.dialogController.close();
                break;
        }
    }

}
