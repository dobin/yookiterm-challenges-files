#include "noteheap-model.h"
#include "noteheap-cmdparser.h"

void cmdTodoAddParser(char *input) {
	char *listName;
	char *todoBody;
	char *todoPrio;

	listName = strtok(NULL, delim);
	if (listName == NULL) {
		cmdHelpTodo();
		return;
	}

	todoPrio = strtok(NULL, delim);
	if (todoPrio == NULL) {
		cmdHelpTodo();
		return;
	}

	todoBody = strtok(NULL, "");
	if (todoBody == NULL) {
		cmdHelpTodo();
		return;
	}

	todoAdd(listName, todoPrio, todoBody);
}


void cmdTodoEditParser(char *input) {
	char *todoBody;
	char *todoPrio;
	char *list;

	char *listName;
	char *listEntryIndex;

	list = strtok(NULL, delim);
	if (list == NULL) {
		cmdHelpTodo();
		return;
	}

	todoPrio = strtok(NULL, delim);
	if (todoPrio == NULL) {
		cmdHelpTodo();
		return;
	}

	todoBody = strtok(NULL, "");
	if (todoBody == NULL) {
		cmdHelpTodo();
		return;
	}

	listName = strtok(list, ":");
	listEntryIndex = strtok(NULL, ":");
	if (listName == NULL || listEntryIndex == NULL) {
		cmdHelpTodo();
		return;
	}

	todoEdit(listName, listEntryIndex, todoPrio, todoBody);
}


void cmdListDelParser(char *input) {
	char *list;
	char *listName;
	char *listEntry;

	list = strtok(NULL, delim);
	if (list == NULL) {
		cmdHelpList();
		return;
	}

	listName = strtok(list, ":");
	if (listName == NULL) {
		cmdHelpList();
		return;
	}

	listEntry = strtok(NULL, ":");
	if (listEntry == NULL) {
		cmdHelpList();
		return;
	}
	listDel(listName, listEntry);
}


void cmdTodoParser(char *input) {
	char *cmd2;

	cmd2 = strtok(NULL, delim);
	if (cmd2 == NULL) {
		return;
	}

	if (strcmp(cmd2, "add") == 0) {
		cmdTodoAddParser(input);
		return;
	}
	if (strcmp(cmd2, "edit") == 0) {
		cmdTodoEditParser(input);
		return;
	}

	printf("Unknown command: %s\n", cmd2);
	cmdHelpTodo();
}


void cmdListViewParser(char *input) {
	char *listName;

	listName = strtok(NULL, delim);
	if (listName == NULL) {
		cmdHelpList();
		return;
	}

	listView(listName);
}


void cmdListAddParser(char *input) {
	char *dstListName;
	char *srcList;
	char *srcListName;
	char *srcListEntryIndex;

	dstListName = strtok(NULL, delim);
	if (dstListName == NULL) {
		cmdHelpList();
		return;
	}

	srcList = strtok(NULL, delim);
	if (srcList == NULL) {
		cmdHelpList();
		return;
	}

	srcListName = strtok(srcList, ":");
	if (srcListName == NULL) {
		cmdHelpList();
		return;
	}

	srcListEntryIndex = strtok(NULL, ":");
	if (srcListEntryIndex == NULL) {
		cmdHelpList();
		return;
	}

	listAdd(dstListName, srcListName, srcListEntryIndex);
}


void cmdListParser(char *input) {
	char *cmd2;

	cmd2 = strtok(NULL, delim);
	if (cmd2 == NULL) {
		cmdHelpList();
		return;
	}

	if (strcmp(cmd2, "view") == 0) {
		cmdListViewParser(input);
		return;
	}
	if (strcmp(cmd2, "del") == 0) {
		cmdListDelParser(input);
		return;
	}
	if (strcmp(cmd2, "add") == 0) {
		cmdListAddParser(input);
		return;
	}

	printf("Unknown command: %s\n", cmd2);
	cmdHelpList();
}


void cmdAlarmAddParser(char *input) {
	char *alarmName;

	alarmName = strtok(NULL, delim);
	if (alarmName == NULL) {
		cmdHelpAlarm();
		return;
	}

	alarmAdd(alarmName);
}


void cmdAlarmListParser(char *input) {
	alarmList();
}

void cmdAlarmDelParser(char *input) {
	char *alarmIndex;
	int idx;

	alarmIndex = strtok(NULL, delim);
	if (alarmIndex == NULL) {
		cmdHelpAlarm();
		return;
	}

	idx = atoi(alarmIndex);
	alarmDel(idx);
}


void cmdAlarmParser(char *input) {
	char *cmd2;

	cmd2 = strtok(NULL, delim);
	if (cmd2 == NULL) {
		cmdHelpAlarm();
		return;
	}

	if (strcmp(cmd2, "add") == 0) {
		cmdAlarmAddParser(input);
		return;
	}
	if (strcmp(cmd2, "list") == 0) {
		cmdAlarmListParser(input);
		return;
	}
	if (strcmp(cmd2, "del") == 0) {
		cmdAlarmDelParser(input);
		return;
	}

	printf("Unknown command: %s\n", cmd2);
	cmdHelpAlarm();
}


void cmdParser(char *input) {
	char *cmd1;
//	printf("Got: %s\n", input);

	cmd1 = strtok(input, delim);
	if (cmd1 == NULL) {
		cmdHelp();
		return;
	}

	if (strcmp(cmd1, "todo") == 0) {
		cmdTodoParser(input);
		return;
	}
	if (strcmp(cmd1, "todolist") == 0) {
		cmdListParser(input);
		return;
	}
	if (strcmp(cmd1, "alarm") == 0) {
		cmdAlarmParser(input);
		return;
	}
	if (strcmp(cmd1, "help") == 0) {
		cmdHelp();
		return;
	}
	if (strcmp(cmd1, "quit") == 0) {
		exit(1);
		return;
	}

	printf("Unknown command: %s\n", cmd1);
	cmdHelp();
}


void cmdHelpTodo() {
	printf("Todo's:\n");
	printf("  todo add <list> <prio> <todotext>\n");
	printf("  todo edit <list>:<entry> <prio> <todotext>\n");
}


void cmdHelpList() {
	printf("List:\n");
	printf("  todolist view <list>\n");
	printf("  todolist add <listDst> <listSrc>:<entry>\n");
	printf("  todolist del <list> <entry>\n");
}


void cmdHelpAlarm() {
	printf("Alarm:\n");
	printf("  alarm add <alarmText>\n");
	printf("  alarm list\n");
	printf("  alarm view <alarmIndex>\n");
	printf("  alarm del <alarmIndex>\n");
}


void cmdHelp() {
	printf("Noteheap:\n");
	cmdHelpTodo();
	printf("\n");
	cmdHelpList();
	printf("\n");
	cmdHelpAlarm();
	printf("\n");
}
