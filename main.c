//@pub
//@end

#include "string_type.h"
#include "string_vector_type.h"
#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool version;
  bool help;
  bool watch;
  StringVector src_paths;
  StringVector errors;
} Options;

const char *VERSION;
const char *HELP;

int main(int argc, char **argv) {
  Options options = {.version = false,
                     .help = false,
                     .watch = false,
                     .src_paths = s_vec(argc),
                     .errors = s_vec(argc)};
  String dot_c_suffix = s(".c");

  if (argc == 1) {
    options.help = true;
  }

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

        char error[500];
        sprintf(error, "error: Path must be a valid .c source file.\n -> '%s'",
                arg.s);
        s_vec_append(&options.errors, error);
      } else {

        s_vec_append(&options.src_paths, arg.s);
      }
    }
  }

  if (options.errors.len != 0) {
    for (size_t i = 0; i < options.errors.len; i += 1) {
      puts(options.errors.items[i].s);
    }
    panic("");
  }

  if (options.watch &&
      (options.help || options.version || options.src_paths.len != 0)) {
    panic("error: Cannot use -w (watch) flag with other options.");
  }

  if (options.version && options.help) {
    puts(VERSION);
    puts(HELP);
  } else if (options.version) {
    puts(VERSION);
  } else if (options.help) {
    puts(VERSION);
    puts(HELP);
  } else if (options.watch) {
    puts("watching!");
  } else {
    puts("yo!");
  }

  s_vec_free(&options.src_paths);
  s_vec_free(&options.errors);
  return 0;
}

const char *VERSION = "mc 1.0.0";
const char *HELP =
    "A pre-preprocessor for C for header files generation\n"
    "using comment macro syntax.\n"
    "\n"
    "Commands:\n"
    "  mc <no args>       -> Print mc version and help.\n"
    "  mc -v              -> Print mc version.\n"
    "  mc -h              -> Print mc help.\n"
    "  mc -w              -> Watch current directory for file changes and "
    "update the header files.\n"
    "  mc main.c hello.c  -> Generate header files for provided .c files.\n"
    "\n"
    "Author: csm\n"
    "License: MIT\n";
