/*
 * Timestamp.h -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月24日 21时07分16秒
 *
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <stdint.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

namespace Common {

class Timestamp {
public:
    Timestamp();
    Timestamp(int64_t );
    Timestamp(const Timestamp &);
    Timestamp& operator=(const Timestamp &);
    ~Timestamp();
    static Timestamp Now();
    std::string ToString();
    int64_t MicroSecond() const;
    time_t ToTime() const;
    static const int persecond = 1000 * 1000;
private:
    int64_t _microsecond;
};
} // namespace 

#endif // TIMESTAMP_H_

