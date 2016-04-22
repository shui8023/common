/*
 * Thread.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月19日 23时46分41秒
 *
 */

#include "Thread.h"

namespace Common {

Thread::Thread(const ThreadFunc func, void *data)
    :_started(false), _joined(false), _pid(0), _func(func), _data(data) {

}

Thread::~Thread() {
    if (_started && !_joined) {
        pthread_cancel(_pid);
    }
}

int Thread::Start() {
    assert(!_started); 
    int result;

    result = pthread_create(&_pid, NULL, _func, _data);
    if (result != 0) {
        _started = false;
    }
    _started = true;
    return result;
}

int Thread::Join() {
    assert(_started);
    assert(!_joined);
    _joined = true;
    return pthread_join(_pid, NULL);
}

bool Thread::IsStart() const {
    return _started;
}

pthread_t Thread::GetPid() const {
    return _pid;
}


} // namespace
