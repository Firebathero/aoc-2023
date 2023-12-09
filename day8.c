#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "cth_uthash.c"

#define MAX_KEYS 100

uint64_t lcm(uint64_t a, uint64_t b) {
    uint64_t temp_a = a, temp_b = b;
    while (temp_b != 0) {
        uint64_t temp = temp_b;
        temp_b = temp_a % temp_b;
        temp_a = temp;
    }
    return (a / temp_a) * b;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();

    cth_buf_t line;
    line = cth_buf_getl(file);
    int M = 293;
    char dirs[M];
    strncpy(dirs, line.buf, line.len);
    cth_buf_getl(file);

    struct nodes *map;

    while ((line = cth_buf_getl(file)).buf != NULL) {
        char key[4], val[9];
        strncpy(key, line.buf, 3);
        key[3] = '\0';
        strncpy(val, line.buf + 7, 9);
        val[8] = '\0';

        add_node(&map, key, val);
    }
    uint64_t cycle_len[MAX_KEYS];
    int num_keys = 0;

    for (struct nodes *s = map; s != NULL; s = (struct nodes*)(s->hh.next)) {
        if (s->key[2] == 'A') {
            uint64_t curr_steps = 0;
            char curr_key[4];
            strncpy(curr_key, s->key, 3);
            curr_key[3] = '\0';
            int dir_idx = 0;

            do {
                struct nodes *curr_node = find_node(map, curr_key);

                if (dirs[dir_idx] == 'L') {
                    strncpy(curr_key, curr_node->val, 3);
                } else {
                    strncpy(curr_key, curr_node->val + 5, 3);
                }
                curr_key[3] = '\0';

                dir_idx = (dir_idx + 1) % M;
                curr_steps++;
            } while (curr_key[2] != 'Z');

            cycle_len[num_keys++] = curr_steps;
        }
    }

    uint64_t res = 1;
    for (int i = 0; i < num_keys; i++) {
        res = lcm(res, cycle_len[i]);
    }

    printf("%lld\n", res);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
    fclose(file);
}