#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void test(int8_t *arr, int8_t *brr)
{
    memcpy(brr, arr, 4 * sizeof(int8_t));
}
    
int main(void)
{
    /* If looking at the address of arr and crr with gdb, they are back-to-back in memory,
     * so after running the codes, arr[0] will be 4. Unlike array, pointers do not have the 
     * concept of "length", so they do not know how many bytes they "hold" like array, so
     * the codes get no compling error or valgrind error. Note that the ARRAY arr and crr are
     * not overlap, but the user has to ensure that the two chunks of memory will not overlap
     * after copying so that ARRAY arr will not be changed.
     */

    int8_t arr[] = {8, 7, 6, 4, 5};
    int8_t brr[] = {1, 2, 3};
    int8_t crr[] = {1, 2, 3};
    test(arr, crr);

    // compilation error, brr is an array of size 3
    /*
    memcpy(brr, arr, 4 * sizeof(int8_t));
    */

    // valgrind error, invalid write to heap
    /* 
    int8_t *crr = malloc(3 * sizeof(int8_t));
    test(arr, crr);
    */
}
