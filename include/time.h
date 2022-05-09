#ifndef TIME_H
#define TIME_H

#include <stddef.h>
#include <stdint.h>

#define PERIPHERAL_BASE 0x3F000000
#define OFFSET_SYS_TIMER 0x3000
#define OFFSET_FREE_TIMER 0x04

uint32_t get_uptime(void);
void wait_msec(uint32_t n);

#endif // !TIME_H