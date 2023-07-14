#include <kernel/shell.h>
#include <kernel/drv/tty.h>
#include "vga.h"
#include <kernel/sys/ports.h>
#include <kernel/drv/keyboard.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <kernel/programs/test.h>
#include <kernel/programs/calculator.h>
#include <string.h>
#include <stdlib.h>

char lastChar;
char command_buf[256];
int buf_location = 0;
char* command;

void process_command(void);
void wait_for_command(void);
void output_prompt(void);

void shell_run(void) {
  while (1) {
    output_prompt();
    wait_for_command();
    process_command();
  }
}

void output_prompt() {
  printf("/>");
}

void wait_for_command() {
  while (lastChar != '\n') {
    terminal_getRow();
    if (lastChar == '\b') {
      if (buf_location > 0) {
        buf_location--;
        terminal_backspace();
      }
      
      lastChar = 0; // Обнуляем lastChar после удаления символа
    }
  }

  command = command_buf;
  lastChar = 0;
}


void reboot() {
  printf("Rebooting your PC...\n");  
  uint8_t good = 0x02;
  while (good & 0x02)
    good = inb(0x64);
  outb(0x64, 0xFE);
  outw(0x604, 0x2000);
}

void process_command() {
  if (strcmp("cls", command) == 0) {
    terminal_clearscreen();
  } else if (strcmp("help", command) == 0) {
    terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    printf("Possible Commands:  | Description:\n");
    printf("\thelp            | Show this list of commands.\n");
    printf("\tcls             | Clear the terminal screen.\n");
    printf("\tstart_screen    | Display the Start Screen.\n");
    printf("\treset_terminal  | Reset the terminal to its initial state.\n");
    printf("\treboot          | Reboot your PC.\n");
    printf("\tcalc            | Launch a simple calculator.\n");
    printf("\ttest            | Run a test program.\n");
    terminal_set_color(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
  } else if (strcmp("reset_terminal", command) == 0) {
    terminal_clearscreen();
    terminal_startscreen();
    printf("Use the 'help' command to view help.\n");
  } else if (strcmp("start_screen", command) == 0) {
    terminal_startscreen();
  } else if (strcmp("reboot", command) == 0) {
    reboot();
  } else if (strcmp("test", command) == 0) {
    test();
  } else if (strcmp("calc", command) == 0) {
  } else if (strcmp("", command) == 0) 
  {

  } 
  else {
    printf("%s", command);
    printf(": command not found\n");
    printf("\n");
  }

  memset(command_buf, 0, sizeof(command_buf));
  command = NULL;
}

void shell_putchar(char c) {
    if (c == '\n') {
        command_buf[buf_location] = '\0';
        buf_location = 0;
        terminal_putchar('\n');
    } else if (c == '\b') {
        if (buf_location > 0) {
            buf_location--;
            command_buf[buf_location] = '\0';
            terminal_backspace();
        }
    } else {
        if (buf_location < (int)(sizeof(command_buf) - 1)) {
            command_buf[buf_location] = c;
            buf_location++;
            terminal_putchar(c);
        }
    }
    lastChar = c;
}

void shell_flush_input() {
    memset(command_buf, 0, sizeof(command_buf));
    buf_location = 0;
    lastChar = 0;
}

char shell_getchar() {
    shell_flush_input();
    while (lastChar == 0) {
        terminal_getRow();
    }
    char c = lastChar;
    lastChar = 0;
    if (c == '\b') {
        // Если считали символ стирания, то удаляем последний символ из буфера ввода
        if (buf_location > 0) {
            buf_location--;
            command_buf[buf_location] = '\0';
            terminal_backspace();
        }
    } else if (c == '\b') {
        // Если считали символ стирания, добавляем символ '\b' в буфер ввода
        if (buf_location < (int)(sizeof(command_buf) - 1)) {
            command_buf[buf_location] = c;
            buf_location++;
        }
    } else {
        // Иначе добавляем символ в буфер ввода
        if (buf_location < (int)(sizeof(command_buf) - 1)) {
            command_buf[buf_location] = c;
            buf_location++;
        }
    }
    return c;
}



void shell_add_to_input(char clicked) {
    command_buf[buf_location] = clicked;
    buf_location++;
}