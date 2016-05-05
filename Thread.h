/*
 * Thread.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月19日 23时25分22秒
 *
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <string>
#include <assert.h>
#include <iostream>

namespace Common {
    
typedef void *(*ThreadFunc)(void *);

class Thread {
public:
    Thread(const ThreadFunc , void *data = NULL);
    Thread();
    void Add(const ThreadFunc fun, void *data);
    ~Thread();
    int Start();
    int Join();
    bool IsStart() const;
    pthread_t GetPid() const;
private:
    Thread (const Thread &);
    Thread &operator=(const Thread &);
private:
    bool _started;
    bool _joined;
    ThreadFunc _func;
    pthread_t _pid;
    void *_data;
    std::string _name;
};

} // namespace 

#endif // THREAD_H_
