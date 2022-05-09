#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

// struct memblock {
//     uint8_t* start;
//     size_t size;
// };

// #define AVAILABLE_BLOCKS 1024
// #define HEAP_SIZE (1024 * 256)

// struct memblock allocated[AVAILABLE_BLOCKS];
// uint32_t next_block = 0;
// uint8_t pseudo_heap[HEAP_SIZE];
// uint8_t* next_heap_start = pseudo_heap;

uint32_t memcpy(void* block_a, void* block_b, size_t data_length);

uint32_t fill(uint8_t* buffer, size_t size, uint8_t value);

// void* malloc(size_t num, size_t size);

// void* calloc(size_t num, size_t size);

// void free(void* ptr);

#endif // !MEMORY_H