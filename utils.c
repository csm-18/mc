//@pub
#include <stddef.h>

void panic(char *msg);
void *alloc(size_t size);
void *resize(void *src, size_t size);
//@end

#include <stdio.h>
#include <stdlib.h>

void panic(char *msg) {
  puts(msg);
  exit(1);
}

void *alloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    panic("internal error: Memory allocation failed!");
  }

  return ptr;
}

void *resize(void *src, size_t size) {
  if (src == NULL) {
    panic("error: NULL passed to resize().");
  }

  void *dest = realloc(src, size);
  if (dest == NULL) {
    panic("internal error: Memory allocation failed!");
  }

  return dest;
}
