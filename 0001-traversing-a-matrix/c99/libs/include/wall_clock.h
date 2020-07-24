#ifndef __WALL_CLOCK_H__
#define __WALL_CLOCK_H__
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

static long start, end;
static struct timeval timecheck;

void wall_clock_start(void)
{
    gettimeofday(&timecheck, NULL);
    start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
}

void wall_clock_end(void)
{
    gettimeofday(&timecheck, NULL);
    end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

    printf("%ld milliseconds elapsed\n", (end - start));
}
#endif
