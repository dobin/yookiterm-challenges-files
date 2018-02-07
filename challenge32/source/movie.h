#ifndef MOVIE_H
#define MOVIE_H

#include "list.h"

#define MAX_MOVIE_NAME_LEN 40
#define MAX_MOVIE_DESCRIPTION_LEN 512

struct Movie
{
	char description[MAX_MOVIE_DESCRIPTION_LEN];
	char name[MAX_MOVIE_NAME_LEN];
	int duration;
	int year;
	void (*print)();	
	struct list_head list;
};

struct Movie *create_movie(char *name, char *description, int duration, int year);
void init_movie(struct Movie *m, char *name, char *description, int duration, int year);

#endif
