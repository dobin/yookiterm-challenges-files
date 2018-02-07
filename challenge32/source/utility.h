#ifndef UTILITY_H
#define UTILITY_H

#include <stddef.h>

size_t read_n_until(char *dst, size_t nbytes, char c);
size_t read_n_line(char *dst, size_t nbytes);

int read_int_line();

void safe_print(char *s);

#endif
