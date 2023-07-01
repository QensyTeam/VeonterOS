#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
size_t terminal_getcolumn(void);
size_t terminal_getRow();
void terminal_getstring(char* buffer);
void terminal_set_color(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_update(void);
void terminal_clear_line(size_t y);
void terminal_clearscreen(void);
void terminal_scroll(void);
void check(void);
void terminal_backspace(void);
char terminal_getchar(void);
void terminal_startscreen();

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void terminal_disable_cursor();
void terminal_update_cursor(int x, int y);
uint16_t terminal_get_cursor_position(void);

#endif
