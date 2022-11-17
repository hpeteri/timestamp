#ifndef N1_TIMESTAMP_H
#define N1_TIMESTAMP_H

#include <stdint.h>
uint64_t n1_gettimestamp_microseconds();

#if defined(N1_TIMESTAMP_IMPLEMENTATION)

#if defined(__WIN32)
static long long n1_timestamp_win32_pfq;
#endif

uint64_t n1_gettimestamp_microseconds(){

#if defined(__linux__)

  timespec t;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
  return (t.tv_sec * 1000000) + (t.tv_nsec / 1000);

#elif defined(__WIN32)

  if(!n1_timestamp_win32_pfq){
    LARGE_INTEGER temp;
    QueryPerformanceFrequency(&temp);
    n1_timestamp_win32_pfq = temp.QuadPart;
  }
  
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (1000000 * now.QuadPart / n1_timestamp_win32_pfq)

#endif
}


#endif
#endif
