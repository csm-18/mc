#pragma once

#include <stddef.h>
#include <string.h>

void panic(char *msg);
void *alloc(size_t size);
void *resize(void *src, size_t size);
