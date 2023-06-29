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
#ifndef __CC_FILEUTILS_OHOS_H__
#define __CC_FILEUTILS_OHOS_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"
#include <string>
#include <vector>
#include "napi/modules/RawFileUtils.h"

NS_CC_BEGIN

class ZipFile;

/**
 * @addtogroup platform
 * @{
 */


class ResizableBuffer {
public:
    virtual ~ResizableBuffer() {}
    virtual void resize(size_t size) = 0;
    virtual void* buffer() const = 0;
};

template<typename T>
class ResizableBufferAdapter { };


template<typename CharT, typename Traits, typename Allocator>
class ResizableBufferAdapter< std::basic_string<CharT, Traits, Allocator> > : public ResizableBuffer {
    typedef std::basic_string<CharT, Traits, Allocator> BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        _buffer->resize((size + sizeof(CharT) - 1) / sizeof(CharT));
    }
    virtual void* buffer() const override {
    // can not invoke string::front() if it is empty

    if (_buffer->empty())
        return nullptr;
    else
        return &_buffer->front();
    }
};

template<typename T, typename Allocator>
class ResizableBufferAdapter< std::vector<T, Allocator> > : public ResizableBuffer {
    typedef std::vector<T, Allocator> BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        _buffer->resize((size + sizeof(T) - 1) / sizeof(T));
    }
    virtual void* buffer() const override {
        // can not invoke vector::front() if it is empty

        if (_buffer->empty())
            return nullptr;
        else
            return &_buffer->front();
    }
};


template<>
class ResizableBufferAdapter<Data> : public ResizableBuffer {
    typedef Data BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        if (static_cast<size_t>(_buffer->getSize()) < size) {
            auto old = _buffer->getBytes();
            void* buffer = realloc(old, size);
            if (buffer)
                _buffer->fastSet((unsigned char*)buffer, size);
        }
    }
    virtual void* buffer() const override {
        return _buffer->getBytes();
    }
};


//! @brief  Helper class to handle file operations
class CC_DLL FileUtilsOhos : public FileUtils
{
    friend class FileUtils;
public:
    virtual ~FileUtilsOhos();

    static std::string ohWritablePath;

    static void setassetmanager(NativeResourceManager* a);
	static NativeResourceManager* getAssetManager() { return nativeResourceManager_; }
    bool getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor);
    /* override funtions */
    bool init();

    /** @deprecated Please use FileUtils::getDataFromFile or FileUtils::getStringFromFile instead. */
    CC_DEPRECATED_ATTRIBUTE virtual unsigned char* getFileData(const std::string& filename, const char* mode, ssize_t * size) override;

    /**
     *  Gets string from a file.
     */
    virtual std::string getStringFromFile(const std::string& filename) override;
    
    /**
     *  Creates binary data from a file.
     *  @return A data object.
     */
    virtual Data getDataFromFile(const std::string& filename) override;

    virtual std::string getWritablePath() const;
    virtual bool isAbsolutePath(const std::string& strPath) const;
	
	virtual bool isFileExist(const std::string& filename) const;

    virtual std::vector<std::string> listFiles(const std::string& dirPath);

private:
    FileUtilsOhos();
    virtual bool isFileExistInternal(const std::string& strFilePath) const;
    Data getData(const std::string& filename);

    template <
            typename T,
            typename Enable = typename std::enable_if<
                    std::is_base_of< ResizableBuffer, ResizableBufferAdapter<T> >::value
    >::type
    >
    bool getContents(const std::string& filename, T* buffer) {
        ResizableBufferAdapter<T> buf(buffer);
        return getContents(filename, &buf);
    }
    virtual bool getContents(const std::string& filename, ResizableBuffer* buffer);

    static NativeResourceManager* nativeResourceManager_;
};

// end of platform group
/// @}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#endif    // __CC_FILEUTILS_OHOS_H__

