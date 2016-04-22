/*
 * Mutex.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月20日 14时49分12秒
 *
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

namespace Common {

class Mutex {
public:
    Mutex();
    Mutex (const Mutex &);
    ~Mutex();
    int Lock();
    int UnLock();
    pthread_mutex_t* GetMutex();
private:
    Mutex& operator=(const Mutex &);
private:
    pthread_mutex_t _mutex;
};

} //namespace

#endif // MUTEX_H_


