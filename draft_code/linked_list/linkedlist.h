#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node_t 
{
    char *data;
    struct node_t *next;
} node_t;

typedef struct 
{
    node_t *head;
} linked_list_t;

linked_list_t* list_create(void);

void list_add_front(linked_list_t *list, const char *data);

void list_print(const linked_list_t *list);

void list_free(linked_list_t *list);

#endif
