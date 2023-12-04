#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <ctype.h>
#include <stdio.h>
#include <time.h>

const char SPACE = ' ';
const int SKIP_GARBAGE = 9;
#define N 213

char cards[200][200];

int main() {
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();
    int res = 0;
    cth_buf_t line;
    line = cth_buf_getl(file);
    int M = strlen(line.buf);
    strcpy(cards[0], line.buf);
    int idx = 1;
    while ( (line = cth_buf_getl(file)).buf != NULL) {
        strcpy(cards[idx++], line.buf);
    }
    static int copies[N+1];
    static int matches[N];
    for (int i = 0;i < N; ++i) matches[i] = 0;
    for (int i = 0;i < N; ++i) copies[i] = 1;

    static int lookup[100];
    for (int i = 0; i < N; ++i) {
        int match_ct = 0;
        int count = 0;
        int idx = SKIP_GARBAGE;
        memset(lookup, 0, sizeof(lookup));
        while (1) {
            if (cards[i][idx] == '|') break;
            if (idx < M && isdigit(cards[i][idx])) {
                int val = 0;
                while (idx < M && isdigit(cards[i][idx])) {
                    val = val * 10 + cards[i][idx]-'0';
                    idx++;
                }
                lookup[val] = 1;
            }
            idx++;
        }

        while ( idx < M ) {
            if (idx < M && isdigit(cards[i][idx])) {
                int val = 0;
                while (idx < M && isdigit(cards[i][idx])) {
                    val = val * 10 + cards[i][idx]-'0';
                    idx++;
                }
                if (lookup[val]) {
                    match_ct++;
                }
            }
            idx++;
        }

        matches[i] = match_ct;

        int curr_copies = copies[i];
        for (int k = i+1; k <= i + match_ct; ++k) {
            copies[k] += curr_copies;
        }
    }
    for (int i = 0; i < N; ++i) {
        printf("%d\n", copies[i]);
        res += copies[i];
    }
    clock_t end = clock();
    printf("%d\n", res);
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
    fclose(file);

    return 0;
}


