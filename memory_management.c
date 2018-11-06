#include <stddef.h>
#include <stdio.h>
#include "memory_management.h"

void * _malloc(size_t size){

  if (size == 0){

    printf("Input is 0\n");
    return NULL;
  }

  if ((size%4096) == 0){

    printf("Multiple of 4096\n");
    return sbrk(size/4096);                         // sbrk will only allocate 1 byte here, need to think of another way
  }
  else{

    printf("Not a multiple of 4096\n");
    return sbrk((size/4096) + 1);
  }
}

void _free(void * ptr){

  if (ptr == NULL){      // check if a pointer can actually equal NULL

    return;
  }
}

void main(){

  _malloc(0);
  _malloc(8192);
}
