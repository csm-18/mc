// Hello Module

//@pub

const char *NAME = "//@end";
const char my_char = 's';
// This function whishes the user
void hello(char *name);
/*Yep!*/
//@end

#include <stdio.h>

void hello(char *name) { printf("Hello %s!", name); }