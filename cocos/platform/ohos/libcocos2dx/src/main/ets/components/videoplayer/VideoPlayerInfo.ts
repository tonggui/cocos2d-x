import hilog from '@ohos.hilog'
export class VideoPlayerInfo {
    // position
    public x: number = 0;
    public y: number = 0;
    // size
    public w: number = 0;
    public h: number = 0;
    // url
    public url: string = ''
    // tag
    public viewTag: number = 0

    // Whether to display
    public visible: boolean = true

    public isPlay: boolean = false

    public isFullScreen: boolean = false
    /**
     * https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/arkui-ts/ts-media-components-video.md#videocontroller
     *
     */
    public controller: VideoController = new VideoController()

    constructor(x: number, y: number, w: number, h: number, viewTag: number) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.viewTag = viewTag;
    }
}
export function cloneVideoPlayerInfo(videoPlayerInfo: VideoPlayerInfo) {
    let newVideoPlayerInfo = new VideoPlayerInfo(videoPlayerInfo.x, videoPlayerInfo.y, videoPlayerInfo.w, videoPlayerInfo.h, videoPlayerInfo.viewTag);
    newVideoPlayerInfo.controller = videoPlayerInfo.controller;
    newVideoPlayerInfo.url = videoPlayerInfo.url;
    newVideoPlayerInfo.visible =videoPlayerInfo.visible;
    return newVideoPlayerInfo;
}

export default class VideoPlayer {
    static MODULE_NAME: string = 'VideoPlay';

    private static parentPort;

    static init(parentPort) {
        VideoPlayer.parentPort = parentPort;
    }

    static setURL(viewTag: number, url: string) {
        hilog.debug(0x0001, "VideoPlayer", "postLoadURL start");
        VideoPlayer.parentPort.postMessage({
            'module': VideoPlayer.MODULE_NAME, 'function': 'setURL', 'viewTag': viewTag, 'url': url
        });
        hilog.debug(0x0001, "VideoPlayer", "setURL end");
    }

    static createVideoPlayer(viewTag: number) {
        VideoPlayer.parentPort.postMessage({'module': VideoPlayer.MODULE_NAME, 'function': 'createVideoPlayer', 'viewTag': viewTag});
        hilog.debug(0x0001, "VideoPlayer", "post%{public}s end", 'createVideoPlayer');
    }

    static removeVideoPlayer(viewTag: number) {
        VideoPlayer.parentPort.postMessage({'module': VideoPlayer.MODULE_NAME, 'function': 'removeVideoPlayer', 'viewTag': viewTag});
        hilog.debug(0x0001, "VideoPlayer", "post%{public}s end", 'createVideoPlayer');
    }

    static postSetVideoPlayerRect(viewTag: number, x: number, y: number, w: number, h: number) {
        hilog.debug(0x0001, "VideoPlayer", "setVideoPlayerRect start, x=%{public}d, y=%{public}d, w=%{public}d, h=%{public}d", x, y, w, h);
        VideoPlayer.parentPort.postMessage({
            'module': VideoPlayer.MODULE_NAME, 'function': 'postSetVideoPlayerRect',
            'viewTag': viewTag,
            'x': x,
            'y': y,
            'w': w,
            'h': h
        });
        hilog.debug(0x0001, "VideoPlayer", "setVideoPlayer end");
    }

    static play(viewTag: number) {
        hilog.debug(0x0001, "VideoPlayer", "play start");
        VideoPlayer.parentPort.postMessage({
            'module': VideoPlayer.MODULE_NAME, 'function': 'play', 'viewTag': viewTag
        });
        hilog.debug(0x0001, "VideoPlayer", "play end ");
    }
    static pause(viewTag: number) {
        hilog.debug(0x0001, "VideoPlayer", "pause start");
        VideoPlayer.parentPort.postMessage({
            'module': VideoPlayer.MODULE_NAME, 'function': 'pause', 'viewTag': viewTag
        });
        hilog.debug(0x0001, "VideoPlayer", "pause end ");
    }

    static stop(viewTag: number) {
        hilog.debug(0x0001, "VideoPlayer", "stop start");
        VideoPlayer.parentPort.postMessage({
            'module': VideoPlayer.MODULE_NAME, 'function': 'stop', 'viewTag': viewTag
        });
        hilog.debug(0x0001, "VideoPlayer", "stop end ");
    }

    static setVideoPlayVisible(viewTag: number, isVisible: boolean) {
        hilog.debug(0x0001, "VideoPlayer", "setVisible start");
        VideoPlayer.parentPort.postMessage({
            'module': VideoPlayer.MODULE_NAME, 'function': 'setVideoPlayVisible', 'viewTag': viewTag, 'visible': isVisible
        });
        hilog.debug(0x0001, "VideoPlayer", "setVisible end");
    }

    static requestFullscreen(viewTag: number, isFullscreen: boolean) {
        hilog.debug(0x0001, "VideoPlayer", "requestFullscreen start");
        VideoPlayer.parentPort.postMessage({
            'module': VideoPlayer.MODULE_NAME, 'function': 'requestFullscreen', 'viewTag': viewTag, 'isFullscreen': isFullscreen
        });
        hilog.debug(0x0001, "VideoPlayer", "requestFullscreen end");
    }

}

globalThis.VideoPlayer = {};
globalThis.VideoPlayer.createVideoPlayer = VideoPlayer.createVideoPlayer;
globalThis.VideoPlayer.removeVideoPlayer = VideoPlayer.removeVideoPlayer;
globalThis.VideoPlayer.setURL = VideoPlayer.setURL;
globalThis.VideoPlayer.postSetVideoPlayerRect = VideoPlayer.postSetVideoPlayerRect;
globalThis.VideoPlayer.play = VideoPlayer.play;
globalThis.VideoPlayer.pause = VideoPlayer.pause;
globalThis.VideoPlayer.stop = VideoPlayer.stop;
globalThis.VideoPlayer.setVideoPlayVisible = VideoPlayer.setVideoPlayVisible;
globalThis.VideoPlayer.requestFullscreen = VideoPlayer.requestFullscreen;
