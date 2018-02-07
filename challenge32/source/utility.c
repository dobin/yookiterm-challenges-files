#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utility.h"

size_t read_n_until(char *dst, size_t nbytes, char c)
{
	char in;
	size_t n;
	for ( n = 0; n < nbytes; ++n )
	{
		if ( read(0, &in, 1) != 1 )
		{
			puts("Error while reading... exiting now.");
			exit(1);
		}

		if ( in == c )
		{
			dst[n] = 0;
			break;
		}

		dst[n] = in;
	}

	return n;
}

size_t read_n_line(char *dst, size_t nbytes)
{
	return read_n_until(dst, nbytes, '\n');	
}

int read_int_line()
{
	char line[32];
	read_n_line(line, 32);
	
	char *endptr;
	int val = strtol(line, &endptr, 10);		

	errno = 0;
	if ( (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0) || endptr == line )
	{
		puts("Error while reading number... exiting now.");
		exit(1);
    }

	return val;
}

void safe_print(char *s)
{
	while ( *s )
	{
		if ( !isprint(*s) )
		{
			puts("[!] Cannot print unsafe character... exiting now.");
			exit(1);
		}

		putchar(*s);
		++s;
	}
}

