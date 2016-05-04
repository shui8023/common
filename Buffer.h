/*
 * Buffer.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月20日 23时52分07秒
 *
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>
#include <cstring>

namespace Common {

template <int SIZE>
class Buffer {
public:
    Buffer() :_cur(_buffer) {
        SetBzero();          
    }

    ~Buffer() {
        
    }

    Buffer(const Buffer &buffer) {
        strncpy(_buffer, buffer.Data(), buffer.GetLength());
        _cur = _buffer + buffer.GetLength();
    }

    Buffer& operator=(const Buffer &buffer) {
        strncpy(_buffer, buffer.Data(), buffer.GetLength());
        _cur = _buffer + buffer.GetLength();
        return *this;
    }

    char *Current() const{
        return _cur;
    }

    const char *Data() const {
        return _buffer;
    }
    
    void SetBzero() {
        bzero(_buffer, sizeof(_buffer));

    }

    int GetSize() const {
        return static_cast<int> (sizeof(_buffer));
    }

    void ReSet() {
        _cur = _buffer;
    }

    int GetLength() const {
        return static_cast<int> (_cur - _buffer);
    }

    int Avail() const {
        return static_cast<int> (end() - _cur);   
    }

    void Append(const char *buffer, size_t len) {
        if (Avail() > len) {
            memcpy(_cur, buffer, len);
            _cur += len;
        }
    }

    void Add(size_t len) {
        _cur += len;       
    }

    std::string ToString() const {
        return std::string(_buffer, GetLength());   
    }
private:
    const char *end() const {
        return _buffer + sizeof(_buffer);
    }
private:
    char _buffer[SIZE];
    char *_cur;
};

} // namespace

#endif // BUFFER_H_
