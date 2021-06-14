#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SocketObj {
    struct SocketObj *next;
    int socket;
} SocketObj;

SocketObj *sflist_create(int, SocketObj *);
SocketObj *slist_remove(SocketObj *, int);
SocketObj *sflist_append(SocketObj *, int);
SocketObj *sflist_at(SocketObj *, int);

/**
 * Observer pattern for each socket entry
*/
void slist_observer(SocketObj *head, void (*func)(int));