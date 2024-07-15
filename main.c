// comment this in and remove stdlib
// #include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "memory_management.h"

// points to the first allocated block of memory
Block *head = NULL;
// points to the last allocated block of memory
Block *tail = NULL;

// adds the required number of pages
void addPages(long number) {
  long i;
  number += 1;

  for (i = 0; i < number; i++) {
    sbrk(4096);
  }

  printf("%d pages added\n", i);
}

// displays information about a block at a given address
void display(Block* block) {
  printf("Address: %d\n", (int) (long) block);
  printf("Size: %d\n", block->size);
  printf("Free: %d\n", block->isFree);
  printf("Next: %d\n", (int) (long) block->nextBlock);
  printf("Prev: %d\n\n", (int) (long) block->prevBlock);
}

// displays information about all of the blocks of memory allocated in the heap
void displayAll() {
  printf("\nDisplaying all blocks\n\n");
  Block* block = head;

  while (block != NULL) {
    display(block);
    block = (Block*) block->nextBlock;
  }
}

// allocates the specified amount of bytes in memory
void * _malloc(size_t size) {
  if (size == 0) {
    return NULL;
  }

  // need to check whether to add new page or not, use sbrk(0) and compare to tail address with size added on top?

  // changes what the value of prevBlock is and the values stored in the previous block
  // depending on whether a block has been created or not
  if (tail == NULL) {

    // trying to create block about blocks here?
    // head = (Block*)(long)sbrk(4096);
    // head->size = 0;
    // head->isFree = false;
    // head->nextBlock = NULL;
    // head->prevBlock = NULL;
    // tail = head + 1;
    // tail->size=0;
    // tail->isFree = false;
    // tail->nextBlock = NULL;
    // tail->prevBlock = NULL;

    head = (Block*) (long) sbrk(4096);
    tail = head;

    // gets the address of the end of the heap
    long pageEnd = (long) sbrk(0);

    // adds the pages required to allocate the memory if there is not enough room on the heap
    if (((long) tail + size + sizeof(Block)) > pageEnd) {
      addPages((((long) tail + size + sizeof(Block)) - pageEnd) / 4096);
    }

    head->size = size;
    head->isFree = false;
    head->nextBlock = NULL;
    head->prevBlock = NULL;
  } else {
    // gets the address of the end of the heap
    long pageEnd = (long) sbrk(0);
    // calculates the address of where the memory about to be allocated will end
    long memoryEnd = (long) tail + sizeof(Block) + tail->size;

    // adds the pages required to allocate the memory if there is not enough room on the heap
    if ((memoryEnd + size + sizeof(Block)) > pageEnd) {
      addPages(((memoryEnd + size + sizeof(Block)) - pageEnd) / 4096);
    }

    // calculates the address of the start of the next memory block's header
    long address = (long) tail + sizeof(Block) + tail->size;
    tail->nextBlock = (struct Block*) address;
    Block* block = tail;
    tail = (Block*) address;
    tail->size = size;
    tail->isFree = 0;
    tail->nextBlock = NULL;
    tail->prevBlock = (struct Block*) block;
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

  // returns pointer to the start of the newly allocated memory
  return tail + 1;
}

// marks the memory at the given address as being free
void _free(void * ptr) {

  if (ptr == NULL) {
    return;
  }

  Block* block = ptr - sizeof(Block);
  block->isFree = 1;
}

void main() {
  // printf("%d\n", sbrk(0));
  // exit(0);

  // returns beginning of the page
  // head = sbrk(0);
  // tail = head;
  // pageEnd = head;

  // printf("Head size: %d\nHead free: %d\nHead next: %d\nHead prev: %d\n", head->size, head->isFree, head->nextBlock, head->prevBlock);
  // printf("Tail size: %d\nTail free: %d\nTail next: %d\nTail prev: %d\n", tail->size, tail->isFree, tail->nextBlock, tail->prevBlock);

  // void * ptr = _malloc(0);
  // printf("%d\n", ptr);
  // _free(ptr);

  printf("Start of heap: %d\n", sbrk(0));
  Block *blocky = _malloc(57344);
  printf("Block 1 address: %d\n", (int) (long) blocky);
  Block *blocky2 = _malloc(7428);
  printf("Block 2 address: %d\n", (int) (long) blocky2);
  Block *blocky3 = _malloc(64);
  printf("Block 3 address: %d\n", (int) (long) blocky3);
  Block *blocky4 = _malloc(128);
  printf("Block 4 address: %d\n", (int) (long) blocky4);
  Block *blocky5 = _malloc(256);
  printf("Block 5 address: %d\n", (int) (long) blocky5);
  
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
