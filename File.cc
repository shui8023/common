/*
 * File.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月21日 19时58分45秒
 *
 */

#include "File.h"
#include <assert.h>
#include <errno.h>
#include <cstring>

namespace Common {

File::File(std::string filename) 
    :_fd(fopen(filename.c_str(), "ae")), _written_bytes(0){
    assert(_fd);
    bzero(_buffer, sizeof(_buffer));
    setbuffer(_fd, _buffer, sizeof(_buffer));
}

File::~File() {
    fclose(_fd);
}

File::File() {
        
}

void File::SetFileName(const std::string &file_name) {
    _file_name = file_name;
}

std::string File::GetFileName() const {
    return _file_name;    
}

void File::Append(const char *logline, const size_t len) {
    size_t n = write(logline, len);
    size_t remain = len - n;
    while (remain > 0) {
        size_t x = write(logline + n, remain);
        if (x < 0) {
            if (errno == EAGAIN) {
                continue;
            }
        } else if (x == 0) {
            break;
        } else {
            n += x;
            remain = len - n;
        }
    }
    _written_bytes += len;
}
void File::Flush() {
    fflush(_fd);
}

size_t File::WrittenBytes() const {
    return _written_bytes;
}

size_t File::write(const char *logline, size_t len) {
    return fwrite_unlocked(logline, 1, len, _fd);
}

} // namespace 

