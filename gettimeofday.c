#include <stdio.h>
#include <sys/time.h>

//int gettimeofday ( struct timeval *tp ,  struct timezone *tz )
/*
The gettimeofday() function gets the system’s clock time. 
The current time is expressed in elapsed seconds and microseconds since 00:00:00, January 1, 1970 (Unix Epoch). 
*/

/* The 1st argument points to the timeval structure:
struct    timeval  {
  time_t        tv_sec ;   //used for seconds
  suseconds_t       tv_usec ;   //used for microseconds
}
*/

/*
The 2nd argument points to the timezone structure. 
It should normally be set to NULL because struct timezone is obsolete. 
This argument is for backwards compatibility only.
*/


//On success, the gettimeofday() return 0, for failure the function returns -1.

int main() {
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  printf("seconds : %ld\nmicro seconds : %ld",
    current_time.tv_sec, current_time.tv_usec);

  return 0;
}