#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

void* memcpy(void* block_a, void* block_b, size_t data_length);

void* memset(void* ptr, int value, size_t num);

#endif // !MEMORY_H