#ifndef STM32F10X_MAKEFILE_FREERTOS_UART_LOG_H
#define STM32F10X_MAKEFILE_FREERTOS_UART_LOG_H

#include <stdarg.h>

void uart_log_init(void);

void debug(const char *format, ...);
void printchar(char **str, unsigned int c);
#endif //STM32F10X_MAKEFILE_FREERTOS_UART_LOG_H
