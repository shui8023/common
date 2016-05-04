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
#include <memory>

namespace Common {

class LogFile {
public:
    LogFile(const std::string &file_name,
            size_t rollsize, int flush_time = 3,
            int check_every = 1024);
    ~LogFile();
    void Append(const char *log_buffer, size_t len);
    void Flush();
    bool RollFile();
private:
    void _append(const char *log_buffer, size_t len);
    static std::string GetLogFileName(const std::string& basename, time_t *now);
    const std::string _file_name;
    const size_t _roll_size;
    const int _check_every_time;
    const int _flush_time;
    int _count;

    Mutex _mutex;
    time_t _last_flush;
    time_t _start_period;
    time_t _last_roll;
        
    File *_file;
    static const int roll_per_seconds = 60 * 60 * 24;
};

} //namespace
#endif ///LOGFILE_H_
