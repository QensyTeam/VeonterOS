#include <kernel/drv/beeper.h>
#include <kernel/sys/ports.h>

// Port of beeper from SayoriOS - original code: pimnik98

void beeperPlay(uint32_t freq) {
    uint32_t divisor = 1000000 / freq;
    uint8_t tmp;
    
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t)(divisor) );
    outb(0x42, (uint8_t)(divisor >> 8));
    
    tmp = inb(0x61);
    
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}

void beeperSilent() {
    uint8_t tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}
