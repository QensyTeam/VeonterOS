#include <kernel/drv/timer.h>
#include <kernel/sys/isr.h>
#include <kernel/sys/ports.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/drv/tty.h>
#include <stddef.h>

#define PIT_REG_COUNTER_0   0x40
#define PIT_REG_COMMAND     0x43
#define TIMER_FREQUENCY     100  // Частота таймера в Гц
#define SECONDS_TO_RUN      10   // Количество секунд, в течение которых будет выводиться сообщение

static unsigned int ticks = 0;
bool should_run = true;
size_t frequency = 0;

void microseconds_delay(size_t microseconds) {
    for (size_t i = 0; i < microseconds; ++i)
        inb(0x80);
}

void timer_irq_handler(__attribute__ ((unused)) struct regs* r) {
    ticks++;
}

unsigned int timer_get_uptime() {
    return ticks;
}

/**
 * @brief Получить частоту таймера
 *
 * @return uint32_t - Частота таймера
 */
size_t getFrequency(){
	return frequency;
}

/**
 * @brief Ожидание по тикам
 *
 * @param uint32_t delay - Тики
 */
void sleep_ticks(uint32_t delay){
	size_t current_ticks = timer_get_uptime();
	while (1){
		if (current_ticks + delay < timer_get_uptime()){
			break;
		}
	}
}

/**
 * @brief Ожидание по милисекундам
 *
 * @param uint32_t milliseconds - Милисекунды
 */
void sleep_ms(uint32_t milliseconds) {
	uint32_t needticks = milliseconds * frequency;
	sleep_ticks(needticks/1000);

	// (milliseconds * frequency + 500) / 1000
}

void timer_set_phase(uint32_t hz) {
    int div = PIT_FREQ / hz;
    uint8_t ocw = PIT_WRITE_LSB_MSB | PIT_WRITE_COUNTER_0 |
                  PIT_BINARY_MODE   | PIT_SQUARE_WAVE_MODE;

    outb(PIT_REG_COMMAND, ocw);
    outb(PIT_REG_COUNTER_0, div & 0xFF);
    outb(PIT_REG_COUNTER_0, div >> 8);
}

void timer_init() {
    timer_set_phase(TIMER_FREQUENCY);
    install_irq_handler(0, timer_irq_handler);
    check();
    printf("Timer initialization completed successfully!\n");
}
