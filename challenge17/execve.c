#include <stdio.h>

void main(void) {
	execve("/bin/sh", NULL, NULL);
}
