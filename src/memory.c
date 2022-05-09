#include "memory.h"

uint32_t memcpy(void* block_a, void* block_b, size_t data_length) {
    uint32_t copied = 0;
    for(size_t i = 0; i < data_length; i++) {
        uint8_t* a = block_a + i;
        uint8_t* b = block_b + i;
        *a = *b;
        copied++;
    }

    return copied;
}

uint32_t fill(uint8_t* buffer, size_t size, uint8_t value) {
    uint32_t filled = 0;
    for(size_t i = 0; i < size; i++) {
        buffer[i] = value;
        filled++;
    }
    return filled;
}

// void* malloc(size_t num, size_t size) {
//     void* start = (void*) next_heap_start;

//     allocated[next_block].start = next_heap_start;
//     allocated[next_block].size = num * size;

//     next_head_start += num * size;
//     next_block++;

//     return start;
// }

// void* calloc(size_t num, size_t size) {
//     void* ptr = malloc(num, size);
//     for(size_t i = 0; i < num * size; i++) {
//         uint8_t c = (uint8_t) *(ptr+i);
//         c = 0;
//     }
//     return ptr;
// }

// void free(void* ptr) {
//     for(unsigned int i = 0; i < AVAILABLE_BLOCKS; i++) {
//         if((uint32_t) allocated[i].start == (uint32_t) ptr) {
//             allocated[i].start = 0;
//             allocated[i].size = 0;
//         }
//     }
// }