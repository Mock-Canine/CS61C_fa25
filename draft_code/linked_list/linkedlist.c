#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

linked_list_t *list_create(void)
{
    linked_list_t *list = malloc(sizeof(linked_list_t));
    if (!list)
        return NULL;
    list->head = NULL;
    return list;
}

void list_add_front(linked_list_t *list, const char *data)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
    {
        printf("Error when allocate node_t\n");
        exit(1);
    }
    node->data = malloc(strlen(data) + 1);
    if (!node)
    {
        printf("Error when allocate node_t\n");
        exit(1);
    }
    strcpy(node->data, data);
    node->next = list->head;
    list->head = node;
}

void list_print(const linked_list_t *list)
{
    node_t *current = list->head;
    while (current)
    {
        printf("%s -> ", current->data);
        current = current->next;
    }
   printf("NULL\n");
}

void list_free(linked_list_t *list)
{
    node_t *current = list->head;
    while (current)
    {
        node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

