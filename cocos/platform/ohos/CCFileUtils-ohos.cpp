/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "CCFileUtils-ohos.h"
// #include "support/zip_support/ZipUtils.h"
#include "platform/CCCommon.h"
// #include "napi/modules//Java_org_cocos2dx_lib_Cocos2dxHelper.h"
// #include "android/asset_manager.h"
// #include "android/asset_manager_jni.h"
// #include "napi/modules/CocosPlayClient.h"
#include "napi/common/plugin_common.h"
#include <stdlib.h>

// #define  LOG_TAG    "CCFileUtils-android.cpp"
// #define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;

NS_CC_BEGIN

NativeResourceManager* FileUtilsOhos::nativeResourceManager_ = nullptr;
string FileUtilsOhos::ohWritablePath = "";

void FileUtilsOhos::setassetmanager(NativeResourceManager* a) {
    if (nullptr == a) {
        return;
    }

    cocos2d::FileUtilsOhos::nativeResourceManager_ = a;
}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsOhos();
        s_sharedFileUtils->init();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = nullptr;
        }
    }
    return s_sharedFileUtils;
}

FileUtilsOhos::FileUtilsOhos()
{
}

FileUtilsOhos::~FileUtilsOhos()
{
}

bool FileUtilsOhos::init()
{
    _defaultResRootPath = "";
    return FileUtils::init();
}

bool FileUtilsOhos::isFileExist(const std::string& filename) const
{
	if (isAbsolutePath(filename))
    {
        return isFileExistInternal(filename);
    }
    else
    {
        std::string fullpath = const_cast<FileUtilsOhos*>(this)->fullPathForFilename(filename);
        if (fullpath.empty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}



bool FileUtilsOhos::isFileExistInternal(const std::string& strFilePath) const
{
    if (strFilePath.empty())
    {
        return false;
    }

    bool bFound = false;

    if(isAbsolutePath(strFilePath)){
        FILE *fp = fopen(strFilePath.c_str(), "r");
        if (fp)
        {
            bFound = true;
            fclose(fp);
        }
    }
    else {
        RawFile *fp = RawFileUtils::GetInstance().Open(strFilePath.c_str());
        if(fp)
        {
            bFound = true;
            RawFileUtils::GetInstance().Close(fp);
        }
    }

    return bFound;
}

// bool CCFileUtilsOhos::isAbsolutePath(const std::string& strPath)
bool FileUtilsOhos::isAbsolutePath(const std::string& strPath) const
{
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. /data/cocos/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
    if (strPath[0] == '/')
    {
        return true;
    }
    return false;
}

std::vector<std::string> FileUtilsOhos::listFiles(const std::string& dirPath)
{
    return RawFileUtils::GetInstance().searchFiles(dirPath.c_str(), false);
}

Data FileUtilsOhos::getData(const std::string& filename)
{
    if (filename.empty())
    {
        return Data::Null;
    }
    
    unsigned char* data = nullptr;
    ssize_t size = 0;


    std::string fullpath = isAbsolutePath(filename)? filename:fullPathForFilename(filename);
    do
    {

        if(isAbsolutePath(fullpath)){
            FILE *fp = fopen(fullpath.c_str(), "r");
            if (!fp) break;
#if defined(_MSC_VER)
            auto descriptor = _fileno(fp);
#else
            auto descriptor = fileno(fp);
#endif
            struct stat statBuf;
            if (fstat(descriptor, &statBuf) == -1) {
                fclose(fp);
                break;
            }
            ssize_t fileSize = statBuf.st_size;
            data = new unsigned char[fileSize];
            size = fread(data, 1, fileSize, fp);
            fclose(fp);
        }
        else {
            RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());
            CC_BREAK_IF(!fp);
            ssize_t fileSize = RawFileUtils::GetInstance().GetSize(fp);
            data = new unsigned char[fileSize];
            fileSize = RawFileUtils::GetInstance().Read(fp, data, fileSize);
            RawFileUtils::GetInstance().Close(fp);
            size = fileSize;
        }
    } while (0);
    
    Data ret;
    if (data == nullptr || size == 0)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    else
    {
        ret.fastSet(data, size);
    }

    return ret;
}


bool FileUtilsOhos::getContents(const std::string& filename, ResizableBuffer* buffer)
{
    if (filename.empty()) {
        //OHOS_LOGE("FileUtilsOhos::getContents() - filename is empty");
        return false;
    }

    std::string fullpath = isAbsolutePath(filename)? filename:fullPathForFilename(filename);

    if (fullpath[0] == '/') {
        FILE *fp = fopen(fullpath.c_str(), "rb");
        if (!fp)
            return false;

#if defined(_MSC_VER)
        auto descriptor = _fileno(fp);
#else
        auto descriptor = fileno(fp);
#endif
        struct stat statBuf;
        if (fstat(descriptor, &statBuf) == -1) {
            fclose(fp);
            return false;
        }
        size_t size = statBuf.st_size;

        buffer->resize(size);
        size_t readsize = fread(buffer->buffer(), 1, size, fp);
        fclose(fp);

        if (readsize < size) {
            buffer->resize(readsize);
            return false;
        }
    }

    else {
        RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());
        if (!fp) {
            OHOS_LOGI("FileUtilsOhos::fp is nullptr");
            return false;
        }
        auto size = RawFileUtils::GetInstance().GetSize(fp);
        buffer->resize(size);

        int readsize = RawFileUtils::GetInstance().Read(fp, buffer->buffer(), size);
        RawFileUtils::GetInstance().Close(fp);

        if (readsize < size) {
            if (readsize >= 0)
                buffer->resize(readsize);
            OHOS_LOGE("FileUtilsOhos::getContents() - readsize < size");
            return false;
        }

        if (!buffer->buffer())
        {
            std::string msg = "Get data from file(" + filename + ") failed!";
            OHOS_LOGI("%{public}s", msg.c_str());
        }
    }

    return true;
}

