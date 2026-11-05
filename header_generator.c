//@pub

#include "string_type.h"
#include <stdio.h>
void generate_header_file(String src_path, String header_path);

//@end

void generate_header_file(String src_path, String header_path) {
  puts(header_path.s);
}
