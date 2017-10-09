#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    struct timespec tp, prev_tp;
    clock_gettime(CLOCK_MONOTONIC, &prev_tp);

    while (1) {
        usleep(1000);

        clock_gettime(CLOCK_MONOTONIC, &tp);

        if (tp.tv_sec < prev_tp.tv_sec || (tp.tv_sec == prev_tp.tv_sec && tp.tv_nsec < prev_tp.tv_nsec)) {
            fprintf(stderr, "Monotonic time wend backwards!!!\n");
            fprintf(stderr, "  was: %ld.%06ld\n", (long)prev_tp.tv_sec, (long)prev_tp.tv_nsec);
            fprintf(stderr, "  now: %ld.%06ld\n", (long)tp.tv_sec, (long)tp.tv_nsec);
        }

        prev_tp.tv_sec = tp.tv_sec;
        prev_tp.tv_nsec = tp.tv_nsec;
    }

    return 0;
}
