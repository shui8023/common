/*
 * LogFile.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月24日 14时13分09秒
 *
 */

#include "LogFile.h"

namespace Common {

LogFile::LogFile(const std::string &file_name,
            size_t rollsize, int flush_time,
            int check_every):
    _file_name(file_name), 
    _roll_size(rollsize),
    _flush_time(flush_time), 
    _check_every_time(check_every),
    _last_flush(0), 
    _start_period(0), 
    _last_roll(0),
    _count(0),
    _file(NULL){
    RollFile();
}

LogFile::~LogFile() {

}

void LogFile::Append(const char *log_buffer, size_t len) {
    _mutex.Lock();
    _append(log_buffer, len);
    _mutex.UnLock();
}

void LogFile::_append(const char *log_buffer, size_t len) {
    _file->Append(log_buffer, len);

    if (_file->WrittenBytes() > _roll_size) {
        RollFile();
    } else {
        ++_count;
        if (_count > _check_every_time) {
            _count = 0;
            time_t now = time(NULL);
            time_t thisperoid = now / roll_per_seconds * roll_per_seconds;
            if (thisperoid != _start_period) {
                RollFile();
            } else if (now - _last_flush > _flush_time) {
                _last_flush = now;
                Flush();
            }
        }
    }
}

void LogFile::Flush() {
    _mutex.Lock();
    _file->Flush();
    _mutex.UnLock();
}

bool LogFile::RollFile() {
    time_t now = 0;
    std::string file_name = GetLogFileName(_file_name, &now);
    time_t start = now / roll_per_seconds * roll_per_seconds;
    
    if (now > _last_roll) {
        _last_roll = now;
        _last_flush = now;
        _start_period = start;
        if (_file != NULL) {
            delete _file;
        }
        _file = new File(file_name);
        return true;
    }

    return false;
}

std::string LogFile::GetLogFileName(const std::string& basename, time_t *now) {
    std::string log_file;
    char timebuf[32];
    struct tm tm;

    log_file.reserve(basename.size() + 64);
    log_file = basename;
    
    *now = time(NULL);
    gmtime_r(now, &tm);
    strftime(timebuf, sizeof(timebuf), "-%y-%m-%d", &tm);

    log_file += timebuf;
    
    log_file += ".log";

    return log_file;
}

} //namespace 

