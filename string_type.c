//@pub
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

//@end

#include "utils.h"
#include <string.h>

String s(char *text) {
  String str = {0};

  if (text == NULL) {
    panic("error: NULL passed to s() function.");
  }

  str.len = strlen(text);
  str.cap = ((sizeof(char) * str.len) * 2);
  str.s = alloc(str.cap);
  str.s = strcpy(str.s, text);
  if (str.s == NULL) {
    panic("internal error: strcpy() failed in s() function.");
  }

  return str;
}

void s_free(String *str) {
  if (str == NULL) {
    panic("error: NULL passed to s_free().");
  }

  str->len = 0;
  str->cap = 0;
  if (str->s != NULL) {
    free(str->s);
  }
  str->s = NULL;
}

bool s_ends_with(String *str, String *suffix) {
  if (str == NULL || suffix == NULL) {
    panic("error: NULL passed to s_ends_with()");
  }

  if (suffix->len > str->len) {
    return false;
  }

  if (strcmp(str->s + (str->len - suffix->len), suffix->s) == 0) {
    return true;
  }
  return false;
}
