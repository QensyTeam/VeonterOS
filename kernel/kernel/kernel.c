#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <kernel/drv/tty.h>
#include <kernel/sys/gdt.h>
#include <kernel/sys/idt.h>
#include <kernel/sys/ports.h>
#include <kernel/sys/pic.h>
#include <kernel/drv/timer.h>
#include <kernel/drv/beeper.h>
#include "../arch/i386/vga.h"
#include <kernel/drv/keyboard.h>
#include <kernel/shell.h>
#include <kernel/multiboot.h>
#include <kernel/hal.h>
#include <kernel/programs/test.h>

void kernel_early(__attribute__((unused)) multiboot_info_t* mbd, __attribute__((unused)) unsigned int magic) {
    terminal_initialize(); 
    init_hal(mbd);
    terminal_startscreen();
    beeperPlay(500);
    printf("Use the 'help' command to view help.\n");
    shell_run();
    
}

void kernel_main(void) {
    for (;;) ;
}
