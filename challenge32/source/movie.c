#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"

static void print_movie(struct Movie *);
static void print_movie_special_offser(struct Movie *);

struct Movie *create_movie(char *name, char *description, int duration, int year)
{
	struct Movie *m = malloc(sizeof(struct Movie));
	init_movie(m, name, description, duration, year);
	return m;
}

void init_movie(struct Movie *m, char *name, char *description, int duration, int year)
{		
	strncpy(m->name, name, MAX_MOVIE_NAME_LEN);
	strncpy(m->description, description, MAX_MOVIE_DESCRIPTION_LEN);
	m->duration = duration;
	m->year = year;
	m->print = print_movie;
}

static void print_movie(struct Movie *m)
{
	printf("Name: %s\n", m->name);
	printf("Description: %s\n", m->description);
	printf("Publishing year: %d\n", m->year);
	printf("Duration: %d minutes\n", m->duration);
}

static void print_movie_special_offser(struct Movie *m)
{
	puts("This operation is not yet supported... exiting now");
	exit(1);
}

