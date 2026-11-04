#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
  char *s;
  size_t len;
  size_t cap;
} String;

String s(char *text);
void s_free(String *str);
bool s_ends_with(String *str, String *suffix);

