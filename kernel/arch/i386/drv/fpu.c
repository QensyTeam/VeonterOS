/**
 * @file fpu.c
 * @author Drew >_ (pikachu_andrey@vk.com)
 * @brief FPU
 * @version 0.3.3
 * @date 2023-12-19
 * @copyright Copyright SayoriOS Team (c) 2022-2023
 */
#include <kernel/drv/fpu.h>
#include <kernel/sys/ports.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

bool fpu_initialized = false;

bool fpu_isInitialized() {
	return fpu_initialized;
}

void fpu_fldcw(const uint16_t cw) {
    asm volatile("fldcw %0" : : "m"(cw));
}

void fpu_init() {
    uint32_t cr4 = 0;

    asm volatile ("mov %%cr4, %0":"=r"(cr4));
    cr4 |= 0x200;
    asm volatile("mov %0, %%cr4"::"r"(cr4));

    fpu_fldcw(0x37F);

	fpu_initialized = true;

}
