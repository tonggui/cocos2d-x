import hilog from '@ohos.hilog';
import { VideoPlayerInfo, cloneVideoPlayerInfo} from './VideoPlayerInfo'

export function handleVideoPlayMsg(eventData: any) {
    let index;
    switch (eventData.function) {
        case "createVideoPlayer":
            hilog.debug(0x0001, "index.ts", "createVideoPlayer start, viewTag:%{public}d", eventData.viewTag);
            globalThis.videoPlayerInfoArray.push(new VideoPlayerInfo(0, 0, 0, 0, eventData.viewTag));
            globalThis.videoPlayerIndexMap.set(eventData.viewTag, globalThis.videoPlayerInfoArray.length - 1);
            hilog.debug(0x0001, "index.ts", "createVideoPlayer end");
            break;
        case "removeVideoPlayer": {
            hilog.debug(0x0001, "index.ts", "createVideoPlayer start, viewTag:%{public}d", eventData.viewTag);
            if (globalThis.videoPlayerInfoArray.length > 0) {
                index = globalThis.videoPlayerIndexMap.get(eventData.viewTag);
                globalThis.videoPlayerInfoArray.splice(index, 1);
                // 不可假定 removeVideoPlayer 的调用时机，在删除某元素后，其后面的元素，位置需要前进1位
                globalThis.videoPlayerIndexMap.forEach((value: number, key: number, map: Map<number, number>) => {
                    if (value > index) {
                        globalThis.videoPlayerIndexMap.set(key, value - 1);
                    }
                })
                // 删除被 remove 的 videoPlayer 的下标映射
                globalThis.videoPlayerIndexMap.delete(eventData.viewTag);
            }
            hilog.debug(0x0001, "index.ts", "removeVideoPlayer end");
            break;
        }
        case "play":
            hilog.debug(0x0001, "index.ts", "viewTag:%{public}d, play:%{public}s start", eventData.viewTag);
            index = globalThis.videoPlayerIndexMap.get(eventData.viewTag);
            globalThis.videoPlayerInfoArray[index].controller.start();
            globalThis.videoPlayerInfoArray[index].isPlay = true;
            hilog.debug(0x0001, "index.ts", "controller start end");
            break;
        case "pause":
            hilog.debug(0x0001, "index.ts", "viewTag:%{public}d, pause:%{public}s pause", eventData.viewTag);
            index = globalThis.videoPlayerIndexMap.get(eventData.viewTag);
            globalThis.videoPlayerInfoArray[index].controller.pause();
            globalThis.videoPlayerInfoArray[index].isPlay = false;
            hilog.debug(0x0001, "index.ts", "controller pause end");
            break;
        case "stop":
            hilog.debug(0x0001, "index.ts", "viewTag:%{public}d, stop:%{public}s start", eventData.viewTag);
            index = globalThis.videoPlayerIndexMap.get(eventData.viewTag);
            globalThis.videoPlayerInfoArray[index].controller.stop();
            globalThis.videoPlayerInfoArray[index].isPlay = false;
            hilog.debug(0x0001, "index.ts", "controller stop end");
            break;
        case "setURL":
            hilog.debug(0x0001, "index.ts", "viewTag:%{public}d, setURL:%{public}s start", eventData.viewTag, eventData.url);
            index = globalThis.videoPlayerIndexMap.get(eventData.viewTag);
            globalThis.videoPlayerInfoArray[index].url = eventData.url;
            let videoPlayerInfo = cloneVideoPlayerInfo(globalThis.videoPlayerInfoArray[index]);
            globalThis.videoPlayerInfoArray[index] = videoPlayerInfo;
            hilog.debug(0x0001, "index.ts", "setURL end");
            break;
        case "postSetVideoPlayerRect":
            hilog.debug(0x0001, "index.ts", "postSetVideoPlayerRect start");
            index = globalThis.videoPlayerIndexMap.get(eventData.viewTag);
            try {
                globalThis.videoPlayerInfoArray[index].x = px2vp(eventData.x);
                globalThis.videoPlayerInfoArray[index].y = px2vp(eventData.y);
                globalThis.videoPlayerInfoArray[index].w = px2vp(eventData.w);
                globalThis.videoPlayerInfoArray[index].h = px2vp(eventData.h);
                let videoPlayerInfo = cloneVideoPlayerInfo(globalThis.videoPlayerInfoArray[index]);
                globalThis.videoPlayerInfoArray[index] = videoPlayerInfo;
            } catch (error) {
                hilog.error(0x0001, 'videoPlayerInfo  ErrorCode: %{public}d,  Message: %{public}s', error.code, error.message);
            }
            hilog.debug(0x0001, "index.ts", "postSetVideoPlayerRect end, x=%{public}d, y=%{public}d, w=%{public}d, h=%{public}d", globalThis.videoPlayerInfoArray[index].x, globalThis.videoPlayerInfoArray[index].y, globalThis.videoPlayerInfoArray[index].w, globalThis.videoPlayerInfoArray[index].h);
            break;
        case "setVideoPlayVisible":
            hilog.debug(0x0001, "index.ts", "setVideoPlayVisible:%{public}s start, viewTag:%{public}d", eventData.visible, eventData.viewTag);
            index = globalThis.videoPlayerIndexMap.get(eventData.viewTag);
            if (globalThis.videoPlayerInfoArray[index].visible == eventData.visible) {
                return;
            }
            globalThis.videoPlayerInfoArray[index].visible = eventData.visible
            let cloneVideoPlayer = cloneVideoPlayerInfo(globalThis.videoPlayerInfoArray[index]);
            globalThis.videoPlayerInfoArray[index] = cloneVideoPlayer;
            hilog.debug(0x0001, "index.ts", "setVideoPlayVisible end");
            break;
        case "requestFullscreen":
            hilog.debug(0x0001, "index.ts", "requestFullscreen:%{public}d, requestFullscreen:%{public}s start", eventData.isFullscreen);
            index = globalThis.videoPlayerIndexMap.get(eventData.viewTag);
            globalThis.videoPlayerInfoArray[index].controller.requestFullscreen(eventData.isFullscreen);
            globalThis.videoPlayerInfoArray[index].isFullScreen = eventData.isFullscreen;
            hilog.debug(0x0001, "index.ts", "requestFullscreen  end");
            break;
    }
}