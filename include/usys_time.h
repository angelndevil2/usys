#ifndef USYS_TIME
#define USYS_TIME

namespace usys {
    #if defined(__WIN32__)

    #include <windows.h>

    msec_t time_ms(void)
    {
        // timeGetTime returns the time since Windows was started, not the milliseconds since the Epoc
        return timeGetTime();
    }

    #else

    #include <sys/time.h>
    #include <stddef.h>

    typedef long long msec_t;

    msec_t time_ms(void)
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (msec_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }

    #endif
}

#endif