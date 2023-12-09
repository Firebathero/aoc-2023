#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct nodes {
    char *key;                 // Key as a char*
    char *val;                 // Value as a char*
    UT_hash_handle hh;         // Makes this structure hashable
};

void add_node(struct nodes **nodes, const char *key, const char *val) {
    struct nodes *s;

    HASH_FIND_STR(*nodes, key, s);
    if (s == NULL) {
        s = malloc(sizeof(struct nodes));
        s->key = strdup(key);
        HASH_ADD_KEYPTR(hh, *nodes, s->key, strlen(s->key), s);
    } else {
        free(s->val);
    }
    s->val = strdup(val);
}

struct nodes *find_node(struct nodes *nodes, const char *key) {
    struct nodes *s;

    HASH_FIND_STR(nodes, key, s);
    return s;
}

void print_nodes(struct nodes *map)
{
    struct nodes *s;

    for (s = map; s != NULL; s = (struct nodes*)(s->hh.next)) {
        printf("key %s: val %s\n", s->key, s->val);
    }
}
int by_val(const struct nodes *a, const struct nodes *b)
{
    return strcmp(a->val, b->val);
}

int by_key(const struct nodes *a, const struct nodes *b)
{
    return strcmp(a->key, b->key);
}