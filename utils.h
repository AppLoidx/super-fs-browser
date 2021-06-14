#pragma once

#include <zconf.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>


#define BUFFER_TMP_FILE "tmp_open_file"

#define REQUEST_BODY_OFFSET     10
#define RESPONSE_BODY_OFFSET    10

#define OBSERVE_STATUS(STATUS) \
        STATUS(SUCCESS)   \
        STATUS(UPDATE)   \
        STATUS(ERROR)  \

#define OBSERVE_COMMAND(COMMAND) \
        COMMAND(GET_LIST)   \
        COMMAND(GET_FILE)  \
        COMMAND(UPLOAD)  \
        COMMAND(UNDEFINED)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum Command {
    OBSERVE_COMMAND(GENERATE_ENUM)
} Command;

typedef enum Status {
    OBSERVE_STATUS(GENERATE_ENUM)
} Status;

static const char *COMMAND[] = {OBSERVE_COMMAND(GENERATE_STRING)};
static const char *STATUS[] = {OBSERVE_STATUS(GENERATE_STRING)};

char *trim(char *str);

bool is_directory(const char *path);

bool file_exists(char *filename);
