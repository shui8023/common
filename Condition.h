/*
 * Condition.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月20日 15时08分13秒
 *
 */

#ifndef CONDITION_H_
#define CONDITION_H_

#include "Mutex.h"
#include <pthread.h>

namespace Common {
class Cond {
public:
    Cond();
    ~Cond();
    int Wait(Mutex mutex);
    int WaitSeconds(Mutex mutex, int seconds);
    int Notify();
    int NotifyAll();
private:
    Cond (const Cond &);
    Cond& operator=(const Cond &);
private:
    pthread_cond_t _cond;
};

} // namespace

#endif // CONDITION_H_
