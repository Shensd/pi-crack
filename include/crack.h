#ifndef CRACK_H
#define CRACK_H

#include <stdint.h>
#include <stddef.h>

#include "words.h"
#include "memory.h"

#include "printf.h"

int from_hex(char* hexstring, uint32_t hexlen, uint8_t* output_buffer, uint32_t max_len);
char* crack(uint8_t* hash);

#endif // !CRACK_H