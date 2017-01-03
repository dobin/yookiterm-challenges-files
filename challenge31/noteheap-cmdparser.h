#ifndef _NOTEHEAP_CMDPARSER
#define _NOTEHEAP_CMDPARSER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Public */
void cmdParser(char *input);

/* Private */
void cmdTodoAddParser(char *input);
void cmdTodoEditParser(char *input);
void cmdListDelParser(char *input);

void cmdTodoParser(char *input);
void cmdListViewParser(char *input);
void cmdListAddParser(char *input);
void cmdListParser(char *input);
void cmdAlarmAddParser(char *input);
void cmdAlarmListParser(char *input);
void cmdAlarmParser(char *input);

void cmdHelpTodo();
void cmdHelpList();
void cmdHelpAlarm();
void cmdHelp();

static char *delim = " ";

#endif
