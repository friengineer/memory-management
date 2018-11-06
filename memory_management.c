// #include <stddef.h>    comment this in and remove stdlib
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "memory_management.h"

void * _malloc(size_t size){

  if (size == 0){

    printf("Input is 0\n");
    return NULL;
  }

  Block block;

  block.size = size;
  block.isFree = false;
  block.prevBlock = sbrk(0);
  printf("Block size: %ld\n", (long)block.size);

  int numberOfBlocks = 0;

  if ((size%4096) == 0){

    printf("Multiple of 4096\n");
    numberOfBlocks = size/4096;
  }
  else{

    printf("Not a multiple of 4096\n");
    numberOfBlocks = (size/4096) + 1;
  }

  sbrk(sizeof(Block) + (numberOfBlocks * 4096));
  block.nextBlock = sbrk(0);
  printf("%d\n", block.nextBlock);

  printf("%d\n", sbrk(0));

  exit(0);

  // return *(void*)sbrk(numberOfBlocks * 4096);
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
