#include "stdlib.h"
#include "stdio.h"

struct u_data                                          //object model: 8 bytes for name, 4 bytes for number
{
 char name[8];
 int number;
};

int main ( int argc, char* argv[] )
{
 struct u_data* objA = malloc(sizeof(struct u_data)); //create object in Heap

 objA->number = 1234;                                 //set the number of our object to a static value
 gets(objA->name);                                    //set name of our object according to user's input

 if(objA->number == 1234)                             //check if static value is intact
 {
  puts("Memory valid");
 }
 else                                                 //proceed here in case the static value gets corrupted
 {
  puts("Memory corrupted");
 }
}
