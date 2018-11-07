#include <sys/types.h>

typedef struct Blocks{                    // need struct for pages??

  size_t size;
  bool isFree;
  struct Block* nextBlock;
  struct Block* prevBlock;
} Block;

void * _malloc(size_t size);

void _free(void * ptr);
