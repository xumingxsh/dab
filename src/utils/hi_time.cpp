#include "utils/hi_time.h"

#include <sys/time.h>

namespace dab {
long long currentMs() {
    static const long long SEC2MSEC = 1000;
    struct timeval t;
    gettimeofday(&t, nullptr);
    return t.tv_sec * SEC2MSEC + t.tv_usec / SEC2MSEC;
}
}