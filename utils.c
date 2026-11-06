//@pub
#include "string_type.h"
#include <stddef.h>
#include <string.h>

void panic(char *msg);
void *alloc(size_t size);
void *resize(void *src, size_t size);
String read_file(String *path, String *content);
//@end

#include <stdio.h>
#include <stdlib.h>

void panic(char *msg) {
  if (strlen(msg) != 0) {
    puts(msg);
  }
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

String read_file(String *path, String *content) {
  String error = s("");
  if (path == NULL || content == NULL) {
    panic("error: NULL passed to read_file()");
  }

  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    error
  }

  return error;
}
