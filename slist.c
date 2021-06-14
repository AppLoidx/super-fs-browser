#include "slist.h"

SocketObj *sflist_create(int socket, SocketObj *next) {
    SocketObj *new_node = (SocketObj *) malloc(sizeof(SocketObj));
    if (new_node == NULL) {
        printf("Ошибка!\n");
        exit(0);
    }
    new_node->socket = socket;
    new_node->next = next;
    return new_node;
}

SocketObj *sflist_append(SocketObj *head, int value) {
    SocketObj *cursor = head;

    if (head == NULL) return sflist_create(value, head);
    while (cursor->next != NULL) cursor = cursor->next;
    cursor->next = sflist_create(value, NULL);
    return head;
}

int slist_length(SocketObj *head) {
    SocketObj *cursor = head;
    int count = 0;
    while (cursor != NULL) {
        count++;
        cursor = cursor->next;
    }
    return count;
}

SocketObj *sflist_at(SocketObj *head, int index) {
    SocketObj *cursor = head;

    int i = 0;
    if (slist_length(head) < index || index < 0) return NULL;
    while (i < index) {
        cursor = cursor->next;
        i++;
    }
    return cursor;
}

SocketObj *slist_remove(SocketObj *head, int socket) {
    SocketObj *cursor = head;
    SocketObj *cursor_prev = NULL;
    int index = 0;
    while (cursor != NULL) {
        if (cursor->socket == socket) {
            if (index == 0) {
                SocketObj *tmp = cursor->next;
                free(cursor);
                return tmp;
            } else {
                SocketObj *tmp = cursor->next;
                cursor_prev->next = tmp;
                free(cursor);
                return head;
            }
        }
        cursor_prev = cursor;
        cursor = cursor->next;
        index++;
    }
    return head;
}

void slist_observer(SocketObj *head, void (*func)(int)) {
    int len = slist_length(head);
    int i;
    for (i = 0; i < len; i++)func(sflist_at(head, i)->socket);
}
