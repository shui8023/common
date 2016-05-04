/*
 * File.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月20日 23时43分15秒
 *
 */

#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <string>
#include <stdio.h>

namespace Common {

class File {
public:
    explicit File(std::string filename);
    ~File();
    std::string GetFileName() const;
    void Append(const char *logline, const size_t len);
    void Flush();
    size_t WrittenBytes() const;
public:
    static const int buffer_size = 64 * 1024;

private:
    File(const File &);
    File& operator=(const File &);
private:
    size_t write(const char *logline, size_t len);
    FILE* _fd;
    std::string _file_name;
    char _buffer[buffer_size];
    size_t _written_bytes;
};

}//namespace

#endif //FILE_H_
