/*
 * Mutex_test.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月20日 15时44分22秒
 *
 */

#include "Mutex.h"
#include "Condition.h"
#include "Thread.h"
#include <unistd.h>
using namespace Common;

int b = 0;
Mutex mutex;
Cond cond;

void *ThreadFunction(void *arg) {
    int a = *(int *)arg;
    std::cout << a << std::endl;
    mutex.Lock();
    b++;
    std::cout << b << std::endl;
    if (b == 3) {
        cond.Notify();
    }
    mutex.UnLock();
}
int main(int argc, char *argv[])
{
    int a = 10;
    Thread thread(ThreadFunction, &a);
    thread.Start();
    b++;
    cond.Wait(mutex);
    std::cout << b << std::endl;
    return 0;
}
