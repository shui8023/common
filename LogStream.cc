/*
 * LogStream.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月24日 16时30分58秒
 *
 */

#include "LogStream.h"
#include <stdint.h>

namespace Common {

const char digits[] = "9876543210123456789";
const char *zero = digits + 9;
const char digitsHex[] = "0123456789ABCDEF";

template<typename T> 
size_t convert(char buf[], T value) {
    T i = value;
    char *p = buf;
    do {
        int s = static_cast<int>(i % 10);
        i /= 10;
        *p++ = zero[s];
    } while (i != 0);
    if (value < 0) {
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
}

size_t convertHex(char buf[], uintptr_t len) {
    uintptr_t i = len;
    char *p = buf;
    do {
        int s = static_cast<int>(i % 16);
        i /= 16;
        *p++ = digitsHex[s];
    } while (i != 0);

    *p = '\0';
    std::reverse(buf, p);
    return p - buf;
}

LogStream::LogStream() {

}

LogStream::~LogStream() {

}

template<typename T> 
void LogStream::formatInteger(T v) {
    if (_buffer.Avail() >= max_num_size) {
        size_t len = convert(_buffer.Current(), v);
        _buffer.Add(len);
    }
}

LogStream& LogStream::operator<<(bool v) {
    _buffer.Append(v ? "1":"0", 1);
    return *this;
}    


LogStream& LogStream::operator<<(short v) {
    *this << static_cast<int>(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned short v) {
    *this << static_cast<unsigned int>(v);
    return *this;
}

LogStream& LogStream::operator<<(int v) {
    formatInteger(v);   
    return *this;
}

LogStream& LogStream::operator<<(unsigned int v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(long v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(long long v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long long v) {
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(const void *p) {
    uintptr_t v = reinterpret_cast<uintptr_t>(p);
    if (_buffer.Avail() > max_num_size) {
        char *buf = _buffer.Current();
        buf[0] = '0';
        buf[1] = 'x';
        size_t len = convertHex(buf + 2, v);
        _buffer.Add(len + 2);
    }
    return *this;
}

LogStream& LogStream::operator<<(float v) {
    *this << static_cast<double>(v);
    return *this;

}

LogStream& LogStream::operator<<(double v) {
    if (_buffer.Avail() >= max_num_size) {
        int len = snprintf(_buffer.Current(), max_num_size, "%.12g", v);
        _buffer.Add(len);
    }   
    return *this;
}

LogStream& LogStream::operator<<(char v) {
    _buffer.Append(&v, 1);
    return *this;
}

LogStream& LogStream::operator<<(const char* str) {
    if (str) {
        _buffer.Append(str, strlen(str));
    } else {
        _buffer.Append("(null)", 6);
    }
    
    return *this;
}

LogStream& LogStream::operator<<(const unsigned char* str) {
    return operator<<(reinterpret_cast<const char *>(str));    
}

LogStream& LogStream::operator<<(const std::string& v) {
    _buffer.Append(v.c_str(), v.size());    
    return *this;
}

LogStream& LogStream::operator<<(const SmallBuffer& v) {
    *this << v.ToString();
    return *this;
}

void LogStream::Append(const char *data, size_t len) {
    _buffer.Append(data, len);
}   

const LogStream::SmallBuffer& LogStream::buffer() const {
    return _buffer;
}

void LogStream::ResetBuffer() {
    _buffer.ReSet();
}

} //namespace 
