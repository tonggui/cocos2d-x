/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCPLATFORMDEFINE_H__
#define __CCPLATFORMDEFINE_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include "CCLogOhos.h"

#define CC_DLL

#define CC_NO_MESSAGE_PSEUDOASSERT(cond)                        \
    if (!(cond)) {                                              \
        OHOS_LOGI("[cocos2d-x assert] %s function:%s line:%d",  __FILE__, __FUNCTION__, __LINE__); \
    }

#define CC_MESSAGE_PSEUDOASSERT(cond, msg)                          \
    if (!(cond)) {                                                  \
        OHOS_LOGI("[cocos2d-x assert] file:%s function:%s line:%d, %s", __FILE__, __FUNCTION__, __LINE__, msg); \
    }


#define CC_ASSERT(cond) CC_NO_MESSAGE_PSEUDOASSERT(cond)

#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

#define CC_AUDIO_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#if defined(_MSC_VER)
#define CC_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define CC_FORCE_INLINE inline __attribute__((always_inline))
#else
#if defined(__cplusplus) || defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L /* C99 */
#define CC_FORCE_INLINE static inline
#elif
#define CC_FORCE_INLINE inline
#endif
#endif

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#endif /* __CCPLATFORMDEFINE_H__*/
