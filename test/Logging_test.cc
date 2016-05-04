/*
 * Logging_test.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月25日 20时16分41秒
 *
 */

#include "Logging.h"

using namespace Common;
using namespace std;

int main(int argc, char *argv[])
{
    LOG_WARN << "asd";
    std::string str = "asd";
    LOG_ERROR << "asd" + str;
    LOG_INFO << "sssssssssssssssssssssss";
    return 0;
}
