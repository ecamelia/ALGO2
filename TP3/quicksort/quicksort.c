#include "quicksort.h"
#include "quicksort.h"
#include <string.h>
#include <stdlib.h>

static void swap(void *a, void *b, size_t size) {
    char *ptr1 = a;
    char *ptr2 = b;

    while (!(size == 0)){
      char temp = *ptr1;
      *ptr1 = *ptr2;
      *ptr2 = temp;
      ptr1++;
      ptr2++;
      size --;
    }
}


void *partition_pivot(void *base, size_t nmemb, size_t size,
                      int (*compar)(const void *, const void *)) {

    if (nmemb == 0) return nullptr;

    char *pivot = (char *)base + (nmemb - 1) * size;
    char *ptr = (char *)base;
    char *arr = (char *)base;


    while(arr < pivot){
        if (compar(arr, pivot) < 0) {
            swap(ptr, arr, size);
            ptr += size;
        }
        arr += size;
    }
    swap(ptr, pivot, size);
    return arr;
}



void quicksort(void *base, size_t nmemb, size_t size,
               int (*compar)(const void *, const void *)) {
    if (nmemb <= 1) return;

    void *pivot = partition_pivot(base, nmemb, size, compar);

    size_t left_size = (size_t)((char *)pivot - (char *)base) / size;

    quicksort(base, left_size, size, compar);
    quicksort((char *)pivot + size, nmemb - left_size - 1, size, compar);
}

