import hilog from '@ohos.hilog';

export default class CCDialogUtils {
    static parentPort;
    static init(parentPort) {
        CCDialogUtils.parentPort = parentPort;
    }
    static showDialogPostToMainThread(message, title)  {
        CCDialogUtils.parentPort.postMessage({'function': 'showDialog', 'title': title, 'message': message});
    }

    static showTextInputDialogPostToMainThread(msg: string) {
        CCDialogUtils.parentPort.postMessage({ 'function': 'showTextInputDialog', 'msg': msg });
    }

    static hideTextInputDialogPostToMainThread(msg: string) {
        CCDialogUtils.parentPort.postMessage({ 'function': 'hideTextInputDialog' });
    }
}
globalThis.ccDialogUtils={};
globalThis.ccDialogUtils.showDialog = CCDialogUtils.showDialogPostToMainThread;
globalThis.ccDialogUtils.showTextInputDialog = CCDialogUtils.showTextInputDialogPostToMainThread;
globalThis.ccDialogUtils.hideTextInputDialog = CCDialogUtils.hideTextInputDialogPostToMainThread;