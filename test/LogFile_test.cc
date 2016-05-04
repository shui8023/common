/*
 * LogFile_test.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月24日 14时48分09秒
 *
 */

#include "LogFile.h"

using namespace Common;

int main(int argc, char *argv[])
{
    LogFile log_file("name", 1000000);
    log_file.Append("asdasd", 6);
    log_file.Append("asdasd", 6);
    log_file.Append("asdasd", 6);
    log_file.Append("asdasd", 6);
    log_file.Append("asdasd", 6);
    log_file.Append("asdasd", 6);
    return 0;
}
