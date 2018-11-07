// #include <stddef.h>    comment this in and remove stdlib
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "memory_management.h"

// pointers for the beginning and end of the memory and for the end of the last page
Block *head;
Block *tail;
int pageEnd;


void * addBlock(Block block){  // change size of block and change address of next block


}

// adds the required number of new pages
void newPage(int number){

  for (int i = 1; i <= number; i++){              // change if not allowed to use std=c99

    sbrk(4096);
    pageEnd = sbrk(0);
  }
}

// allocates the specified amount of bytes in memory
void * _malloc(size_t size){

  if (size == 0){

    printf("Input is 0\n");
    return NULL;
  }
  printf("%d\n", tail->size);
  int newMemoryEnd = tail + tail->size + size + sizeof(Block);       // adding tail->size to anything is causing problem
  printf("%d\n", newMemoryEnd);

  // checks if there is room for the new block in the current page and if not, asks for
  // the required number of new pages
  if (newMemoryEnd > pageEnd){

    int bytesRequired = newMemoryEnd - (int)pageEnd;

    if ((bytesRequired%4096) == 0){

      printf("Multiple of 4096\n");
      newPage((bytesRequired/4096));
    }
    else{

      printf("Not a multiple of 4096\n");
      newPage((bytesRequired/4096) + 1);
    }
  }

  Block block;

  // block size include data and the block header
  block.size = size + sizeof(Block);
  block.isFree = false;
  // there is no block after the new block
  block.nextBlock = NULL;

  // changes what the value of prevBlock is and the values stored in the previous block
  // depending on whether a block has been created or not
  if (tail == head){
    block.prevBlock = head;
  }
  else{
    block.prevBlock = tail;
    tail->nextBlock = tail + tail->size;
    tail = tail->nextBlock;
  }

  printf("Block size: %ld\n", (long)block.size);

  printf("%d\n", block.nextBlock);

  printf("%d\n", sbrk(0));

  printf("Here\n");
  // returns pointer for the address of the created block
  return tail;
}

void _free(void * ptr){

  if (ptr == NULL){      // check if a pointer can actually equal NULL

    printf("Special here\n");
    return;
  }

  printf("Here\n");

  // Block block = *ptr;
  // printf("%d\n", block.isFree);
}

void main(){

  head = sbrk(4096);  // returns beggining of the page
  tail = head;
  pageEnd = head;
  printf("%d\n", head);
  printf("%d\n", pageEnd);

  void * ptr = _malloc(0);
  printf("%d\n", ptr);
  // _free(ptr);
  void * ptr2 = _malloc(100);
  printf("%d\n", ptr2);
  // _free(ptr2);
}
