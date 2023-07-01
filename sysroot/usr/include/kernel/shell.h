#ifndef _KERNEL_SHELL_H
#define _KERNEL_SHELL_H

#include <stddef.h>
void calculator();
void shell_send_char(const char c);
void init_shell(char* prompt);
void shell_initialize(void);
void shell_run(void);
void shell_putchar(char c);
void shell_add_to_input(char clicked);
char shell_getchar();
void shell_flush_input();
void terminal_backspace(void);
void output_prompt();

#define COMMAND_BUF_SIZE 256

extern char command_buf[COMMAND_BUF_SIZE];
extern int buf_location;
extern int command_max_length;

#endif
