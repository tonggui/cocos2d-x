/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ui/UIVideoPlayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include <unordered_map>
#include <stdlib.h>
#include <string>
#include "base/CCDirector.h"
#include "base/CCEventListenerKeyboard.h"
#include "platform/ohos/CCFileUtils-ohos.h"
#include "platform/ohos/CCArkJsVideoPlay.h"

#include "ui/UIHelper.h"

USING_NS_CC;
#define QUIT_FULLSCREEN 1000

//-----------------------------------------------------------------------------------------------------------

using namespace cocos2d::experimental::ui;
static int32_t kVideoPlayerTag = 0;
static std::unordered_map<int, VideoPlayer *> s_allVideoPlayers;

VideoPlayer::VideoPlayer()
    : _fullScreenDirty(false),
      _fullScreenEnabled(false),
      _keepAspectRatioEnabled(false),
      _videoPlayerIndex(-1),
      _eventCallback(nullptr),
      _isPlaying(false)
{
    // 增加索引
    _videoPlayerIndex = kVideoPlayerTag++;
    s_allVideoPlayers[_videoPlayerIndex] = this;

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif
    CCArkJsVideoPlay::createVideoPlayer(_videoPlayerIndex);
}

VideoPlayer::~VideoPlayer()
{
    if (_videoPlayerIndex != -1 && kVideoPlayerTag != -1) {
        CCArkJsVideoPlay::removeVideoPlayer(_videoPlayerIndex);
        auto iter = s_allVideoPlayers.find(_videoPlayerIndex);
        if (iter != s_allVideoPlayers.end()) {
            s_allVideoPlayers.erase(iter);
        }
        kVideoPlayerTag--;
    }
}
//todo:沙箱路径地址应该有更好的实现方式
void VideoPlayer::setFileName(const std::string &fileName)
{
    _videoURL = "file:///data/storage/el1/bundle/entry/resources/rawfile/" + fileName;
    _videoSource = VideoPlayer::Source::FILENAME;
    CCArkJsVideoPlay::setURL(_videoPlayerIndex, _videoURL);
}

void VideoPlayer::setURL(const std::string &videoUrl)
{
    if (videoUrl.find("://") == std::string::npos) {
        _videoURL = FileUtils::getInstance()->fullPathForFilename(videoUrl);
        _videoSource = VideoPlayer::Source::FILENAME;
    } else {
        _videoURL = videoUrl;
        _videoSource = VideoPlayer::Source::URL;
    }
    CCArkJsVideoPlay::setURL(_videoPlayerIndex, _videoURL);
}


void VideoPlayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    cocos2d::ui::Widget::draw(renderer, transform, flags);

    if (flags & FLAGS_TRANSFORM_DIRTY) {
        auto uiRect = cocos2d::ui::Helper::convertBoundingBoxToScreen(this);
        CCArkJsVideoPlay::setVideoPlayRect(_videoPlayerIndex, (int)uiRect.origin.x, (int)uiRect.origin.y,
            (int)uiRect.size.width, (int)uiRect.size.height);
    }

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode->clear();
    auto size = getContentSize();
    Point vertices[4] = {Point::ZERO, Point(size.width, 0), Point(size.width, size.height), Point(0, size.height)};
    _debugdrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
#endif
}

void VideoPlayer::setFullScreenEnabled(bool enabled)
{
    if (_fullScreenEnabled != enabled) {
        _fullScreenEnabled = enabled;

        auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
        CCArkJsVideoPlay::requestFullscreen(_videoPlayerIndex, enabled);
    }
}

bool VideoPlayer::isFullScreenEnabled() const
{
    return _fullScreenEnabled;
}

void VideoPlayer::setKeepAspectRatioEnabled(bool enable)
{
    if (_keepAspectRatioEnabled != enable) {
        _keepAspectRatioEnabled = enable;
        // todo:鸿蒙暂时不支持
    }
}

#if CC_VIDEOPLAYER_DEBUG_DRAW
void VideoPlayer::drawDebugData()
{
    Director *director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");

    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    auto size = getContentSize();

    Point vertices[4] = {Point::ZERO, Point(size.width, 0), Point(size.width, size.height), Point(0, size.height)};

    DrawPrimitives::drawPoly(vertices, 4, true);

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
#endif

void VideoPlayer::play()
{
    if (!_videoURL.empty()) {
        CCArkJsVideoPlay::play(_videoPlayerIndex);
    }
}

void VideoPlayer::pause()
{
    if (!_videoURL.empty()) {
        CCArkJsVideoPlay::pause(_videoPlayerIndex);
    }
}

void VideoPlayer::resume()
{
    if (!_videoURL.empty()) {
        CCArkJsVideoPlay::play(_videoPlayerIndex);
    }
}

void VideoPlayer::stop()
{
    if (!_videoURL.empty()) {
        CCArkJsVideoPlay::stop(_videoPlayerIndex);
    }
}

void VideoPlayer::seekTo(float sec)
{
    if (!_videoURL.empty()) {
        CCArkJsVideoPlay::seekTo(_videoPlayerIndex, int(sec * 1000));
    }
}

bool VideoPlayer::isPlaying() const
{
    return _isPlaying;
}


void VideoPlayer::setVisible(bool visible)
{
    cocos2d::ui::Widget::setVisible(visible);

    if (!visible || isRunning()) {
        CCArkJsVideoPlay::setVisible(_videoPlayerIndex, visible);
    }
}

void VideoPlayer::addEventListener(const VideoPlayer::ccVideoPlayerCallback &callback)
{
    _eventCallback = callback;
}

void VideoPlayer::onPlayEvent(int event)
{
    if (event == QUIT_FULLSCREEN) {
        _fullScreenEnabled = false;
    } else {
        VideoPlayer::EventType videoEvent = (VideoPlayer::EventType)event;
        if (videoEvent == VideoPlayer::EventType::PLAYING) {
            _isPlaying = true;
        } else {
            _isPlaying = false;
        }

        if (_eventCallback) {
            _eventCallback(this, videoEvent);
        }
    }
}

cocos2d::ui::Widget *VideoPlayer::createCloneInstance()
{
    return VideoPlayer::create();
}

void VideoPlayer::copySpecialProperties(Widget *widget)
{
    VideoPlayer *videoPlayer = dynamic_cast<VideoPlayer *>(widget);
    if (videoPlayer) {
        _isPlaying = videoPlayer->_isPlaying;
        _fullScreenEnabled = videoPlayer->_fullScreenEnabled;
        _fullScreenDirty = videoPlayer->_fullScreenDirty;
        _videoURL = videoPlayer->_videoURL;
        _keepAspectRatioEnabled = videoPlayer->_keepAspectRatioEnabled;
        _videoSource = videoPlayer->_videoSource;
        _videoPlayerIndex = videoPlayer->_videoPlayerIndex;
        _eventCallback = videoPlayer->_eventCallback;
        _videoView = videoPlayer->_videoView;
    }
}

void executeVideoCallback(int index, int event)
{
    auto it = s_allVideoPlayers.find(index);
    if (it != s_allVideoPlayers.end()) {
        s_allVideoPlayers[index]->onPlayEvent(event);
    }
}

#endif
