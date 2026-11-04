//@pub

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
//@end

#include "utils.h"

StringVector s_vec(size_t capacity) {
  StringVector sv = {0};

  if (capacity < 8) {
    capacity = 8;
  }

  sv.cap = sizeof(String) * capacity;
  sv.items = alloc(sv.cap);

  return sv;
}

void s_vec_append(StringVector *sv, char *text) {
  if (sv == NULL || text == NULL) {
    panic("error: NULL passed to s_append().");
  }

  sv->len += 1;
  if (sv->len * sizeof(String) >= sv->cap) {
    sv->cap = sv->len * 2 * sizeof(String);
    sv->items = resize(sv->items, sv->cap);
  }

  sv->items[sv->len - 1] = s(text);
}

void s_vec_free(StringVector *sv) {
  if (sv == NULL) {
    panic("error: NULL passed to s_vec_free()");
  }

  if (sv->items != NULL) {
    for (size_t i = 0; i < sv->len; i += 1) {
      s_free(&sv->items[i]);
    }
    free(sv->items);
  }
  sv->len = 0;
  sv->cap = 0;
  sv->items = NULL;
}
