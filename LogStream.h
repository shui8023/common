/*
 * LogStream.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月24日 15时01分31秒
 *
 */

#ifndef LOGSTREAM_H_
#define LOGSTREAM_H_

#include "Buffer.h"
#include <stdio.h>
#include <string>
#include <algorithm>

namespace Common {

const int buffer_size = 4096;
class LogStream {
public:
    typedef Buffer<buffer_size> SmallBuffer;

    LogStream();
    ~LogStream();
    LogStream& operator<<(bool);
    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);
    LogStream& operator<<(const void *);
    LogStream& operator<<(float);
    LogStream& operator<<(double);
    LogStream& operator<<(char);
    LogStream& operator<<(const char*);
    LogStream& operator<<(const unsigned char*);
    LogStream& operator<<(const std::string& v);
    LogStream& operator<<(const SmallBuffer&);
    void Append(const char *, size_t len);
    const SmallBuffer& buffer() const;
    void ResetBuffer();
private:   
    template<typename T> 
    void formatInteger(T);
    SmallBuffer _buffer;
    static const int max_num_size = 32;
};

} // namespace

#endif // LOGStREAM_H_
