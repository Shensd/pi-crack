#include <stddef.h>
#include <stdint.h>

void uart_init();
 
void uart_putc(unsigned char c);
 
unsigned char uart_getc();
 
void uart_puts(const char* str);