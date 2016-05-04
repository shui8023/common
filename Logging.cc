/*
 * Logging.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月25日 11时28分02秒
 *
 */

#include "Logging.h"
#include <time.h>

namespace Common {

void defaultOutput(const char *msg, int len)
{
    size_t n = fwrite(msg, 1, len, stdout);
}

void defaultFlush()
{
    fflush(stdout);
}

Logger::LogLevel initLogLevel() 
{
    return Logger::DEBUG;
}
Logger::LogLevel g_loglevel = initLogLevel();
Logger::OutPutFunc g_output = defaultOutput;
Logger::FlushFunc g_flush = defaultFlush;

__thread time_t _lastSecond;
__thread char t_time[32];

class T {
public:
    T(const char *str, unsigned int len):
        _str(str), _len(len) {
            
    }
    const char *_str;
    const unsigned _len;
};

inline LogStream& operator <<(LogStream& s, T v) {
    s.Append(v._str, v._len);
    return s;
}

inline LogStream& operator <<(LogStream& s, const Logger::SourceFile& v) {
    s.Append(v._data, v._size);
    return s;
}

const char *LogLevelName[Logger::NUM_LOG_LEVELS] = {
    "[TRACE] ",
    "[DEBUG] ",
    "[INFO ] ", 
    "[WARN ] ",
    "[ERROR] ",
    "[FATAL] "
};

Logger::Logger(SourceFile file, int line):
    _time(Timestamp::Now()),
    _line(line),
    _file(file),
    _level(INFO){

    FormatTime();
    _stream << T(LogLevelName[INFO], 8); 
}

Logger::Logger(SourceFile file, int line, LogLevel level):
    _time(Timestamp::Now()),
    _line(line),
    _file(file),
    _level(level) {

    FormatTime();
    _stream << T(LogLevelName[_level], 8); 
}

Logger::Logger(SourceFile file, int line, LogLevel level, const char *func):
    _time(Timestamp::Now()),
    _line(line),
    _file(file), 
    _level(level){

    FormatTime();
    _stream << T(LogLevelName[_level], 8); 
    _stream << func << ' ';
}

Logger::Logger(SourceFile file, int line, bool Abort):
    _time(Timestamp::Now()),
    _line(line),
    _file(file),
    _level(Abort?FATAL:ERROR){

    FormatTime();
    _stream << T(LogLevelName[_level], 8); 
}

LogStream &Logger::Stream() {
    return _stream;
}

void Logger::FormatTime() {
    int64_t microSecond = _time.MicroSecond();
    time_t seconds = static_cast<time_t>(microSecond / Timestamp::persecond);
    int microseconds = static_cast<int>(microSecond % Timestamp::persecond);
    char micro_buffer[9];
    int len = 0;

    if (seconds != _lastSecond) {
        _lastSecond = seconds;
        struct tm tm_time;
        gmtime_r(&seconds, &tm_time);
        int len = snprintf(t_time, sizeof(t_time), "%4d-%02d-%02d %02d:%02d:%02d",
            tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
            tm_time.tm_hour + 8, tm_time.tm_min, tm_time.tm_sec);
        t_time[len] = '\0';
    }
    len = snprintf(micro_buffer, sizeof(micro_buffer), ".%06d ", microseconds);
    _stream << T(t_time, 19) << T(micro_buffer, 8);
}


void Logger::SetLogLevel(Logger::LogLevel level) {
    g_loglevel = level;
}


void Logger::SetOut(OutPutFunc func) {
    g_output = func;
}

void Logger::SetFlush(FlushFunc func) {
    g_flush = func;
}

Logger::LogLevel Logger::logLevel() {
    return  g_loglevel;
}

Logger::~Logger() {
    _stream << "  -" << _file << ":" << _line << '\n';
    const LogStream::SmallBuffer& buffer(_stream.buffer());
    g_output(buffer.Data(), buffer.GetLength());
    if (_level == FATAL) {
        g_flush();
        abort();
    }
}
} //namespace 
