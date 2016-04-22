/*
 * Mutex.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月20日 14时58分13秒
 *
 */

#include "Mutex.h"

namespace Common {

Mutex::Mutex() {
    pthread_mutex_init(&_mutex, NULL);
}
Mutex::Mutex (const Mutex &mutex) {
    _mutex = mutex._mutex;
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&_mutex);
}

int Mutex::Lock() {
    int result;

    result = pthread_mutex_lock(&_mutex);

    return result;
}

int Mutex::UnLock() {
    int result;

    result = pthread_mutex_unlock(&_mutex);
    
    return result;
}

pthread_mutex_t* Mutex::GetMutex() {
    return &_mutex;
}

} //namespace
