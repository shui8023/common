/*
 * test.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月20日 11时24分09秒
 *
 */

#include "Thread.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>

using namespace Common;
void * ThreadFun(void *arg) {
    int a = *(int *)(arg);
    std::cout << a << std::endl;
    sleep(10);
}

int main(int argc, char *argv[])
{
    int  a = 10;
    Thread thread(ThreadFun, (void *)&a);

    thread.Start();
    std::cout << thread.GetPid() << std::endl;
    std::cout << thread.IsStart() << std::endl;
    printf("%u\n", thread.GetPid());
    thread.Join();
    std::cout << "test the join" << std::endl;
    return 0;
}
