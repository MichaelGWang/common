#include <sys/time.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>

inline void time_delta(const struct timeval& begin, const struct timeval& end) {
    int delta_usec = end.tv_usec - begin.tv_usec;
    time_t delta_sec = end.tv_sec - begin.tv_sec;
    
    if (delta_usec < 0) {
        delta_usec = -delta_sec;
        --delta_sec;
    }

    std::cout << delta_sec + static_cast<float>(delta_usec) / 1000000 << std::endl;
}

int main() {
    struct timeval begin;
    struct timeval end;
    
    gettimeofday(&begin, NULL);
    sleep(1);
    gettimeofday(&end, NULL);

    printf ("%ld %d\n", begin.tv_sec, begin.tv_usec);
    printf ("%ld %d\n", end.tv_sec, end.tv_usec);

    time_delta(begin, end);
    return 0;
}