std::string FileUtilsOhos::getStringFromFile(const std::string& filename)
{
    std::string s;
    getContents(filename, &s);
    return s;
}
    
Data FileUtilsOhos::getDataFromFile(const std::string& filename)
{
    Data d;
    getContents(filename, &d);
    return d;
}


// unsigned char* CCFileUtilsOhos::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
unsigned char* FileUtilsOhos::getFileData(const std::string& filename, const char* mode, ssize_t * size)
{    
    unsigned char * data = 0;
    
    if ( filename.empty() || (! mode) )
    {
        return 0;
    }

    std::string fullpath = isAbsolutePath(filename)? filename:fullPathForFilename(filename);

    do
    {
        RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());
        //CCLOG("[Nnnnut] FileUtilsOhos::getFileData filename: %s", fullpath.c_str());
        CC_BREAK_IF(!fp);
        ssize_t fileSize = RawFileUtils::GetInstance().GetSize(fp);
        data = new unsigned char[fileSize];
        fileSize = RawFileUtils::GetInstance().Read(fp, data, fileSize);
        RawFileUtils::GetInstance().Close(fp);
        //CCLOG("[Nnnnut] FileUtilsOhos::getFileData fileSize: %d", fileSize);

        if (size)
        {
            *size = fileSize;
        }

    } while (0);
    
    if (! data)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    return data;
}

bool FileUtilsOhos::getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor) {
    if (filename.empty()) {
        return false;
    }
    std::string fullpath = isAbsolutePath(filename)? filename:fullPathForFilename(filename);

    RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());//fopen(strFilePath.c_str(), "r");
    if (!fp) {
        CCLOGERROR("FileUtilsOhos::fp is nullptr");
        return false;
    }

    bool result = RawFileUtils::GetInstance().GetRawFileDescriptor(fp, descriptor);
    RawFileUtils::GetInstance().Close(fp);
    return result;
}

string FileUtilsOhos::getWritablePath() const
{
    return ohWritablePath;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
