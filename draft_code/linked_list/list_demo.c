#include "linkedlist.h"
#include <stdio.h>

int main(void)
{
    linked_list_t *list = list_create();
    if (!list)
    {
        printf("NULL\n");
        return(1);
    }

    list_add_front(list, "Alice");
    list_add_front(list, "Bob");
    list_add_front(list, "Cara");

    list_print(list);

    list_free(list);

}

