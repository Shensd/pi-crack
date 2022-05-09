#include "time.h"

uint32_t get_uptime(void) {
    uint32_t* system_time = PERIPHERAL_BASE + OFFSET_SYS_TIMER + OFFSET_FREE_TIMER;

    return *system_time;
}

void wait_msec(uint32_t n) {
    uint32_t current_time = get_uptime();

    while((get_uptime() - current_time) / 1000 < n) {}
}