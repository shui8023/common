/*
 * LogFile.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月22日 14时29分18秒
 *
 */

#ifndef LOGFILE_H_
#define LOGFILE_H_

#include "File.h"
#include "Mutex.h"

#include <string>

namespace Common {

class LogFile {
public:

private:
    std::string GetLogFileName(const std::string& basename, time_t *now);
    Mutex _mutex;
    time_t _last_flush;
    File _file;
};

} //namespace
#endif ///LOGFILE_H_
