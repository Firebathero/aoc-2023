#include <ctype.h>
#include <stdio.h>
#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <time.h>

#define DIGIT_ARR_LEN 10

int main() {
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();
    const char* digits[] =
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
    int res = 0;
    cth_str_t line;
    while ((line = cth_getl(file)).data != NULL) {
        int first = 0, last = 0;
        for (size_t i = 0; i < line.len; ++i) {
            if (isdigit(line.data[i])) {
                first = line.data[i] - '0';
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
        for (size_t i = line.len; i >= 0; --i) {
            if (i > 0 && isdigit(line.data[i - 1])) {
                last = line.data[i - 1] - '0';
                break;
            }
            for (size_t j = 0; j < DIGIT_ARR_LEN; ++j) {
                char *dig = digits[j];
                int dig_len = strlen(dig);
                if (i + 1 >= dig_len && !cth_strncmp(dig, line.data + i - dig_len + 1, dig_len)) {
                    last = j;
                    goto considered_harmful;
                }
            }
        }
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