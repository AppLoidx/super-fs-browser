#include "flist.h"

FileObj *flist_create(FileObj *next, char *name, char *type, char *date, u_long size) {

    FileObj *new_node = (FileObj *) malloc(sizeof(FileObj));
    if (new_node == NULL) exit(1);


    new_node->file.size = size;

    new_node->file.type = malloc(strlen(type) * sizeof(char));
    strcpy(new_node->file.type, type);

    new_node->file.name = malloc(255 * sizeof(char));
    strcpy(new_node->file.name, name);

    new_node->file.date = malloc(strlen(date) * sizeof(char));
    strcpy(new_node->file.date, date);

    new_node->next = next;
    return new_node;
}

FileObj *flist_append(FileObj *head, char *name, char *type, char *date, u_long size) {
    FileObj *cursor = head;

    if (head == NULL) return flist_create(head, name, type, date, size);
    while (cursor->next != NULL) cursor = cursor->next;
    cursor->next = flist_create(NULL, name, type, date, size);
    return head;
}

FileObj *flist_at(FileObj *head, int index) {
    FileObj *cursor = head;
    int i = 0;
    if (flist_size(head) < index || index < 0) return NULL;
    while (i < index) {
        cursor = cursor->next;
        i++;
    }
    return cursor;
}

int flist_size(FileObj *head) {
    FileObj *cursor = head;
    int count = 0;
    while (cursor != NULL) {
        count++;
        cursor = cursor->next;
    }
    return count;
}

FileObj *flist_clear(FileObj *node) {
    FileObj *nodeForFree;
    while (node != NULL) {
        nodeForFree = node;
        node = node->next;
        free(nodeForFree->file.type);
        free(nodeForFree->file.name);
        free(nodeForFree->file.date);
        free(nodeForFree);
    }
    return node;
}
