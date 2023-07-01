#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/keyboard.h>
#include <kernel/hal.h>

void irq_disable();
void irq_enable();
void keyboard_install();

int init_hal(__attribute__((unused)) multiboot_info_t* multiboot_info) {
    irq_disable();

    idt_init(GDT_CODE_SEL_1);
    gdt_init();
    pic_init();
    pit_init();
    keyboard_install();

    irq_enable();
    return 0;
}
