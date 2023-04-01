//
// Created by Stefan on 13/03/2023.
//

#ifndef LABDB_UTILS_H
#define LABDB_UTILS_H
#include <sys/time.h>

#include <time.h>

struct timeval getCurrentTime();
float time_diff_microseconds(struct timeval start, struct timeval end);

#endif //LABDB_UTILS_H
