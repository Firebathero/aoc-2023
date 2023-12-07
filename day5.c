#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define MAX_RANGES 4096
#define SENTINEL_VALUE UINT64_MAX
#define LAST_MAPPING 7

typedef struct {
    uint64_t next_dest;
    uint64_t src_min;
    uint64_t src_max;
} translation_node_t;

typedef enum {
    DEST,
    SRC,
    OFFSET
} pos_t;

typedef enum {
    STOS,
    STOF,
    FTOW,
    WTOL,
    LTOT,
    TTOH,
    HTOL,
    NUM_ARRAYS
} conversion_t;

void initialize_array(translation_node_t array[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        array[i].next_dest = SENTINEL_VALUE;
        array[i].src_min = SENTINEL_VALUE;
        array[i].src_max = SENTINEL_VALUE;
    }
}

int main() {
    int rep = 1;
    uint32_t N = 187;
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();

    translation_node_t stos[MAX_RANGES];
    translation_node_t ttoh[MAX_RANGES];
    translation_node_t htol[MAX_RANGES];
    translation_node_t seed[MAX_RANGES];
    translation_node_t stof[MAX_RANGES];
    translation_node_t ltot[MAX_RANGES];
    translation_node_t ftow[MAX_RANGES];
    translation_node_t wtol[MAX_RANGES];


    initialize_array(seed, MAX_RANGES);
    initialize_array(stos, MAX_RANGES);
    initialize_array(ttoh, MAX_RANGES);
    initialize_array(htol, MAX_RANGES);
    initialize_array(stof, MAX_RANGES);
    initialize_array(ltot, MAX_RANGES);
    initialize_array(ftow, MAX_RANGES);
    initialize_array(wtol, MAX_RANGES);

    translation_node_t *arrs[NUM_ARRAYS] =
    {
             stos,
             stof,
             ftow,
             wtol,
             ltot,
             ttoh,
             htol
    };

    cth_buf_t seed_line;
    seed_line = cth_buf_getl(file);
    int M = seed_line.size;
    int seed_idx = 0;
    for (int i = 0; i < M; ++i) {
        if (!isdigit(seed_line.buf[i])) {
            continue;
        } else {
            uint64_t val = 0;
            while (i < M && isdigit(seed_line.buf[i])) {
                val = val * 10 + (seed_line.buf[i] - '0');
                i++;
            }
            seed[seed_idx++].next_dest = val;
        }
    }

    int MAP_IDX = 0;
    cth_buf_t line;
    cth_buf_getl(file);
    cth_buf_getl(file);


    int line_idx = 0;
    while (rep < N) {
        line = cth_buf_getl(file);
        if (line.buf == NULL) {
            break;
        }

        if (!isdigit(line.buf[0])) {
            cth_buf_getl(file);
            MAP_IDX++;
            line_idx = 0;

            if (MAP_IDX == LAST_MAPPING) {
                goto calc_my_shit_father;
            }
            continue;
        }

        int idx = 0;
        M = line.size;
        int CONVERSION_PHASE = 0;
        while (idx < M) {
            while (idx < M && line.buf[idx] == ' ') { idx++; }
            uint64_t val = 0;
            while (idx < M && isdigit(line.buf[idx])) {
                val = val * 10 + (line.buf[idx] - '0');
                idx++;
            }

            switch(CONVERSION_PHASE) {
                case DEST:
                    (arrs[MAP_IDX][line_idx]).next_dest = val;
                    break;
                case SRC:
                    (arrs[MAP_IDX][line_idx]).src_min = val;
                    break;
                case OFFSET:
                    (arrs[MAP_IDX][line_idx]).src_max = (arrs[MAP_IDX][line_idx]).src_min + val - 1;
                    if (MAP_IDX == 0)
                    break;
            }
            idx++;
            CONVERSION_PHASE = (CONVERSION_PHASE + 1) % 3;
        }
        line_idx++;
        rep++;
        if (MAP_IDX >= NUM_ARRAYS || line_idx >= MAX_RANGES) {
            break;
        }

    }

    for (int i = 0; i < MAX_RANGES; ++i) {
        if (stos[i].next_dest == SENTINEL_VALUE) {
            break;
        }
    }

    typedef struct {
        uint64_t start;
        uint64_t end;
    } range_t;

    range_t dests[MAX_RANGES];
    for (int i = 0; i < MAX_RANGES; ++i) {
        dests[i].start = SENTINEL_VALUE;
        dests[i].end =  SENTINEL_VALUE;
    }

    calc_my_shit_father:

    for (int i = 0; i < MAX_RANGES; i += 2) {
        if (i + 1 < MAX_RANGES && seed[i].next_dest != SENTINEL_VALUE) {
            dests[i / 2].start = seed[i].next_dest;
            dests[i / 2].end = seed[i].next_dest + seed[i + 1].next_dest - 1;
        } else {
            break;
        }
    }

    for (int phase = 0; phase < NUM_ARRAYS; ++phase) {
        range_t new_dests[MAX_RANGES];
        int new_dests_count = 0;

        for (int j = 0; j < MAX_RANGES && dests[j].start != SENTINEL_VALUE; ++j) {
            if (dests[j].start == SENTINEL_VALUE) {
                continue;
            }
            int transformed = 0;

            for (int k = 0; k < MAX_RANGES && arrs[phase][k].next_dest != SENTINEL_VALUE; ++k) {
                uint64_t src_min = arrs[phase][k].src_min;
                uint64_t src_max = arrs[phase][k].src_max;

                if (dests[j].start <= src_max && dests[j].end >= src_min) {
                    uint64_t start_in_range = cth_max(dests[j].start, src_min);
                    uint64_t end_in_range = cth_min(dests[j].end, src_max);
                    uint64_t offset = start_in_range - src_min;
                    new_dests[new_dests_count++] = (range_t){arrs[phase][k].next_dest + offset,
                                                    arrs[phase][k].next_dest + offset + (end_in_range - start_in_range)};

                    transformed = 1;
                }
            }  //End landing src ranges eval
            if (!transformed) {
                new_dests[new_dests_count++] = dests[j];
            }
        } //End incoming dest eval

        memcpy(dests, new_dests, sizeof(new_dests[0]) * new_dests_count);
        if (new_dests_count < MAX_RANGES) {
            dests[new_dests_count].start = dests[new_dests_count].end = SENTINEL_VALUE;
        }
        for (int i = new_dests_count; i < MAX_RANGES; ++i) {
            dests[i].start = SENTINEL_VALUE;
            dests[i].end = SENTINEL_VALUE;
        }
    }

    uint64_t lowest_dest = UINT64_MAX;
    for (int i = 0; i < MAX_RANGES && dests[i].start != SENTINEL_VALUE; ++i) {
        if (dests[i].start < lowest_dest) {
            lowest_dest = dests[i].start;
        }
    }

    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
    printf("Lowest destination: %llu\n", lowest_dest);
    fclose(file);
}
