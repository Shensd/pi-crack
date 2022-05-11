#include "memory.h"

#include "printf.h"

void* memcpy(void* dest, void* src, size_t data_length) {
    char *dest_ptr = dest;
    const char *source_ptr = src;
    while (data_length--)
        *dest_ptr++ = *source_ptr++;
    return dest;
}

uint32_t fill(uint8_t* buffer, size_t size, uint8_t value) {
    uint32_t filled = 0;
    for(size_t i = 0; i < size; i++) {
        buffer[i] = value;
        filled++;
    }
    return filled;
}

// from https://github.com/Smattr/memset since I didn't have time to write this myself lmao
void* memset(void* ptr, int value, size_t num) {
    
    uint32_t* p = (uint32_t*)ptr;

    uint32_t x = value & 0xff;

    x |= x << 8;
    x |= x << 16;

    num >>= 2;

    while (num--)
        *p++ = x;
    return ptr;
}