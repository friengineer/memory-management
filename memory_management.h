#include <sys/types.h>

// need struct for pages?
typedef struct Blocks {
  size_t size;
  bool isFree;
  struct Block* nextBlock;
  struct Block* prevBlock;
} Block;

void * _malloc(size_t size);
void _free(void * ptr);
