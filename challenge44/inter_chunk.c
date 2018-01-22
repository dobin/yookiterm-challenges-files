#include "stdlib.h"
#include "stdio.h"

int main ( int argc, char* argv[] )
{
 char *some_string = malloc(8);  //create some_string "object" in Heap
 int *some_number = malloc(4);   //create some_number "object" in Heap

 *some_number = 1234;            //assign some_number a static value
 gets(some_string);              //ask user for input for some_string

 if(*some_number == 1234)        //check if static value (of some_number) is in tact
 {
 puts("Memory valid");
 }
 else                            //proceed here in case the static some_number gets corrupted
 {
 puts("Memory corrupted");
 }
}
