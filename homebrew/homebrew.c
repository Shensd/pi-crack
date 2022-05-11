#include "words.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// #define VERBOSE

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
 
// These vars will contain the hash
uint32_t h0, h1, h2, h3;

// MD5 function from https://gist.github.com/creationix/4710780
void md5(uint8_t *initial_msg, size_t initial_len) {
 
    // Message (to prepare)
    uint8_t *msg = NULL;
    // uint8_t msg[12;
 
    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
 
    // r specifies the per-round shift amounts
 
    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
 
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
    int new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;
    
    msg = calloc(new_len + 64, 1);

    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit
 
    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer
 
    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {
 
        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);

        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
 
        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {
 
            uint32_t f, g;
 
             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;          
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;
        }
 
        // Add this chunk's hash to result so far:
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
 
    }
}

/** 
 * converts a single char to it's hex value
 * @param hexchar character to convert
 * @returns value on successful convert, -1 if invalid char
 */
char hexchar_to_int(char hexchar) {
  if(hexchar >= 'A' && hexchar <= 'F') { return hexchar - 55; }
  if(hexchar >= 'a' && hexchar <= 'f') { return hexchar - 87; }
  if(hexchar >= '0' && hexchar <= '9') { return hexchar - '0'; }
  return -1;
}

/**
 * convert a hex string to an array of bytes
 * @param hexstring pointer to string of hex characters
 * @param hexlen length of hexstring
 * @param output_buffer buffer for output bytes
 * @param max_len max length to write to output_buffer
 * @returns number of bytes converted, -1 if invalid hex string
 */
int from_hex(char* hexstring, uint32_t hexlen, uint8_t* output_buffer, uint32_t max_len) {
  uint32_t bytes_converted = 0;

  // iterate over pairs of two characters (a hex byte)
  for(unsigned int i = 0; i < hexlen / 2; i++) {
    char a = hexstring[(i*2)];
    char b = hexstring[(i*2)+1];
    
    // convert each char to it's numeric value
    char a_val = hexchar_to_int(a);
    char b_val = hexchar_to_int(b);

    // return error if either char was invalid
    if(a_val < 0 || b_val < 0) return -1; 
    
    // combine converted values into single byte
    uint8_t byte = ((a_val & 0x0F) << 4) | (b_val & 0x0F);

    // write byte to output buffer
    output_buffer[i] = byte;
    bytes_converted++;
    
    if(bytes_converted > max_len) break;
  }
  return bytes_converted;
}

/**
 * compares a target hash against the hash generated by md5()
 * @param target_hash byte array representing an md5 hash, use from_hex() to convert
 *  a raw hexstring
 * @returns 1 on equal, 0 on different
 */
int compare_hashes(uint8_t* target_hash) {
    // C moment
    return (*(uint32_t*)(target_hash+0) == h0) &&
        (*(uint32_t*)(target_hash+4) == h1) &&
        (*(uint32_t*)(target_hash+8) == h2) &&
        (*(uint32_t*)(target_hash+12) == h3);
}

/**
 * returns the number of chars encountered until a 0x00 byte is found
 * @param str pointer to char array
 * @returns number of characters in string
 */
// uint32_t strlen(char* str) {
//     uint32_t len = 0;
//     while(str[len] != 0x00) len++;
//     return len;
// }

/** 
 * crack will take a hash and attempt to crack it with the in memory wordlist,
 * if cracking multiple hashes, crack_multi() is *much* more efficient
 * @param hash an array of bytes representing an MD5 hash, use from_hex() to 
 *  convert a hexstring 
 * @returns a pointer to the cracked word on success, NULL on failure
 */
