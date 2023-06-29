/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import worker from '@ohos.worker';
import nativerender from "libnativerender.so";
import { ContextType } from "../common/Constants"
import "@ohos/libcocos2dx/src/main/ets/components/audio/AudioEngine"
import "@ohos/libcocos2dx/src/main/ets/components/display/getDpi"
import "@ohos/libcocos2dx/src/main/ets/components/language/LanguageUtils"
import "@ohos/libcocos2dx/src/main/ets/components/want/WantUtils"
import CCDialogUtils from "@ohos/libcocos2dx/src/main/ets/components/dialog/CCDialogWorkerUtils"
import Accelerometer from "@ohos/libcocos2dx/src/main/ets/components/sensor/AccelerometerUtils"
import WebView from "@ohos/libcocos2dx/src/main/ets/components/webview/WebView"
import VideoPlayer from "@ohos/libcocos2dx/src/main/ets/components/videoplayer/VideoPlayerInfo"

console.log("[cocos] native render workerInit =-------> ");
const nativeContext = nativerender.getContext(ContextType.WORKER_INIT);
const editBoxNapi = nativerender.getContext(ContextType.EDITBOX_NAPI);
const webViewNapi = nativerender.getContext(ContextType.WEBVIEW_NAPI);
nativeContext.workerInit()
const parentPort = worker.parentPort;
CCDialogUtils.init(parentPort);
WebView.init(parentPort);
VideoPlayer.init(parentPort);
Accelerometer.init();

parentPort.onmessage = function(e) {
    var data = e.data;
    switch(data.type) {
        case "onXCLoad":
            console.log("[cocos] onXCLoad Callback");
            const renderContext = nativerender.getContext(ContextType.NATIVE_RENDER_API);
            renderContext.nativeEngineStart();
            globalThis.abilityContext = data.data;
            break;

        case "onTextInput":
            editBoxNapi.onTextInsert(data.text);
            break;
        case "onTextDelete":
            editBoxNapi.onTextDelete();
            break;
        case "onComplete":
            editBoxNapi.onComplete(data.text);
            break;
        case "onPageBegin":
            webViewNapi.shouldStartLoading(data.viewTag, data.url);
            break;
        case "onPageEnd":
            webViewNapi.finishLoading(data.viewTag, data.url);
            break;
        case "onErrorReceive":
            webViewNapi.failLoading(data.viewTag, data.url);
            break;
        default:
            console.error("cocos worker: message type unknown")
    }
}


