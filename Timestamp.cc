/*
 * Timestamp.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月24日 23时06分33秒
 *
 */

#include "Timestamp.h"

namespace Common {

Timestamp::Timestamp():
    _microsecond(0) {

}

Timestamp::Timestamp(int64_t microsecond):
    _microsecond(microsecond) {
    
}
Timestamp::Timestamp(const Timestamp &rhs) {
    _microsecond = rhs._microsecond;
}

Timestamp& Timestamp::operator=(const Timestamp &rhs) {
    _microsecond = rhs._microsecond;
    return *this;
}

Timestamp::~Timestamp() {

}

Timestamp Timestamp::Now() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return Timestamp(tv.tv_sec * persecond + tv.tv_usec);
}

std::string Timestamp::ToString() {
    char buf[32] = {0};
    int microseconds = 0;
    struct tm  tm_time;

    time_t seconds = static_cast<time_t>(_microsecond / persecond);
    gmtime_r(&seconds, &tm_time);
    microseconds = static_cast<int>(_microsecond % persecond);

    snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d.%06d",
            tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
            tm_time.tm_hour + 8, tm_time.tm_min, tm_time.tm_sec, microseconds);

    return buf;
}

int64_t Timestamp::MicroSecond() const {
    return _microsecond;
}

time_t Timestamp::ToTime() const {
    return static_cast<time_t>(_microsecond / persecond);
}


} // namespace 

