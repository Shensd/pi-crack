#include "mini_uart.h"
#include "printf.h"
#include "time.h"

#include "crack.h"

#include <stddef.h>
#include <stdint.h>

extern unsigned char bss_end;

void kernel_main(void)
{
	uart_init();

    printf("MD5-CRACK-OS STARTED.\r\n");

    // char to_crack[] = "65fbef05e01fac390cb3fa073fb3e8cf"; // anthony
    char to_crack[] = "67355e810914ddce4333bc56816705a8"; // alexandra12
    
    uint8_t buffer[16];
    from_hex(to_crack, sizeof(to_crack), buffer, 16);

    
    #define NUM_HASHES 5
    char* hashstrings[NUM_HASHES] = {
        "67355e810914ddce4333bc56816705a8", // alexandra12
        "65fbef05e01fac390cb3fa073fb3e8cf", // anthony
        "5f4dcc3b5aa765d61d8327deb882cf99", // password
        "ea5dc6553f4d915abc7579aad7d027d9", // bestpass
        "2ab96390c7dbe3439de74d0c9b0b1767", // hunter2
    };
    uint8_t hashes[NUM_HASHES][16];
    char* output[NUM_HASHES];

    for(unsigned int i = 0; i < NUM_HASHES; i++) {
        from_hex(hashstrings[i], 32, hashes[i], 16);
    }

    uint32_t last_time = get_uptime();

    // char* result = crack(buffer);
    uint32_t result = crack_multi(hashes[0], NUM_HASHES, output);

    uint32_t delta = get_uptime() - last_time;

    /*
    if(result) {
        printf("%s:%s\n", to_crack, result);
        printf("cracked in %d microseconds\t\n", delta);
    } else {
        // printf("%s:\n", to_crack);
        printf("unable to crack, exhausted in %d microseconds\t\n", delta);
    }
    */
    
    if(result > 0) {
        for(unsigned int i = 0; i < NUM_HASHES; i++) {
            if(output[i] == NULL) {
                printf("x %s:\n", hashstrings[i]);
            } else {
                printf("o %s:%s\n", hashstrings[i], output[i]);
            }
        }
        printf("cracked in %d hashes in %d microseconds\t\n", result, delta);
    } else {
        printf("unable to crack, exhausted in %d microseconds\t\n", delta);
    }
    

    while(1) {}
}
