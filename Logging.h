/*
 * Logging.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月24日 20时40分20秒
 *
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <string>
#include <cstring>
#include "LogStream.h"
#include "Timestamp.h"

namespace Common {

class Logger {
public:
    enum LogLevel {
        TRACE = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5,
        NUM_LOG_LEVELS = 6,
    };

    class SourceFile {
    public:
        explicit SourceFile(const char *file_name):
                _data(file_name){
            const char *file = strrchr(file_name, '/');
            if (file) {
                _data = file + 1;
            }
            _size = static_cast<size_t>(strlen(_data));
        }
        template<int N>
        inline SourceFile(const char (&file_name)[N]): // this is a quest
                _data(file_name),
                _size(N - 1){
            const char *file = strrchr(file_name, '/');
            if (file) {
                _data = file + 1;
                _size -= static_cast<int>(_data - file_name);
            }
        }
        const char * _data;
        size_t _size;
    };

    Logger(SourceFile file, int line);
    Logger(SourceFile file, int line, Logger::LogLevel level);
    Logger(SourceFile file, int line, Logger::LogLevel level, const char *func);
    Logger(SourceFile file, int line, bool Abort);
    ~Logger();
    LogStream &Stream();

    static LogLevel logLevel();
    static void SetLogLevel(LogLevel level);
    
    typedef void (*OutPutFunc)(const char *msg, int len);
    typedef void (*FlushFunc)();
    
    void FormatTime();
    static void SetOut(OutPutFunc func);
    static void SetFlush(FlushFunc func);

private:
    LogLevel  _level;
    Timestamp _time;
    LogStream _stream;
    SourceFile _file;
    int _line;

};

  
#define LOG_TRACE if (Common::Logger::logLevel() <= Common::Logger::TRACE) \
                Common::Logger(__FILE__, __LINE__, Common::Logger::TRACE, __func__).Stream()

#define LOG_DEBUG if (Common::Logger::logLevel() <= Common::Logger::DEBUG) \
                Common::Logger(__FILE__, __LINE__, Common::Logger::DEBUG).Stream()

#define LOG_INFO if (Common::Logger::logLevel() <= Common::Logger::INFO) \
                Common::Logger(__FILE__, __LINE__).Stream()

#define LOG_WARN Common::Logger(__FILE__, __LINE__, Common::Logger::WARN).Stream()

#define LOG_ERROR Common::Logger(__FILE__, __LINE__, Common::Logger::ERROR).Stream()

#define LOG_FATAL Common::Logger(__FILE__, __LINE__, Common::Logger::FATAL).Stream()

#define LOG_SYSERR Common::Logger(__FILE__, __LINE__, false).Stream()

#define LOG_SYSFATAL Common::Logger(__FILE__, __LINE__, true).Stream()

} // namespace

#endif // LOGGING_H_
