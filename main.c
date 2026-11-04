//@pub
//@end

#include "string_type.h"
#include "string_vector_type.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  bool version;
  bool help;
  bool watch;
  StringVector src_paths;
  StringVector errors;
} Options;

int main(int argc, char **argv) {
  Options options = {.version = false,
                     .help = false,
                     .watch = false,
                     .src_paths = s_vec(argc),
                     .errors = s_vec(argc)};
  String dot_c_suffix = s(".c");

  for (int i = 1; i < argc; i += 1) {
    if (strcmp(argv[i], "-v") == 0) {
      options.version = true;
    } else if (strcmp(argv[i], "-h") == 0) {
      options.help = true;
    } else if (strcmp(argv[i], "-w") == 0) {
      options.watch = true;
    } else {
      String arg = s(argv[i]);
      if (!s_ends_with(&arg, &dot_c_suffix)) {
        s_vec_append(&options.errors, "Unknown option!");
        break;
      }

      s_vec_append(&options.src_paths, arg.s);
    }
  }

  return 0;
}
