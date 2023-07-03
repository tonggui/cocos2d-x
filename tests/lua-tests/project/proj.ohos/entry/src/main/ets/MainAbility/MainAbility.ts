// @ts-nocheck
import nativerender from "libnativerender.so";
import Ability from '@ohos.application.Ability';
import web_webview from '@ohos.web.webview';
import { ContextType } from "../common/Constants"
import Window from '@ohos.window';
const nativeAppLifecycle = nativerender.getContext(ContextType.APP_LIFECYCLE);
const rawFileUtils = nativerender.getContext(ContextType.RAW_FILE_UTILS);

export default class MainAbility extends Ability {
    onCreate(want, launchParam) {
        let windowClass = null;
        try {
            Window.getLastWindow(this.context, (err, data) => { //获取窗口实例
                if (err.code) {
                    console.error('Failed to obtain the top window. Cause: ' + JSON.stringify(err));
                    return;
                }
                windowClass = data;
                let names = [];  //设置状态栏和导航栏是否显示，不显示则为[]
                let isLayoutFullScreen = true;  //窗口的布局是否为全屏显示状态
                let isKeepScreenOn = true;  //设置屏幕是否为常亮状态
                let barEnablePromise = windowClass.setWindowSystemBarEnable(names);
                let fullScreenPromise = windowClass.setWindowLayoutFullScreen(isLayoutFullScreen);
                let keepScreenOnPromise = windowClass.setWindowKeepScreenOn(isKeepScreenOn);
                Promise.all([barEnablePromise,fullScreenPromise,keepScreenOnPromise]).then(()=> {
                    console.info('Succeeded in setting the window .');
                }).catch((err)=>{
                    console.error('Failed to set the window layout. Cause:' + JSON.stringify(err));
                });
            });
        } catch (exception) {
            console.error('Failed to set the window layout. Cause:' + JSON.stringify(err));
        }
        nativeAppLifecycle.onCreate();
        globalThis.abilityContext = this.context;
        web_webview.WebviewController.initializeWebEngine();
        globalThis.abilityWant = want;
        console.info('[LIFECYCLE-App] onCreate')
    }

    onDestroy() {
        nativeAppLifecycle.onDestroy();
        console.info('[LIFECYCLE-App] onDestroy')
    }

    onWindowStageCreate(windowStage) {
        // Main window is created, set main page for this ability
        windowStage.loadContent('pages/Index', (err, data) => {
            if (err.code) {
                return;
            }
            rawFileUtils.nativeResourceManagerInit(this.context.resourceManager);
            rawFileUtils.writablePathInit(this.context.cacheDir);
        });
    }

    onWindowStageDestroy() {
        // Main window is destroyed, release UI related resources

    }

    onForeground() {
        // Ability has brought to foreground
        console.info('[LIFECYCLE-App] onShow')
        nativeAppLifecycle.onShow();
    }

    onBackground() {
        // Ability has back to background
        console.info('[LIFECYCLE-App] onDestroy')
        nativeAppLifecycle.onHide();
    }
};
