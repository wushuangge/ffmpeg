#include "./common.h"

time_t get_now_microseconds() {
    time_t result;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    result = 1000000 * tv.tv_sec + tv.tv_usec;
    return result;
}
