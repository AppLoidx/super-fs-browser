#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "ui.h"

typedef struct FileObj {
    File file;
    struct FileObj *next;
} FileObj;

FileObj *flist_append(FileObj *head, char *name,
                      char *type,
                      char *date,
                      u_long size);

int flist_size(FileObj *);

FileObj *flist_at(FileObj *head, int index);

FileObj *flist_clear(FileObj *node);

