#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <ctype.h>
#include <stdio.h>
#include <time.h>

#define N 140
#define M 140

char eng[200][200];

typedef enum {
    NOT_FOUND,
    FOUND
} SEARCH_STATUS;

int in_bounds(int i, int j) {
    return (i >= 0 && j >= 0 && i < N && j < M);
}

int is_match_at_position(int x, int y, char *matches, int num_matches) {
    for (int i = 0; i < num_matches; ++i) {
        if (eng[x][y] == matches[i]) {
            return 1;
        }
    }
    return 0;
}

int find_adjacent_match(xy_t *start, xy_t *found_loc, char *matches, int num_matches) {

    if (in_bounds(start->x, start->y-1) && is_match_at_position(start->x, start->y-1, matches, num_matches)) {
        *found_loc = (xy_t){start->x, start->y-1, 0};
        return FOUND;
    }
    if (in_bounds(start->x, start->y+start->len+1) && is_match_at_position(start->x, start->y+start->len+1, matches, num_matches)) {
        *found_loc = (xy_t){start->x, start->y+start->len+1, 0};
        return FOUND;
    }

    for (int x = start->x, y = start->y-1; y <= start->y + start->len + 1; ++y) {
        if (in_bounds(x+1, y) && is_match_at_position(x+1, y, matches, num_matches)) {
            *found_loc = (xy_t){x+1, y, 0};
            return FOUND;
        }
        if (in_bounds(x-1, y) && is_match_at_position(x-1, y, matches, num_matches)) {
            *found_loc = (xy_t){x-1, y, 0};
            return FOUND;
        }
    }

    return NOT_FOUND;
}


int main() {
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();
    int res = 0;
    cth_buf_t line;
    line = cth_buf_getl(file);
    strcpy(eng[0], line.buf);
    int idx = 1;
    while ( (line = cth_buf_getl(file)).buf != NULL) {
        strcpy(eng[idx++], line.buf);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (eng[i][j] == '*') {
                xy_t gear_loc = {i, j, 0};
                xy_t dig1 = {0};
                xy_t dig2 = {0};
                int val1 = 0, val2 = 0;
                eng[gear_loc.x][gear_loc.y] = '.';
                if (find_adjacent_match(&gear_loc, &dig1, "0123456789", 10) == FOUND) {
                    int start_x = dig1.x;
                    int start_y = dig1.y;
                    while (in_bounds(start_x, start_y - 1) && isdigit(eng[start_x][start_y - 1])) {
                        start_y--;
                    }
                    while (in_bounds(start_x, start_y) && isdigit(eng[start_x][start_y])) {
                        val1 = val1 * 10 + (eng[start_x][start_y] - '0');
                        eng[start_x][start_y] = '.';
                        start_y++;
                    }

                    if (find_adjacent_match(&gear_loc, &dig2, "0123456789", 10) == FOUND) {
                        start_x = dig2.x;
                        start_y = dig2.y;
                        while (in_bounds(start_x, start_y - 1) && isdigit(eng[start_x][start_y - 1])) {
                            start_y--;
                        }
                        while (in_bounds(start_x, start_y) && isdigit(eng[start_x][start_y])) {
                            val2 = val2 * 10 + (eng[start_x][start_y] - '0');
                            eng[start_x][start_y] = '.';
                            start_y++;
                        }
                        res += val1*val2;
                    }
                }
            }
        }
    }
    clock_t end = clock();
    printf("%d\n", res);
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);

    fclose(file);
    return 0;
}



