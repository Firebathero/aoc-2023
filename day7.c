#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXN 1000
#define HAND_SIZE 5

typedef enum {
    A,
    K,
    Q,
    T,
    NINE,
    EIGHT,
    SEVEN,
    SIX,
    FIVE,
    FOUR,
    THREE,
    TWO,
    J,
    CARD_TYPES
 } CARD;

typedef enum {
    FIVE_OF_KIND,
    FOUR_OF_KIND,
    FULL_HOUSE,
    THREE_OF_KIND,
    TWO_PAIR,
    PAIR,
    HIGH_CARD
} HAND_STRENGTH;

typedef struct {
    HAND_STRENGTH str;
    CARD cards[5];
    int bid;
} hand_t;


static int cmp_strength(const void* cmp_a, const void* cmp_b) {
    const hand_t *a = (const hand_t *)cmp_a;
    const hand_t *b = (const hand_t *)cmp_b;

    if (a->str == b->str) {
        for (int i = 0; i < 5; ++i) {
            if (a->cards[i] < b->cards[i]) return 1;
            else if (b->cards[i] < a->cards[i]) return -1;
        }
    } else {
        return a->str > b->str ? -1 : 1;
    }
    return 0;
}

HAND_STRENGTH get_hand_strength(CARD hand[]) {
    int freq[CARD_TYPES] = {0};
    int max_freq = 0;
    int pair_count = 0;

    int jokers = 0;
    for (int i = 0; i < HAND_SIZE; ++i) {
        if (hand[i] == J) {
            jokers++;
        }
        freq[hand[i]]++;
        if (freq[hand[i]] > max_freq) {
            max_freq = freq[hand[i]];
        }
    }

    for (int i = 0; i < CARD_TYPES; ++i) {
        if (freq[i] == 2) {
            pair_count++;
        }
    }

    switch(max_freq) {
        case 5:
            return FIVE_OF_KIND;
        case 4:
            return jokers ? FIVE_OF_KIND : FOUR_OF_KIND;
        case 3:
            if (pair_count == 1) {
                return jokers ? FIVE_OF_KIND : FULL_HOUSE;
            } else {
                return jokers ? FOUR_OF_KIND : THREE_OF_KIND;
            }
        case 2:
            if (pair_count == 2) {
                if (jokers == 2) {
                    return FOUR_OF_KIND;
                } else if (jokers == 1) {
                    return FULL_HOUSE;
                } else {
                    return TWO_PAIR;
                }
            } else {
                return jokers ? THREE_OF_KIND : PAIR;
            }
        default:
            return jokers ? PAIR : HIGH_CARD;
    }
}

void encode_hand_as_ints(char* hand, CARD a[]) {
    for (int i = 0; i < HAND_SIZE; ++i) {
        switch(hand[i]) {
            case 'A':
                a[i] = A;
            break;
            case 'K':
                a[i] = K;
            break;
            case 'Q':
                a[i] = Q;
                break;
            case 'J':
                a[i] = J;
                break;
            case 'T':
                a[i] = T;
                break;
            case '9':
                a[i] = NINE;
                break;
            case '8':
                a[i] = EIGHT;
                break;
            case '7':
                a[i] = SEVEN;
                break;
            case '6':
                a[i] = SIX;
                break;
            case '5':
                a[i] = FIVE;
                break;
            case '4':
                a[i] = FOUR;
                break;
            case '3':
                a[i] = THREE;
                break;
            case '2':
                a[i] = TWO;
                break;
            default:
                break;
        }
    }
}


int main() {
    FILE *file = fopen("input.txt", "r");
    clock_t start = clock();

    cth_buf_t line;
    int idx = 0;
    hand_t hands[MAXN];
    while ((line = cth_buf_getl(file)).buf != NULL) {
        char hand[6], bids[5];
        strncpy(hand, line.buf, 5);
        hand[5] = '\0';
        const char *space_pos = strchr(line.buf, ' ');
        strncpy(bids, space_pos + 1, 4);
        bids[4] = '\0';

        CARD h[5];
        encode_hand_as_ints(hand, h);
        HAND_STRENGTH strength = get_hand_strength(h);

        memcpy(hands[idx].cards, h, sizeof(h));
        hands[idx].str = strength;
        hands[idx].bid = atoi((char*)bids);
        idx++;
    }

    qsort(hands, MAXN, sizeof(hand_t), cmp_strength);

    uint64_t res = 0, curr = 0;
    for (int i = 0; i < MAXN; ++i) {
        curr = (i+1)*hands[i].bid;
        res += curr;
    }

    printf("%lld\n", res);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n", cpu_time_used);
    fclose(file);
}
