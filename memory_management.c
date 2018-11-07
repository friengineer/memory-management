// #include <stddef.h>    comment this in and remove stdlib
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "memory_management.h"

// pointers for the beginning and end of the memory and for the end of the last page
Block *head = NULL;
Block *tail = NULL;
// int pageEnd;
// bool pageCreated = false;


void * addBlock(Block block){  // change size of block and change address of next block


}

// adds the required number of new pages
void newPage(int number){

  for (int i = 1; i <= number; i++){              // change if not allowed to use std=c99

    sbrk(4096);
    printf("Created new page\n");
    // pageEnd = sbrk(0);
  }
}

void display(){

  // Block *temp;

  // temp = head->nextBlock;

  if (block->prevBlock == NULL){

    printf("End\n\n");
  } else (block->prevBlock != NULL){

    display(block->prevBlock);
  }

  printf("Size: %d\n", block->size);
  printf("Free: %d\n", block->isFree);
  printf("Next: %d\n", block->nextBlock);
  printf("Prev: %d\n\n", block->prevBlock);
}

// allocates the specified amount of bytes in memory
void * _malloc(size_t size){

  if (size == 0){

    return NULL;
  }

  // changes what the value of prevBlock is and the values stored in the previous block
  // depending on whether a block has been created or not
  if (head == NULL && tail == NULL){      // don't need head part??

    head = sbrk(4096);
    head->size = 0;
    head->isFree = false;
    head->nextBlock = NULL;
    head->prevBlock = NULL;
    tail = (int)head + sizeof(Block);
    tail->size=0;
    tail->isFree = false;
    tail->nextBlock = NULL;
    tail->prevBlock = NULL;
  }

  if (tail == ((int)head + sizeof(Block))){

    Block *block = (int)tail + sizeof(Block);
    block->prevBlock = NULL;
    block->size = size;
    block->isFree = false;
    // there is no block after the new block
    block->nextBlock = NULL;
    // head =
    display();
    tail = (int)tail + sizeof(Block);
    tail->size = block->size;
    tail->isFree = block->isFree;
    tail->nextBlock = block->nextBlock;
    tail->prevBlock = block->prevBlock;
  }
  else{

    Block *block = (int)tail + sizeof(Block) + size;
    block->prevBlock = (int)tail;
    block->size = size;
    block->isFree = false;
    // there is no block after the new block
    block->nextBlock = NULL;
    // tail->nextBlock = (int)tail + tail->size;
    display();
    tail = (int)tail + sizeof(Block) + size;
    tail->size = block->size;
    tail->isFree = block->isFree;
    tail->nextBlock = block->nextBlock;
    tail->prevBlock = block->prevBlock;
  }

  // display(head);
  display();
  // display(block);

  printf("Here\n");
  // returns pointer for the address of the created block
  return (int)tail + sizeof(Block);
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

  // head = sbrk(0);  // returns beggining of the page
  // tail = head;
  // pageEnd = head;

  // printf("Head size: %d\nHead free: %d\nHead next: %d\nHead prev: %d\n", head->size, head->isFree, head->nextBlock, head->prevBlock);
  // printf("Tail size: %d\nTail free: %d\nTail next: %d\nTail prev: %d\n", tail->size, tail->isFree, tail->nextBlock, tail->prevBlock);

  // void * ptr = _malloc(0);
  // printf("%d\n", ptr);
  // _free(ptr);

  Block *blocky = _malloc(sizeof(Block)); // 32
  Block *blocky2 = _malloc(sizeof(Block)); // 32
  display();
  display();
  blocky->size = 50;
  // int x = _malloc(sizeof(int));
  // printf("%d\n", ptr2);
  // display(ptr2);
  // // _free(ptr2);
  // void * ptr3 = _malloc(200);
  // printf("%d\n", ptr3);
  // display(ptr3);
}
