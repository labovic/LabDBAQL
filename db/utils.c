//
// Created by Stefan on 13/03/2023.
//
#include "utils.h"
#define NANOS_IN_SECOND 1000000000

struct timeval getCurrentTime()
{
    struct timeval ts;
    gettimeofday(&ts, NULL);
    return ts;
}

float time_diff_microseconds(struct timeval start, struct timeval end) {
    long long sec1 = start.tv_sec * 1000000;
    long long sec2 = end.tv_sec * 1000000;
    long long ms1 = start.tv_usec;
    long long ms2 = end.tv_usec;

    sec1 += ms1;
    sec2 += ms2;

    return (float)(sec2 - sec1)/1000000;

}

