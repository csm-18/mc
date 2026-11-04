#pragma once

#include "string_type.h"
#include <stddef.h>
#include <stdlib.h>
typedef struct {
  String *items;
  size_t len;
  size_t cap;
} StringVector;

StringVector s_vec(size_t capacity);
void s_vec_append(StringVector *sv, char *text);
void s_vec_free(StringVector *sv);
