#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <zconf.h>
#include <string.h>
#include "utils.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "slist.h"
#include <event.h>
#include <errno.h>
#include <sys/inotify.h>
#include <limits.h>

#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME 16 /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*size of one event*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*buffer to store the data of events*/

int run_server(unsigned int port, char *path);

