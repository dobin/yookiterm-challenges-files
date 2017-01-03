#ifndef _NOTEHEAP_MODEL
#define _NOTEHEAP_MODEL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIST_SIZE 128

typedef struct {
	char *body;
	int priority;
	int id;
} Todo;

typedef struct {
	char *name;
	void (*cleanupFunction)();
	int id;
} Alarm;


struct Global {
	int id;
	int alarmId;

	Todo *todos[2][LIST_SIZE];
	Alarm *alarms[LIST_SIZE];
};


/* Functions */
void modelInit();

void alarmAdd(char *alarmName);
void alarmList();
void alarmDel(int alarmIndex);
int alarmGetFreeEntryIndex();

void todoAdd(char *listName, char *todoPrio, char *todoBody);
void todoEdit(char *listName, char *listEntryIndex, char *todoPrio, char *todoBody);
void todoPrint(Todo *todo);

void listView(char *listName);
void listDel(char *listName, char *listEntry);
void listAdd(char *dstListName, char *srcListName, char *srcListEntryIndex);

int listNameToIndex(char *listName);
int listGetFreeEntryIndex(int listIndex);

#endif
