// https://solarianprogrammer.com/2019/04/17/c17-programming-measuring-execution-time-delaying-program/

#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <time.h>
#include <stdbool.h>

// Portable timspec_get equivalent, returns bool true on success
bool gettime(struct timespec *ts);

#endif
