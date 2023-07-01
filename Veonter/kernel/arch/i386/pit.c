#include <kernel/pit.h>
#include <kernel/isr.h>
#include <kernel/ports.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/tty.h>

#define PIT_REG_COUNTER_0   0x40
#define PIT_REG_COMMAND     0x43
#define TIMER_FREQUENCY     100  // Частота таймера в Гц
#define SECONDS_TO_RUN      10   // Количество секунд, в течение которых будет выводиться сообщение

static unsigned int ticks = 0;
bool should_run = true;

void pit_irq_handler(__attribute__ ((unused)) struct regs* r) {
    ticks++;
    /*static uint32_t milliseconds = 0;
    static uint32_t seconds = 0;
    static uint32_t minutes = 0;

    
    milliseconds += 10; // Увеличиваем количество миллисекунд на 10 при каждом прерывании

    if (milliseconds >= 1000) {
        milliseconds = 0;
        seconds++;

        if (seconds >= 60) {
            seconds = 0;
            minutes++;
        }
    }

    printf("Time: %d:%d:%d\n", minutes, seconds, milliseconds);
    
    if (minutes >= 0 && seconds >= SECONDS_TO_RUN) {
        should_run = false;
    }*/
}

unsigned int pit_get_uptime() {
    return ticks;
}

void pit_set_phase(uint32_t hz) {
    int div = PIT_FREQ / hz;
    uint8_t ocw = PIT_WRITE_LSB_MSB | PIT_WRITE_COUNTER_0 |
                  PIT_BINARY_MODE   | PIT_SQUARE_WAVE_MODE;

    outb(PIT_REG_COMMAND, ocw);
    outb(PIT_REG_COUNTER_0, div & 0xFF);
    outb(PIT_REG_COUNTER_0, div >> 8);
}

void pit_init() {
    pit_set_phase(TIMER_FREQUENCY);
    install_irq_handler(0, pit_irq_handler);
    check();
    printf("PIT initialization completed successfully!\n");
}
