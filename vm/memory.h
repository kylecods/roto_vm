#define ALLOCATE(type, count)\
        (type*)reallocate(NULL, 0, sizeof(type)* (count))

#define FREE(type, pointer)\
        reallocate(pointer, sizeof(type), 0)

#define GROW_CAPACITY(cap)\
        ((cap) < 8 ? 8 : (cap) * 2)
#define GROW_ARRAY(prev, type, old_count, count)\
        (type*)reallocate(prev, sizeof(type) * (old_count),\
         sizeof(type) * (count))

#define FREE_ARRAY(type, pointer, old_count)\
        reallocate(pointer, sizeof(type) * (old_count), 0)

void *reallocate(void* prev, size_t old_size, size_t new_size);