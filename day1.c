#include <ctype.h>
#include <stdio.h>
#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <time.h>

#define DIGIT_ARR_LEN 10
#define PREFETCH_DISTANCE 64

static const int lookup_dig[256] = {
        ['0'] = 1, ['1'] = 1, ['2'] = 1, ['3'] = 1,
        ['4'] = 1, ['5'] = 1, ['6'] = 1, ['7'] = 1,
        ['8'] = 1, ['9'] = 1
};
static const char* digits[] =
        {
                "zero",
                "one",
                "two",
                "three",
                "four",
                "five",
                "six",
                "seven",
                "eight",
                "nine",
        };
int main() {

    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();
    int res = 0;
    cth_str_t line;
    while ((line = cth_getl(file)).data != NULL) {

        int first = 0, last = 0;
        for (size_t i = 0; i < line.len; ++i) {
            char ch = line.data[i - 1];
            if (ch >= '0' && ch <= '9') {
                first = ch - '0';
                break;
            }
            for (size_t j = 0; j < DIGIT_ARR_LEN; ++j) {
                char *dig = digits[j];
                int dig_len = strlen(dig);
                if (line.len - i - dig_len >= 0 && !cth_strncmp(dig, line.data + i, dig_len)) {
                        first = j;
                        goto reverse;
                }
            }
        }

        reverse:
        __builtin_prefetch(line.data + line.len - PREFETCH_DISTANCE, 0, 0);
        size_t i = line.len;
        do {
            char ch = line.data[i - 1];
            if (ch >= '0' && ch <= '9') {
                first = ch - '0';
                break;
            }

            for (size_t j = 0; j < DIGIT_ARR_LEN; ++j) {
                const char *dig = digits[j];
                size_t dig_len = strlen(dig);

                if (i >= dig_len) {
                    size_t k = 0;
                    for (; k < dig_len; ++k) {
                        if (dig[k] != line.data[i - dig_len + k]) {
                            break;
                        }
                    }
                    if (k == dig_len) {
                        first = j;
                        goto considered_harmful;
                    }
                }
            }
        } while (i-- > 1);

        considered_harmful:
        res += first * 10 + last;
    }
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
    printf("%d", res);

    fclose(file);
    return 0;
}