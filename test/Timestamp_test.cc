/*
 * Timestamp_test.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月24日 23时28分13秒
 *
 */

#include "Timestamp.h"
#include <iostream>
using namespace std;
using namespace Common;

int main(int argc,char *argv[])
{
    Timestamp tv = Timestamp::Now();
    cout <<tv.ToString() << endl;
    return 0;
}
