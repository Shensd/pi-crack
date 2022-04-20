#include <stddef.h>
#include <stdint.h>

#ifdef OPTION_A

static uint32_t MMIO_BASE;
 
// The MMIO area base address, depends on board type
static inline void mmio_init(int raspi);
 
// Memory-Mapped I/O output
static inline void mmio_write(uint32_t reg, uint32_t data);
 
// Memory-Mapped I/O input
static inline uint32_t mmio_read(uint32_t reg);
 
// Loop <delay> times in a way that the compiler won't optimize away
// static inline void delay(int32_t count);

#endif // OPTION_A

void uart_init();
 
void uart_putc(unsigned char c);
 
unsigned char uart_getc();
 
void uart_puts(const char* str);