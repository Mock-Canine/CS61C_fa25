#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

void increment(char *str)
{   
    for (int i = 0; i < strlen(str); i++)
        str[i]++;
}

void rotate(void *front, void *separator, void *end)
{
    // typecast into char * before arithmetic, using void * for 
    // arithmetic computation is not a standard C way
    size_t first = (char *)separator - (char *)front;
    size_t last = (char *)end - (char *)separator; 

    char tmp[first];
    memcpy(tmp, front, first);
    memmove(front, separator, last);
    memcpy((char *)front + last, tmp, first);
}

int main(void)
{
   char s[] = "Hello";
   increment(s);
   uint32_t arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   uint16_t *ptr = (uint16_t *)(arr + 10);
   void *pp = arr;
   pp++;
   rotate(arr, arr + 5, ptr);
   rotate(arr, arr + 1, ptr);
   rotate(arr + 4, arr + 5, arr + 6);
}
