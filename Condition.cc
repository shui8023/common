/*
 * Condition.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月20日 15时20分12秒
 *
 */

#include "Condition.h"

namespace Common {

Cond::Cond() {
    pthread_cond_init(&_cond, NULL);
}

Cond::~Cond() {
    pthread_cond_destroy(&_cond);
}

int Cond::Wait(Mutex mutex) {
    int result;

    result = pthread_cond_wait(&_cond, mutex.GetMutex());

    return result;
}

int Cond::WaitSeconds(Mutex mutex, int seconds) {
    int result;
    struct timespec times;
    clock_gettime(CLOCK_REALTIME, &times);  // this is question, the clock_gettime have return value
    times.tv_sec += seconds;
    result = pthread_cond_timedwait(&_cond, mutex.GetMutex(), &times);
}

int Cond::Notify() {
    int result;
    
    result = pthread_cond_signal(&_cond);

    return result;
}

int Cond::NotifyAll() {
    int result;
    
    result = pthread_cond_broadcast(&_cond);

    return result;
}

} //namespace 
