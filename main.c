//@pub
//@end

#include "string_vector_type.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
  bool version;
  bool help;
  bool watch;
  StringVector src_paths;
} Options;

int main(int argc, char **argv) {
  StringVector args = s_vec(8);
  s_vec_append(&args, argv[0]);
  for (size_t i = 0; i < args.len; i += 1) {
    puts(args.items[i].s);
  }
  s_vec_free(&args);
  return 0;
}
