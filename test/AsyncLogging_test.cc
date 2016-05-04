/*
 * AsyncLogging_test.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月26日 20时52分21秒
 *
 */

#include "AsyncLogging.h"
#include "Logging.h"

using namespace Common;
using namespace std;

AsyncLogging logg("test_log");

void output(const char *msg, int len) {
    cout << msg;
    logg.Append(msg, len);    
}

int main()
{
    Logger::SetOut(output);
    Logger::SetLogLevel(Logger::ERROR);
    cout << Logger::logLevel();
    logg.Start();
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    LOG_WARN << "asdasdddddddddddddddddddddddddddddd";
    while (1);
    return 0;
}
