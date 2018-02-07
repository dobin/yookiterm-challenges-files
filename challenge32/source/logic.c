#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"
#include "logic.h"
#include "movie.h"
#include "utility.h"

static struct Movie *find_movie(char *name);
static int movie_exists(char *name);

static LIST_HEAD(movie_list);

void print_welcome_message(char *file_name)
{
	FILE *fd;
	int c;

	if ( !(fd = fopen(file_name, "rb")) )
	{
		perror("Movie does not exist... exiting now.");
		exit(1);
	}

	while ( 1 )
	{
		c = getc(fd);
		if ( c == -1 )
			break;
		putchar(c);
	}

	fclose(fd);
}

void add_movie()
{
	char name[MAX_MOVIE_NAME_LEN];
	char description[MAX_MOVIE_DESCRIPTION_LEN];
	int year;
	int duration;

	printf("Name: ");
	read_n_line(name, MAX_MOVIE_NAME_LEN);
	if ( movie_exists(name) )
	{
		puts("Movie already exists.");
		return;
	}

	printf("Description: ");
	read_n_line(description, MAX_MOVIE_DESCRIPTION_LEN);

	printf("Year: ");
	year = read_int_line();

	printf("Duration: ");
	duration = read_int_line();

	struct Movie *m = create_movie(name, description, duration, year);	
	list_add(&m->list, &movie_list);	
}

void remove_movie()
{
	char name[MAX_MOVIE_NAME_LEN];
	printf("Name: ");
	read_n_line(name, MAX_MOVIE_NAME_LEN);
	
	struct Movie *m = find_movie(name);	
	if ( !m )
	{
		puts("Movie does not exist");
		return;
	}
	
	list_del_entry(&m->list);
	free(m);
}

void edit_movie()
{
	char name[MAX_MOVIE_NAME_LEN];
	printf("Name: ");
	read_n_line(name, MAX_MOVIE_NAME_LEN);

	struct Movie *m = find_movie(name);
	if ( !m )
	{
		puts("Movie does not exist");
		return;
	}
	
	printf("New name: ");
	read_n_line(m->name, MAX_MOVIE_DESCRIPTION_LEN);
	
	printf("New description: ");
	read_n_line(m->description, MAX_MOVIE_DESCRIPTION_LEN);

	printf("New duration: ");
	m->duration = read_int_line();

	printf("New year: ");
	m->year = read_int_line();
}

void print_movies()
{
	if ( list_empty(&movie_list) )
	{
		puts("");
		puts("No movies available");
		puts("");
		return;
	}

	puts("");
	puts("--- Available Movies ---");
	puts("");

	struct Movie *m;
	list_for_each_entry(m, &movie_list, list)
	{
		m->print(m);
		puts("");
	}

	puts("------------------------");
	puts("");
}

static struct Movie *find_movie(char *name)
{
	struct Movie *m;
	list_for_each_entry(m, &movie_list, list )
	{
		if ( strcmp(m->name, name) == 0 )
			return m;
	}

	return NULL;
}

static int movie_exists(char *name)
{
	return find_movie(name) != NULL;
}

