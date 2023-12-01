#include "one_eye_shut_cryptic_lullaby_bit_cthulu_watching_you_input_0xDEADBEEF.h"



cth_str_t cth_getl(FILE *file) {
    static char buf[FATBUF];
    cth_str_t line = {NULL, 0};

    if (fgets(buf, FATBUF, file) != NULL) {
        buf[strcspn(buf, "\n")] = 0;
        line.data = buf;
        line.len = strlen(buf);
    }

    return line;
}

void cth_strtok(char *line, const char *delimiter) {
    char *token = strtok(line, delimiter);
    while (token != NULL) {
        token = strtok(NULL, delimiter);
    }
}
