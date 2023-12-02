#include <ctype.h>
#include <stdio.h>
#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <time.h>

#define RED_MAX    12
#define GREEN_MAX  13
#define BLUE_MAX   14

typedef enum {
    RED,
    GREEN,
    BLUE,
    NONE
} COLOR;

inline int32_t consume_int(cth_buf_t *line) {
char num[10] = {0};
int pow_idx = 0;
    while (isdigit((unsigned char)line->buf[line->readpos])) {

        num[pow_idx] = line->buf[line->readpos] - '0';
        line->readpos++;
        pow_idx++;
    }
    int res = 0;
    for (int i = 0; i < pow_idx; i++) {
        res = res * 10 + num[i];
    }

    return res;
}

inline COLOR consume_color(cth_buf_t *line) {
    if (strncmp(line->buf + line->readpos, "green", 5) == 0) {
        line->readpos += 5;
        return GREEN;
    }
    else if (strncmp(line->buf + line->readpos, "blue", 4) == 0) {
        line->readpos += 4;
        return BLUE;
    }
    else if (strncmp(line->buf + line->readpos, "red", 3) == 0) {
        line->readpos += 3;
        return RED;
    }
    return NONE;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();
    int res = 0;

    cth_buf_t line;
    while ((line = cth_buf_getl(file)).buf != NULL) {
        cth_buf_t *p_line = &line;

        SKIP_TO_CHAR(p_line, ':')
        ADVANCE_PAST_CHAR(p_line, ':')
        SKIP_SPACES(p_line)

        int g_max, b_max, r_max;
        g_max = b_max = r_max = 0;

        while (p_line->readpos < p_line->len) {
            int32_t num = consume_int(p_line);
            SKIP_SPACES(p_line)
            COLOR c = consume_color(p_line);
            switch (c) {
                case RED:
                    r_max = cth_max(r_max, num);
                    break;
                case BLUE:
                    b_max = cth_max(b_max, num);
                    break;
                case GREEN:
                    g_max = cth_max(g_max, num);
                    break;
                default:
                    break;
            }
            ADVANCE_TO_NEXT_SEGMENT(p_line)
            SKIP_SPACES(p_line)
        }
        res += (g_max * r_max * b_max);
    }

    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
    printf("%d", res);

    fclose(file);
    return 0;
}



