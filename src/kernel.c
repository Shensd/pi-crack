#include "mini_uart.h"

#include "printf.h"

#include <stddef.h>
#include <stdint.h>

#define PERIPHERAL_BASE 0x3F000000
#define OFFSET_SYS_TIMER 0x3000
#define OFFSET_FREE_TIMER 0x04

void kernel_main(void)
{
	uart_init();
    // printf("MD5-CRACK-OS STARTED.\r\n");
    printf("AAAAAAAA");

    while(1) {}

    uint32_t* system_time = PERIPHERAL_BASE + OFFSET_SYS_TIMER + OFFSET_FREE_TIMER;
    uint32_t last_time = *system_time;
    while(1) {
        if(*system_time - last_time > 1000000) {
            printf("%d tick\r\n", last_time);
            last_time = *system_time;
        }
    }
    // uart_init();
	// uart_puts("Hello, kernel World!\r\n");
 
	// while (1)
	// 	uart_putc(uart_getc());

    // uint32_t* system_time = PERIPHERAL_BASE + OFFSET_SYS_TIMER + OFFSET_FREE_TIMER;
    // // for 115200, 265-270 seems to work best
    // // for 9600, 
    // for(unsigned int i = 2500; i < 3500; i+=10) {
    //     uart_init(i);
        
    //     uint32_t last_time = *system_time;
    //     for(unsigned int j = 0; j < 5; j++) {
    //         while (*system_time - last_time < 500000) {}

    //         printf("TEST MESSAGE %d\r\n", i);
    //         last_time = *system_time;
    //     }
    // }
}
