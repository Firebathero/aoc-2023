#ifndef ONE_EYE_SHUT_CRYPTIC_LULLABY_BIT_CTHULU_WATCHING_YOU_INPUT_0xDEADBEEF_H
#define ONE_EYE_SHUT_CRYPTIC_LULLABY_BIT_CTHULU_WATCHING_YOU_INPUT_0xDEADBEEF_H

#include <stdio.h>
#include <string.h>

#define FATBUF 10000

typedef struct {
    char* data;
    size_t len;
} cth_str_t;

#define cth_string(str)     { sizeof(str) - 1, (u_char *) str }
#define cth_str_set(str, text)                                               \
    (str)->len = sizeof(text) - 1; (str)->data = (u_char *) text
#define cth_tolower(c)      (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define cth_toupper(c)      (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)
#define cth_strncmp(s1, s2, n)  strncmp((const char *) s1, (const char *) s2, n)

cth_str_t cth_getl(FILE *file);
void cth_strtok(char *line, const char *delimiter);

#endif // ONE_EYE_SHUT_CRYPTIC_LULLABY_BIT_CTHULU_WATCHING_YOU_INPUT_0xDEADBEEF_H
