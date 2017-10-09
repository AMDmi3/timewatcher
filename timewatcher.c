#include <stdio.h>
#include <time.h>
#include <unistd.h>

void update_clock(struct timespec* prev, struct timespec* curr, clockid_t mode) {
    prev->tv_sec = curr->tv_sec;
    prev->tv_nsec = curr->tv_nsec;

    clock_gettime(mode, curr);
}

void check_clock(struct timespec* prev, struct timespec* curr, const char* desc) {
    if (curr->tv_sec < prev->tv_sec || (curr->tv_sec == prev->tv_sec && curr->tv_nsec < prev->tv_nsec)) {
        fprintf(stderr, "%s time wend backwards!!!\n", desc);
        fprintf(stderr, "  was: %ld.%06ld\n", (long)prev->tv_sec, (long)prev->tv_nsec);
        fprintf(stderr, "  now: %ld.%06ld\n", (long)curr->tv_sec, (long)curr->tv_nsec);
    }
}

int main(void) {
    struct timespec monotonic_prev;
    struct timespec monotonic_curr;
    struct timespec realtime_prev;
    struct timespec realtime_curr;

    update_clock(&monotonic_prev, &monotonic_curr, CLOCK_MONOTONIC);
    update_clock(&realtime_prev, &realtime_curr, CLOCK_REALTIME);

    while (1) {
        usleep(10000);

        update_clock(&monotonic_prev, &monotonic_curr, CLOCK_MONOTONIC);
        update_clock(&realtime_prev, &realtime_curr, CLOCK_REALTIME);

        check_clock(&monotonic_prev, &monotonic_curr, "monotonic");
        check_clock(&realtime_prev, &realtime_curr, "realtime");
    }

    return 0;
}
