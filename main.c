#include <stdio.h>

#include <assert.h>
#include "src/garbageset.h"

#define TEST_CAPACITY 1793

int main() {

    int testPayload;

    garbageset_t set;
    garbageset_init(&set, TEST_CAPACITY, sizeof(int));

    for (int i = 0; i < TEST_CAPACITY; i++) {
        assert(garbageset_get(&set, i) == NULL);
    }

    for (int i = 0; i < TEST_CAPACITY; i += 2) {
        testPayload = i;
        garbageset_write(&set, i, &testPayload);
    }

    for (int i = 0; i < TEST_CAPACITY; i++) {
        if (i % 2 == 0) {
            assert(garbageset_isset(&set, i));
            assert(*(int*)garbageset_get(&set, i) == i);
            assert(*(int*)garbageset_getUnsafe(&set, i) == i);
        }
        else {
            assert(!garbageset_isset(&set, i));
            assert(garbageset_get(&set, i) == NULL);
        }
    }

    printf("Hello, World/!\n");

    return 0;

}