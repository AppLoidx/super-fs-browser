#pragma once

#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <zconf.h>
#include "utils.h"

#define BACK_TO_HOME_LETTER 'H'
#define BACK_TO_HOME_LETTER_SPACED " H "

#define DOWNLOAD_LETTER 'D'
#define DOWNLOAD_LETTER_SPACED " D "

#define UPLOAD_LETTER 'U'
#define UPLOAD_LETTER_SPACED " U "

#define EXIT_LETTER 'Q'
#define EXIT_LETTER_SPACED " Q "

#define OPEN_LETTER 'O'
#define OPEN_LETTER_SPACED " O "

#define REFRESH_LETTER 'R'
#define REFRESH_LETTER_SPACED " R "

#define EXIT_VIEW_MODE_LETTER 'C'
#define EXIT_VIEW_MODE_LETTER_SPACED "C"

#define HELP_LETTER 'H'
#define HELP_LETTER_SPACED " H "


extern bool view_mode;

typedef struct File {
    char *type;
    char *name;
    u_long size;
    char *date;
} File;

void init_file_wrap();

void print_files_info();

void append_file_info(File *file);

void run_ui();

void start_read_key(void (*on_select)(char *, bool), void (*on_download)(char *), void (*on_upload)(char *));

void init_file_view();