#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"
#include "logic.h"
#include "movie.h"
#include "utility.h"

int main()
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	print_welcome_message("welcome-message.txt");
	
	while ( 1 )
	{
		puts("1) Add Movie");
		puts("2) Remove Movie");
		puts("3) Edit Movie");
		puts("4) Print Movies");
		puts("5) Exit");
		printf("> ");

		int option = read_int_line();
		switch ( option )
		{
		case 1:
			add_movie();
			break;
		case 2:
			remove_movie();
			break;
		case 3:
			edit_movie();
			break;
		case 4:
			print_movies();
			break;
		case 5:
			puts("Bye Bye");
			exit(1);	
		default:
			printf("Invalid option!\n\n");
			break;
		}
	}	
}


