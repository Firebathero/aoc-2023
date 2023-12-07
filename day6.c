#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <ctype.h>
#include <stdio.h>
#include <time.h>

u_int64_t dist_a[1];
u_int64_t time_a[1];

u_int64_t find_first(int i, __uint128_t n) {
    __uint128_t low = 0, high = n - 1;
    __uint128_t first = n;

    while (low <= high) {
        __uint128_t mid = low + (high - low) / 2;
        __uint128_t time_left = time_a[i] - mid;

        if ((__uint128_t)mid * time_left > dist_a[i]) {
            if (mid == 0 || (__uint128_t)(mid - 1) * (time_left + 1) <= dist_a[i]) {
                return mid;
            }
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return first;
}

u_int64_t find_last(int i, __uint128_t n) {
    __uint128_t low = 0, high = n;
    __uint128_t last = 0;

    while (low < high) {
        __uint128_t mid = low + (high - low) / 2;
        __uint128_t time_left = time_a[i] - mid;

        if ((__uint128_t)mid * time_left <= dist_a[i]) {
            high = mid;
        } else {
            last = mid;
            low = mid + 1;
        }
    }
    return last;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();

    cth_buf_t line = cth_buf_getl(file);
    int idx = 0;
    u_int64_t time_val = 0;
    while (idx < line.len) {
        if (isdigit(line.buf[idx])) {
            time_val = time_val * 10 + line.buf[idx] - '0';
        }
        idx++;
    }
    time_a[0] = time_val;
    line = cth_buf_getl(file);
    idx = 0;
    u_int64_t dist_val = 0;
    while (idx < line.len) {
        if (isdigit(line.buf[idx])) {
            dist_val = dist_val * 10 + line.buf[idx] - '0';
        }
        idx++;
    }
    dist_a[0] = dist_val;

    u_int64_t first_win = find_first(0, time_a[0]);
    u_int64_t last_win = find_last(0, time_a[0]);
    u_int64_t res = last_win - first_win + 1;

    printf("%lld\n", res);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
    fclose(file);
}
