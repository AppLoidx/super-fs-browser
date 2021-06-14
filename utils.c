#include "utils.h"

bool is_directory(const char *path) {
    struct stat buffer;
    if (stat(path, &buffer) != 0) return 0;
    return S_ISDIR(buffer.st_mode);
}

bool file_exists(char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

char *trim(char *str) {
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if (str == NULL) { return NULL; }
    if (str[0] == '\0') { return str; }

    len = strlen(str);
    endp = str + len;

    while (isspace((unsigned char) *frontp)) { ++frontp; }
    if (endp != frontp) {
        while (isspace((unsigned char) *(--endp)) && endp != frontp) {}
    }

    if (frontp != str && endp == frontp)*str = '\0';
    else if (str + len - 1 != endp)*(endp + 1) = '\0';

    endp = str;
    if (frontp != str) {
        while (*frontp) { *endp++ = *frontp++; }
        *endp = '\0';
    }

    return str;
}


