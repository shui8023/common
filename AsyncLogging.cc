/*
 * AsyncLogging.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月26日 13时13分25秒
 *
 */

#include "AsyncLogging.h"
#include "Logging.h"
#include "Thread.h"

#include <functional>
#include <iostream>
#include <boost/bind.hpp>

namespace Common {

AsyncLogging::AsyncLogging(const std::string &file_name, 
        size_t rollsize, 
        int flush) {
    _thread.Add(
            (ThreadFunc)&AsyncLogging::thread_func,
            this);
    _current_buffer.SetBzero();
    _next_buffer.SetBzero();
    buffer_ptr = &_current_buffer;
    write_ptr = &_next_buffer;
    _flushlevel = flush;
    _file_name = file_name;
    _rollsize = rollsize;
    _running = false;

}

AsyncLogging::~AsyncLogging() {
    if (_running) {
        Stop();
    }
}

void AsyncLogging::Append(const char *buffer, size_t len) {
    Mutex lock(_mutex);
    if (buffer_ptr->Avail() > len) {
        buffer_ptr->Append(buffer, len);
        vector_buffer.push_back(*buffer_ptr);
        buffer_ptr->ReSet();
        buffer_ptr->SetBzero();
        _cond.Notify();
    } else {
        vector_buffer.push_back(*buffer_ptr);
        buffer_ptr->ReSet();
        buffer_ptr->SetBzero();
        buffer_ptr->Append(buffer, len);
        _cond.Notify();
    }
}

void * AsyncLogging::thread_func(void *arg) {
    std::vector<LarBuffer> write_buffer_ptr;

    LogFile output(_file_name,_rollsize, _flushlevel);
    while (_running) {
        {
            Mutex lock(_mutex);
            if (vector_buffer.empty()) {
                _cond.Wait(lock);
            }
            vector_buffer.push_back(*buffer_ptr);
            buffer_ptr->SetBzero();
            buffer_ptr->ReSet();
            write_buffer_ptr = vector_buffer;
            vector_buffer.clear();
        } 

        if (write_buffer_ptr.size() > 10) {
            char buf[256];
            snprintf(buf, sizeof(buf), "Dropped log message");
            output.Append(buf, strlen(buf));
        }
        for (size_t i = 0; i != write_buffer_ptr.size(); i++) {
            output.Append(write_buffer_ptr[i].Data(), write_buffer_ptr[i].GetLength());
        }
        write_buffer_ptr.clear();
        output.Flush();
    }

    if (buffer_ptr->GetLength() != 0) {
        output.Append(buffer_ptr->Data(), buffer_ptr->GetLength());
    }
    output.Flush();
    return (void *)(0);
}

void AsyncLogging::Start() {
    _running = true;
    _thread.Start();
}

void AsyncLogging::Stop() {
    _running = false;
    _cond.Notify();
    _thread.Join();
}

} //namespace 

