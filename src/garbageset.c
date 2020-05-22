#include "garbageset.h"

#include <assert.h>
#include <string.h>

bool garbageset_init(garbageset_t* set, index_t capacity, size_t payloadSize) {

    assert(payloadSize > 0);
    assert(set != NULL);
    assert(capacity > 0);

    set->payload = GARBAGE_ALLOC((sizeof(index_t) + payloadSize) * capacity);

    if (set->payload == NULL) {
        return false;
    }

    set->indices = (index_t*)GARBAGE_ALLOC(sizeof(index_t) * capacity);

    if (set->indices == NULL) {
        GARBAGE_FREE(set->payload);
        return false;
    }

    set->length = 0;

    set->capacity = capacity;

    set->payloadSize = payloadSize;

    return true;

}

bool garbageset_isset(garbageset_t* set, index_t index) {

    assert(set != NULL);
    assert(index >= 0);
    assert(index < set->capacity);

    index_t garbage = *(index_t*)(((uint8_t*)set->payload) + index * (sizeof(index_t) + set->payloadSize));

    assert(garbage >= 0); // verify an unsigned type is used

    if (garbage >= set->length) {
        // garbage is really garbage
        return false; // thus the value has not been set
    }

    // garbage is a valid index to indices array
    // the index may however be invalid

    index_t trustedIndex = set->indices[garbage];

    return trustedIndex == index;

}

void* garbageset_getUnsafe(garbageset_t* set, index_t index) {

    assert(set != NULL);
    assert(index >= 0);
    assert(index < set->capacity);

    return (void*)(((uint8_t*)set->payload) + index * (sizeof(index_t) + set->payloadSize) + sizeof(index_t));

}

void* garbageset_get(garbageset_t* set, index_t index) {

    assert(set != NULL);
    assert(index >= 0);
    assert(index < set->capacity);

    index_t* garbagePointer = (index_t*)(((uint8_t*)set->payload) + index * (sizeof(index_t) + set->payloadSize));

    index_t garbage = *garbagePointer;

    assert(garbage >= 0); // verify an unsigned type is used

    if (garbage >= set->length) {
        // garbage is really garbage
        return NULL; // thus the value has not been set
    }

    // garbage is a valid index to indices array
    // the index may however be invalid

    index_t trustedIndex = set->indices[garbage];

    if (trustedIndex != index) {
        return NULL;
    }

    return garbagePointer + 1;

}

void* garbageset_writePointer(garbageset_t* set, index_t index) {

    assert(set != NULL);
    assert(index >= 0);
    assert(index < set->capacity);

    index_t* garbagePointer = (index_t*)(((uint8_t*)set->payload) + index * (sizeof(index_t) + set->payloadSize));

    index_t garbage = *garbagePointer;

    assert(garbage >= 0); // verify an unsigned type is used

    if (garbage >= set->length) {
        // garbage is really garbage
        // thus the value has not been set
        *garbagePointer = set->length;
        set->indices[set->length] = index;
        set->length++;
        return garbagePointer + 1;
    }

    // garbage is a valid index to indices array
    // the index may however be invalid

    index_t trustedIndex = set->indices[garbage];

    if (trustedIndex != index) {
        // the value at index has not been set
        *garbagePointer = set->length;
        set->indices[set->length] = index;
        set->length++;
        return garbagePointer + 1;
    }

    return garbagePointer + 1;

}

void garbageset_write(garbageset_t* set, index_t index, void* payload) {

    memcpy(
        garbageset_writePointer(set, index),
        payload,
        set->payloadSize
    );

}