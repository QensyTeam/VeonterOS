#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/ports.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include "../arch/i386/vga.h"
#include <kernel/keyboard.h>
#include <kernel/shell.h>
#include <kernel/multiboot.h>
#include <kernel/hal.h>
#include <kernel/programs/test.h>

void kernel_early(__attribute__((unused)) multiboot_info_t* mbd, __attribute__((unused)) unsigned int magic) {
    terminal_initialize(); 
    init_hal(mbd);
    terminal_startscreen();
    printf("Use the 'help' command to view help.\n");
    test();
    shell_run();
    
}

void kernel_main(void) {
    for (;;) ;
}
