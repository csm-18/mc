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
} Options;

int main(int argc, char **argv) {
  String str = s("buddy!");
  String suffix = s(argv[1]);
  if (s_ends_with(&str, &suffix)) {
    puts("true!");
  }
  // Options options = {.version = false,
  //                    .help = false,
  //                    .watch = false,
  //                    .src_paths = s_vec(argc)};

  // for (int i = 1; i < argc; i += 1) {
  //   if (strcmp(argv[i], "-v") == 0) {
  //     options.version = true;
  //   } else if (strcmp(argv[i], "-h") == 0) {
  //     options.help = true;
  //   } else if (strcmp(argv[i], "-w") == 0) {
  //     options.watch = true;
  //   } else {
  //     char *arg = argv[i];
  //     int arg_len = strlen(arg);
  //   }
  // }

  return 0;
}
