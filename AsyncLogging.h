/*
 * AsyncLogging.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月26日 11时58分19秒
 *
 */

#ifndef ASYNCLOGGING_H_
#define ASYNCLOGGING_H_

#include "Thread.h"
#include "Condition.h"
#include "LogFile.h"
#include "Mutex.h"
#include "Buffer.h"

#include <string>
#include <vector>

namespace Common {

const int LargeSize = 4000;

class AsyncLogging {
public:
    AsyncLogging();
    void Init(const std::string &file_name, size_t rollsize = 1024*1024*1024, int flush = 3);
    ~AsyncLogging();
    void Append(const char *buffer, size_t len);
    void Start();
    void Stop();
    typedef Buffer<LargeSize> LarBuffer;
private:
    void *thread_func(void *);
    std::vector<LarBuffer> vector_buffer;
    bool _running;
    std::string _file_name;
    size_t _rollsize;
    Common::Thread _thread;
    Common::Mutex _mutex;
    Common::Cond _cond;
    int _flushlevel;
    LarBuffer _current_buffer;
    LarBuffer _next_buffer;
    LarBuffer *buffer_ptr;
    LarBuffer *write_ptr;
};

} //namespace
#endif ///ASYNCLOGGING_H_
