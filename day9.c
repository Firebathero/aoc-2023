#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXM 21
#define MAXN 200

uint64_t solve_seq() {
    return 0;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();

    int N = 250;
    uint64_t a[N][32];
    cth_buf_t line = {0};

    int arr_row = 0;
    while ((line = cth_buf_getl(file)).buf != NULL) {
        int arr_col = 0;
        int idx = 0;
        int m = line.len;
        for (; idx < m; ) {
            int is_neg = 0;
            if (line.buf[idx] == '-') {is_neg = 1; idx++;}
            if (idx < m && isdigit(line.buf[idx])) {
                uint64_t val = 0;
                while (idx < m && isdigit(line.buf[idx])) {
                    val = val * 10 + line.buf[idx] - '0';
                    idx++;
                }
                a[arr_row][arr_col] = is_neg ? -1 * val : val;
                arr_col++;
            }
            idx++;
        }
        arr_row++;
    }

    uint64_t total_res = 0;
    for (int row = 0; row < MAXN; ++row) {
        int col = MAXM;

        uint64_t first_elt[100];
        int f_idx = 0;
        uint64_t first_val = a[row][0];
        while (1) {
            int new_col = col - 1;
            for (int i = 0; i < new_col; ++i) {
                a[row][i] = a[row][i+1] - a[row][i];
            }
            first_elt[f_idx++] = a[row][0];

            int all_zero = 1;
            for (int i = 0; i < new_col; ++i) {
                if (a[row][i] != 0) {
                    all_zero = 0;
                    break;
                }
            }
            if (all_zero) break;
            col--;
        }
        for (int i = f_idx-2; i >= 0; --i) {
            first_elt[i] = first_elt[i] - first_elt[i+1];
        }
        total_res += (first_val - first_elt[0]);
    }

    printf("\n\n%lld\n", total_res);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
    fclose(file);
}
