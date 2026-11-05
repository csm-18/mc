//@pub

#include "string_type.h"
#include "string_vector_type.h"
#include <stdio.h>
StringVector generate_header_file(String src_path, String header_path);

//@end

StringVector generate_header_file(String src_path, String header_path) {
  StringVector errors = s_vec(8);
  puts(header_path.s);

  return errors;
}
