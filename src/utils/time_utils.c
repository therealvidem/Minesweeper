// https://solarianprogrammer.com/2019/04/17/c17-programming-measuring-execution-time-delaying-program/

#include "time_utils.h"

bool gettime(struct timespec *ts)
{
#ifdef _MSC_VER
    if (timespec_get(ts, TIME_UTC) == TIME_UTC)
    {
        return true;
    }
#else
    if (clock_gettime(CLOCK_REALTIME, ts) == 0)
    {
        return true;
    }
#endif
    return false;
}
