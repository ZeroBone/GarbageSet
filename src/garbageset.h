#ifndef GARBAGESET_H
#define GARBAGESET_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#define GARBAGE_ALLOC malloc
#define GARBAGE_FREE free

// typedef size_t index_t;
typedef uint32_t index_t;

typedef struct {
    void* payload;
    index_t* indices; // indexes of non-garbage cells at the beginning of the memory block
    index_t length;
    index_t capacity;
    size_t payloadSize;
} garbageset_t;

bool garbageset_init(garbageset_t* set, index_t capacity, size_t payloadSize);
bool garbageset_isset(garbageset_t* set, index_t index);
void* garbageset_getUnsafe(garbageset_t* set, index_t index);
void* garbageset_get(garbageset_t* set, index_t index);
void* garbageset_writePointer(garbageset_t* set, index_t index);
void garbageset_write(garbageset_t* set, index_t index, void* payload);

#endif //GARBAGESET_H