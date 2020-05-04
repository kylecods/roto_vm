#include "general.h"
#include "memory.h"

void *reallocate(void* prev, size_t old_size, size_t new_size){
  if(new_size == 0){
    free(prev);
    return NULL;
  }
  return realloc(prev, new_size);
}


