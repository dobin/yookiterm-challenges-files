#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Set memory[loc] = a
void bof(long a, long loc) {
        long *ptr = (void*) (long) loc;
        *ptr = a;
}

int main(int argc, char **argv) {
  system(""); // load system system-call
  if (argc != 3) {
    printf("Usage: %s <value-to-write> <destination-memory-address>\n", argv[0]);
    printf("       %s 0x1337 0x08080808\n", argv[0]);
    exit(1);
  }

  printf("Start\n"); // load puts system call
  bof( (long)strtol(argv[1], NULL, 16), (long)strtol(argv[2], NULL, 16));

  // System call we overwrite with system()
  printf("id \n");
}