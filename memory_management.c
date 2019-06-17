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


// void * addBlock(Block block){  // change size of block and change address of next block
//
//
// }

// adds the required number of new pages
// void newPage(int number){
//
//   for (int i = 1; i <= number; i++){              // change if not allowed to use std=c99
//
//     sbrk(4096);
//     printf("Created new page\n");
//     // pageEnd = sbrk(0);
//   }
// }

void display(Block* block){                         // need function for displaying all blocks?

  // Block *temp;

  // temp = head->nextBlock;

  // if (block->prevBlock == NULL){
  //
  //   printf("End\n\n");
  // } else{
  //
  //   printf("There is a block before this block.\n");
  // }

  printf("Address: %d\n", (int)(long)block);
  printf("Size: %d\n", block->size);
  printf("Free: %d\n", block->isFree);
  printf("Next: %d\n", (int)(long)block->nextBlock);
  printf("Prev: %d\n\n", (int)(long)block->prevBlock);
}

void displayAll(){
  printf("Displaying all blocks\n");
  Block* block = head;

  while (block != NULL){
    display(block);
    block = (Block*)block->nextBlock;
  }
}

// allocates the specified amount of bytes in memory
void * _malloc(size_t size){

  if (size == 0){
    printf("Returning null from malloc\n");
    return NULL;
  }

  // need to check whether to add new page or not, use sbrk(0) and compare to tail address with size added on top?

  // changes what the value of prevBlock is and the values stored in the previous block
  // depending on whether a block has been created or not

  if (tail == NULL){

    // head = (Block*)(long)sbrk(4096);     // trying to create block about blocks here?
    // head->size = 0;
    // head->isFree = false;
    // head->nextBlock = NULL;
    // head->prevBlock = NULL;
    // tail = head + 1;
    // tail->size=0;
    // tail->isFree = false;
    // tail->nextBlock = NULL;
    // tail->prevBlock = NULL;

    head = (Block*)(long)sbrk(4096);   // make first page in heap since size is greater than 0
    tail = head;

    long pageEnd = (long)sbrk(0);
    printf("TAIL: %d\n", tail);
    printf("PAGE END: %d\n", pageEnd);

    if (((long)tail + size + sizeof(Block)) > pageEnd){
      printf("Not enough memory in page, allocate new page\n");
    }

    head->size = size;
    head->isFree = false;
    head->nextBlock = NULL;
    head->prevBlock = NULL;
  } else{
    long pageEnd = (long)sbrk(0);
    long memoryEnd = (long)tail + sizeof(Block) + tail->size;    // calculates the address of where the memory about to be allocated will end

    if ((memoryEnd + size + sizeof(Block)) > pageEnd){
      printf("NOT ENOUGH MEMORY IN PAGE, ALLOCATE NEW PAGE\n");
    }

    long address = (long)tail + sizeof(Block) + tail->size;
    tail->nextBlock = (struct Block*)address;
    Block* block = tail;
    tail = (Block*)address;
    printf("Tail address: %d\n", tail);
    printf("Previous block address: %d\n", block);
    // tail = (Block*)tail->nextBlock;
    tail->size = size;                        // PROBLEM HERE WHEN TRYING TO ACCESS ADDRESS BEYOND HEAP
    tail->isFree = 0;
    tail->nextBlock = NULL;
    tail->prevBlock = (struct Block*)block;
  }

  // if (tail == (head + 1)){
  //
  //   Block *block = tail + 1;
  //   block->prevBlock = NULL;
  //   block->size = size;
  //   block->isFree = false;
  //   // there is no block after the new block
  //   block->nextBlock = NULL;
  //   // head =
  //   display(block);
  //   tail = tail + 1;
  //   tail->size = block->size;
  //   tail->isFree = block->isFree;
  //   tail->nextBlock = block->nextBlock;
  //   tail->prevBlock = block->prevBlock;
  // }
  // else{
  //
  //   Block *block = (int)tail + sizeof(Block) + size;
  //   block->prevBlock = tail;
  //   block->size = size;
  //   block->isFree = false;
  //   // there is no block after the new block
  //   block->nextBlock = NULL;
  //   // tail->nextBlock = (int)tail + tail->size;
  //   display(block);
  //   tail = (int)tail + sizeof(Block) + size;
  //   tail->size = block->size;
  //   tail->isFree = block->isFree;
  //   tail->nextBlock = block->nextBlock;
  //   tail->prevBlock = block->prevBlock;
  // }

  // display(head);
  // display(tail);

  printf("Returning from malloc\n");
  // returns pointer for the address of the created block
  return tail + 1;         // adds the size of one block header to the tail address
}

void _free(void * ptr){

  if (ptr == NULL){      // check if a pointer can actually equal NULL

    printf("No size specified\n");
    return;
  }

  Block* block = ptr - sizeof(Block);
  printf("Block before being freed\n");
  display(block);
  block->isFree = 1;
  printf("Block after being freed\n");
  display(block);
  // printf("%d\n", block.isFree);

  printf("Returning from free\n");
}

void main(){
  // printf("%d\n", sbrk(0));
  // exit(0);

  // head = sbrk(0);  // returns beggining of the page
  // tail = head;
  // pageEnd = head;

  // printf("Head size: %d\nHead free: %d\nHead next: %d\nHead prev: %d\n", head->size, head->isFree, head->nextBlock, head->prevBlock);
  // printf("Tail size: %d\nTail free: %d\nTail next: %d\nTail prev: %d\n", tail->size, tail->isFree, tail->nextBlock, tail->prevBlock);

  // void * ptr = _malloc(0);
  // printf("%d\n", ptr);
  // _free(ptr);

  printf("Start of heap: %d\n", sbrk(0));
  Block *blocky = _malloc(4064);              // need to update block metadata?
  printf("Block 1 address: %d\n", (int)(long)blocky);
  Block *blocky2 = _malloc(32); // need to make sure when putting something bigger than 4064 that pages are added
  printf("Block 2 address: %d\n", (int)(long)blocky2);
  Block *blocky3 = _malloc(64);
  printf("Block 3 address: %d\n", (int)(long)blocky3);
  Block *blocky4 = _malloc(128);
  printf("Block 4 address: %d\n", (int)(long)blocky4);
  Block *blocky5 = _malloc(256);
  printf("Block 5 address: %d\n", (int)(long)blocky5);
  _free(blocky);
  _free(blocky2);
  _free(blocky3);
  // blocky->size = 50;
  // int x = _malloc(sizeof(int));
  // printf("%d\n", ptr2);
  // display(ptr2);
  // // _free(ptr2);
  // void * ptr3 = _malloc(200);
  // printf("%d\n", ptr3);
  // display(ptr3);
  displayAll();
}
