#ifndef CRACK_H
#define CRACK_H

#include <stdint.h>
#include <stddef.h>

#include "words.h"
#include "memory.h"

#include "printf.h"

int from_hex(char* hexstring, uint32_t hexlen, uint8_t* output_buffer, uint32_t max_len);
char* crack(uint8_t* hash);
uint32_t crack_multi(uint8_t* hashes, uint32_t num_hashes, char* output[]);

#endif // !CRACK_H