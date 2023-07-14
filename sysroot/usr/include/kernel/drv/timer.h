#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#define     PIT_FREQ            1193180

#define     PIT_WRITE_LSB_MSB       0x30
#define     PIT_WRITE_COUNTER_0     0x00
#define     PIT_BINARY_MODE         0x00
#define     PIT_SQUARE_WAVE_MODE    0x06

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void timer_init();
unsigned int timer_get_uptime();
size_t getTicks();
size_t getFrequency();
void sleep_ticks(uint32_t delay);
void sleep_ms(uint32_t milliseconds);

/**
 * @brief Ожидание по секундам
 *
 * @param uint32_t _d - Секунды
 */
static inline void sleep(size_t _d) {
	sleep_ms(_d * 1000);
}

#endif