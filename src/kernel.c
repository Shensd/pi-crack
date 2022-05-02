#include "mini_uart.h"

#include "printf.h"

#include <stddef.h>
#include <stdint.h>

#define PERIPHERAL_BASE 0x3F000000
#define OFFSET_SYS_TIMER 0x3000
#define OFFSET_FREE_TIMER 0x04

/**
 * returns the system uptime in microseconds
 */
uint32_t get_uptime(void) {
    uint32_t* system_time = PERIPHERAL_BASE + OFFSET_SYS_TIMER + OFFSET_FREE_TIMER;

    return *system_time;
}

void kernel_main(void)
{
	uart_init();
    printf("MD5-CRACK-OS STARTED.\r\n");

    uint32_t last_time = get_uptime();
    while(1) {
        uint32_t current_time = get_uptime();
        if(current_time - last_time > 1000000) {
            printf("%d tick\r\n", last_time);
            last_time = current_time;
        }
    }
}
