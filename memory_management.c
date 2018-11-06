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

  block.size = size;                     //problem here with segmentation fault when using Block* block
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
  block.nextBlock = sbrk(0) + block.size;
  printf("%d\n", block.nextBlock);

  printf("%d\n", sbrk(0));

  printf("Here\n");
  return sbrk(0);
}

void _free(void * ptr){

  if (ptr == NULL){      // check if a pointer can actually equal NULL

    printf("Special here\n");
    return;
  }

  printf("Here\n");

  Block block = *ptr;
  printf("%d\n", block.isFree);
}

void main(){

  void * ptr = _malloc(0);
  printf("%d\n", ptr);
  _free(ptr);
  void * ptr2 = _malloc(8192);
  printf("%d\n", ptr2);
  _free(ptr2);
}
