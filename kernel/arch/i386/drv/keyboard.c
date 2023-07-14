#include <kernel/sys/isr.h>
#include <kernel/drv/tty.h>
#include <kernel/sys/ports.h>
#include <stdlib.h>
#include <stdio.h>
#include <kernel/shell.h>
#include <kernel/drv/keyboard.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

extern void keyboard_install();
extern void terminal_putchar(char c);
extern void keyboard_handler();

struct kb_state {
  int caps_lock;
  int shift_held;
};

struct kb_state state;


unsigned char kbdus[128][5] = {
    {0, 0, 0, 0, 0}, //0x00
    {27, 27, 27, 27, 27}, //0x01
    {'1', '!', '1', '!', '!'}, //0x02
    {'2', '@', '2', '@', '@'},
    {'3', '#', '3', '#', '#'},
    {'4', '$', '4', '$', '$'},
    {'5', '%', '5', '%', '%'},
    {'6', '^', '6', '^', '^'},
    {'7', '&', '7', '&', '&'},
    {'8', '*', '8', '*', '*'},  // index 9
    {'9', '(', '9', '(', '('},
    {'0', ')', '0', ')', ')'},
    {'-', '_', '-', '_', '_'},
    {'=', '+', '=', '+', '+'},
    {'\b', '\b', '\b', '\b', '\b'},  // Backspace
    {'\t', '\t', '\t', '\t', '\t'},  // Tab
    {'q', 'Q', 'Q', 'q', 'q'},
    {'w', 'W', 'W', 'w', 'w'},
    {'e', 'E', 'E', 'e', 'e'},
    {'r', 'R', 'R', 'r', 'r'},  // index 19
    {'t', 'T', 'T', 't', 't'},
    {'y', 'Y', 'Y', 'y', 'y'},
    {'u', 'U', 'U', 'u', 'u'},
    {'i', 'I', 'I', 'i', 'i'},
    {'o', 'O', 'O', 'o', 'o'},
    {'p', 'P', 'P', 'p', 'p'},
    {'[', '{', '[', '{', '{'},
    {']', '}', ']', '}', '}'},
    {'\n', '\n', '\n', '\n', '\n'},  // Enter key
    {0, 0, 0, 0, 0},              // Control key, index 29
    {'a', 'A', 'A', 'a', 'a'},
    {'s', 'S', 'S', 's', 's'},
    {'d', 'D', 'D', 'd', 'd'},
    {'f', 'F', 'F', 'f', 'f'},
    {'g', 'G', 'G', 'g', 'g'},
    {'h', 'H', 'H', 'h', 'h'},
    {'j', 'J', 'J', 'j', 'j'},
    {'k', 'K', 'K', 'k', 'k'},
    {'l', 'L', 'L', 'l', 'l'},
    {';', ':', ';', ':', ':'},  // index 39
    {'\'', '\"', '\'', '\"', '\"'},
    {'`', '~', '`', '~', '~'},
    {0, 0, 0, 0, 0},  // Left Shift
    {'\\', '|', '\\', '|', '|'},
    {'z', 'Z', 'Z', 'z', 'z'},
    {'x', 'X', 'X', 'x', 'x'},
    {'c', 'C', 'C', 'c', 'c'},
    {'v', 'V', 'V', 'v', 'v'},
    {'b', 'B', 'B', 'b', 'b'},
    {'n', 'N', 'N', 'n', 'n'},  // index 49
    {'m', 'M', 'M', 'm', 'm'},
    {',', '<', ',', '<', '<'},
    {'.', '>', '.', '>', '>'},
    {'/', '?', '/', '?', '?'},
    {0, 0, 0, 0, 0},  // Right Shift
    {'*', '*', '*', '*', '*'},
    {0, 0, 0, 0, 0},          // Alt
    {' ', ' ', ' ', ' ', ' '},  // Space
    {0, 0, 0, 0, 0},          // Caps Lock
    {0, 0, 0, 0, 0},          // F1 key, index 59
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},  // F10
    {0, 0, 0, 0, 0},  // Num Lock, index 69
    {0, 0, 0, 0, 0},  // Scroll Lock
    {0, 0, 0, 0, 0},  // Home Key
    {0, 0, 0, 0, 0},  // Up Arrow
    {0, 0, 0, 0, 0},  // Page Up
    {'-', '-', '-', '-', '-'},
    {0, 0, 0, 0, 0},  // Left Arrow
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},  // Right Arrow
    {'+', '+', '+', '+', '+'},
    {0, 0, 0, 0, 0},  // End Key, index 79
    {0, 0, 0, 0, 0},  // Down Arrow
    {0, 0, 0, 0, 0},  // Page Down
    {0, 0, 0, 0, 0},  // Insert Key
    {0, 0, 0, 0, '.'},  // Delete Key
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},  // F11 Key
    {0, 0, 0, 0, 0},  // F12 Key
    {0, 0, 0, 0, 0},  // All other keys are undefined
};

void keyboard_getstring(char* buffer, int buffer_size) {
    int i = 0;
    char c;
    while (i < buffer_size - 1) {
        c = keyboard_getchar();
        if (c == '\n') {
            buffer[i] = '\0';
            terminal_putchar('\n');
            break;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                terminal_backspace();
                buffer[i] = '\0';  // Удаляем символ из буфера
            }
        } else {
            buffer[i] = c;
            i++;
            terminal_putchar(c);
        }
    }
}




char keyboard_getchar() {
    char c;
    do {
        c = terminal_getchar();
    } while (c == 0);
    return c;
}

static unsigned char prev_scancode = 0;

void keyboard_handler(__attribute__((unused)) struct regs *r) {
    unsigned char scancode;
    int column = 0;
    char clicked = 0;
    // Read from the keyboard's data buffer
    scancode = inb(0x60);
    // If the top bit of the scancode is set, a key has just been released
    if (scancode & 0x80) {
        if (scancode >> 2 == 42 || scancode >> 2 == 54) {
            state.shift_held = 0;
        }
    } else {
        switch (scancode) {
            case 14:  // backspace
                terminal_backspace();
                break;
            case 42:  // shifts
            case 54:
                state.shift_held = 1;
                break;
            case 58:  // caps lock
                state.caps_lock = !state.caps_lock;
                break;
            default:
                if (scancode == prev_scancode && clicked != 0) {
                    break; // Игнорировать повторное срабатывание клавиши
                }
                prev_scancode = scancode; // Сохранить текущий скан-код
                column = state.shift_held * 1 + state.caps_lock * 2;
                clicked = kbdus[scancode][column];
                if (clicked != 0 && clicked != 27) {
                    shell_putchar(clicked);
                }
                break;
        }
    }
}

/* Install an irq handler for the keyboard. */
void keyboard_install() {
    install_irq_handler(1, keyboard_handler);
    state.caps_lock = 0;
    state.shift_held = 0;
    check();
    printf("Keyboard initialization completed successfully!\n");
}