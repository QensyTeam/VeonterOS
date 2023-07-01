#include <stddef.h>
#include <stdlib.h>

// Структура блока памяти
typedef struct {
  size_t size; // Размер блока памяти
  int free;    // Флаг, свободен ли блок памяти
} block_t;

// Указатель на начало области памяти
void* base = NULL;

// Инициализация области памяти
void init_memory(size_t size) {
  base = malloc(size);
  block_t* block = (block_t*)base;
  block->size = size - sizeof(block_t);
  block->free = 1;
}

// Функция malloc
void* malloc(size_t size) {
  if (base == NULL) {
    // Инициализируем память, если она еще не была инициализирована
    init_memory(size);
  }

  block_t* current = (block_t*)base;

  while (1) {
    if (current->size >= size && current->free) {
      if (current->size > size + sizeof(block_t)) {
        // Если блок памяти слишком большой, разбиваем его на два блока
        block_t* new_block = (block_t*)((char*)current + sizeof(block_t) + size);
        new_block->size = current->size - size - sizeof(block_t);
        new_block->free = 1;

        current->size = size;
        current->free = 0;

        return (void*)((char*)current + sizeof(block_t));
      } else {
        // Иначе, отмечаем блок памяти как занятый и возвращаем его адрес
        current->free = 0;
        return (void*)((char*)current + sizeof(block_t));
      }
    }

    if (current->size == 0) {
      // Достигли конца области памяти и не нашли подходящего блока
      return NULL;
    }

    // Переходим к следующему блоку памяти
    current = (block_t*)((char*)current + sizeof(block_t) + current->size);
  }
}

// Функция free
void free(void* ptr) {
  if (ptr == NULL) {
    return;
  }

  block_t* block = (block_t*)((char*)ptr - sizeof(block_t));
  block->free = 1;
}