char* crack(uint8_t* hash, uint32_t* words_tested) {
    // iterate over all words
    for(unsigned int i = 0; i < NUM_WORDS; i++) {
        uint32_t len = strlen(words[i]);
        md5(words[i], len);
        // return word if hash is successfully cracked
        // if(compare_hashes(hash)) {
        if((*(uint32_t*)(hash+0) == h0) &&
            (*(uint32_t*)(hash+4) == h1) &&
            (*(uint32_t*)(hash+8) == h2) &&
            (*(uint32_t*)(hash+12) == h3)) {
            *words_tested = i;
            return words[i];
        }
    }
    // return NULL on hash not cracked
    *words_tested = NUM_WORDS;
    return NULL;
}

/**
 * crack_multi takes an array of hashes and outputs an array of results, more
 * efficient than calling crack() for each one 
 * @param hashes an array of pointers to hashes 
 * @param num_hashes the number of provided hashes
 * @param output an array of character pointers for words
 * @returns number of hashes successfully cracked
 */
uint32_t crack_multi(uint8_t* hashes, uint32_t num_hashes, char* output[], uint32_t* words_tested) {
    // default all outputs to NULL, case for if not cracked
    for(unsigned int i = 0; i < num_hashes; i++) {
        output[i] = NULL;
    }

    // keep track of the number of hashes cracked
    uint32_t cracked = 0;
    // iterate over all words
    for(unsigned int i = 0; i < NUM_WORDS; i++) {
        // printf("%d %s\r\n", i, words[i]);
        uint32_t len = strlen(words[i]);
        // hash current word
        md5(words[i], len);

        for(unsigned int j = 0; j < num_hashes; j++) {
            // comparing hashes is so cheap it would be *more* expensive to keep
            // a log of already cracked ones, so just compare each one regardless
            // of if it's already cracked
            if((*(uint32_t*)(hashes+(16*j)+0) == h0) &&
                (*(uint32_t*)(hashes+(16*j)+4) == h1) &&
                (*(uint32_t*)(hashes+(16*j)+8) == h2) &&
                (*(uint32_t*)(hashes+(16*j)+12) == h3)) {
#ifdef VERBOSE
                printf("cracked pass %d : %s\r\n", j, words[i]);
#endif // VERBOSE
                cracked++;
                output[j] = words[i];
            }
        }

        // quit if all hashes have been cracked
        if(cracked == num_hashes) {
            *words_tested = i;
            return cracked;
        };
    }

    *words_tested = NUM_WORDS;
    return cracked;
}

int main(int argc, char** argv) {

    if(argc < 2) {
        printf("usage: %s hashes.txt\n", argv[0]);
        return 0;
    }

    char * buffer = 0;
    long length;
    FILE * fd = fopen(argv[1], "r");

    if(fd) {
        fseek (fd, 0, SEEK_END);
        length = ftell(fd);
        fseek (fd, 0, SEEK_SET);
        buffer = malloc(length);
        if(buffer) {
            fread (buffer, 1, length, fd);
        }
        fclose (fd);
    }

    uint32_t hashes = (length - 1) / 32;
    uint8_t* hash_buffer = (uint8_t*) malloc(16 * hashes);
    if(hashes < 1) {
        printf("no hashes.\n");
        return 0;
    }

    if (buffer) {
        for(uint32_t i = 0; i < length; i++) {
            if(buffer[i] == '\n') {
                buffer[i] = 0x00;
            }
        }
        for(uint32_t i = 0; i < hashes; i++) {
            char* hash = buffer+(i*33);
            // printf("%s\n", hash);
            from_hex(hash, 32, hash_buffer+(i*16), 16);
        }
    }

    // special case for single hash
    if(hashes == 1) {
        uint32_t words_tested = 0;
        char* result = crack(hash_buffer, &words_tested);

        printf("%s:%s\n", buffer, result);
        return 0;
    }

    uint32_t words_tested = 0;
    char** output = (char**) malloc(sizeof(char*) * hashes);
    crack_multi(hash_buffer, hashes, output, &words_tested);

    for(uint32_t i = 0; i < hashes; i++) {
        char* c_result = output[i];
        if(c_result == NULL) {

        } else {
            printf("%s:%s\n", (char*) buffer+(i*33), c_result);
        }
    }
}