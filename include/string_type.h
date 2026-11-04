#pragma once

#include <stddef.h>
#include <stdlib.h>

typedef struct {
  char *s;
  size_t len;
  size_t cap;
} String;

String s(char *text);
void s_free(String *str);

