#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

void keyboard_install();
char keyboard_getchar();
void keyboard_getstring(char* buffer, int buffer_size);

#endif
