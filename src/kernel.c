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
    char to_crack[] = "67355e810914ddce4333bc56816705a8";
    uint8_t buffer[16];
    from_hex(to_crack, sizeof(to_crack), buffer, 16);

    // printf("Attempting to crack %s...\r\n", to_crack);

    uint32_t last_time = get_uptime();

    char* result = crack(buffer);

    uint32_t delta = get_uptime() - last_time;

    if(result) {
        printf("%s:%s\n", to_crack, result);
        printf("cracked in %d microseconds\t\n", delta);
    } else {
        // printf("%s:\n", to_crack);
        printf("unable to crack, exhausted in %d microseconds\t\n", delta);
    }

    while(1) {}
    // while(1) {
    //     uint32_t current_time = get_uptime();
    //     if(current_time - last_time > 1000000) {
    //         printf("%d tick\r\n", last_time);
    //         last_time = current_time;
    //     }
    // }
}
