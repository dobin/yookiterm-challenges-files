
#include "noteheap-model.h"

/* All data is stored in this global struct */
struct Global global;


/* And initialized here */
void modelInit() {
	global.id = 0;
	global.alarmId = 0;

	bzero(global.todos, sizeof(global.todos));
	bzero(global.alarms, sizeof(global.alarms));
}


/*************************************************/

void alarmCleanupFunction() {
	// Not yet implemented, waiting for business case
	printf("  cleanup function running");
}


void alarmAdd(char *alarmName) {
	Alarm *alarm;

	alarm = malloc(sizeof(Alarm));
	alarm->name = strdup(alarmName);
	alarm->cleanupFunction = &alarmCleanupFunction;
	alarm->id = global.alarmId++;

	global.alarms[alarmGetFreeEntryIndex()] = alarm;

	printf("Added alarm (\"%s\", %x)\n",
		alarmName, alarm->id);
}


void alarmList() {
	int n = 0;
	Alarm *alarm;

	alarm = global.alarms[n];

	printf("Alarm: %i\n", n);
	printf("  Name: %s\n", alarm->name);
	printf("  gid: 0x%x\n", alarm->id);
}


void alarmDel(int alarmIndex) {
	Alarm *alarm;

	alarm = global.alarms[alarmIndex];
	global.alarms[alarmIndex] = NULL;

	free(alarm->name);
	alarm->cleanupFunction();
	free(alarm);

	printf("Alarm %i deleted", alarmIndex);
}


/*************************************************/


void todoAdd(char *listName, char *todoPrio, char *todoBody) {
	Todo *todo;
	int listIndex = -1;
	int listEntryIndex = -1;

	todo = (Todo*) malloc(sizeof(Todo));
	todo->body = strdup(todoBody);
	todo->priority = atoi(todoPrio);
	todo->id = global.id++;

	listIndex = listNameToIndex(listName);
	if (listIndex < 0) {
		return;
	}

	listEntryIndex = listGetFreeEntryIndex(listIndex);
	global.todos[listIndex][listEntryIndex] = todo;

	printf("Todo added to list %s as nr %i (prio 0x%x, body: \"%s\")\n",
		listName, listEntryIndex, todo->priority, todo->body);
}


void todoEdit(char *listName, char *listEntryIndex, char *todoPrio, char *todoBody) {
	Todo *todo;
	int listIndex = -1;
	int listEntry = -1;

	listIndex = listNameToIndex(listName);
	listEntry = atoi(listEntryIndex);

	todo = global.todos[listIndex][listEntry];

	todo->body = strdup(todoBody);
	todo->priority = atoi(todoPrio);

	printf("Todo %s:%i modified (prio 0x%x, body: \"%s\")\n",
		listName, listIndex, todo->priority, todo->body);
}


void todoPrint(Todo *todo) {
	if (todo->body != NULL) {
		printf("    body: %s\n", todo->body);
		printf("    prio: 0x%x\n", todo->priority);
		printf("    guid: 0x%x\n", todo->id);
	} else {
		printf("    body: NULL\n");
		printf("    prio: 0x%x\n", todo->priority);
		printf("    guid: 0x%x\n", todo->id);
	}
}


/*************************************************/


void listView(char *listName) {
	int listIndex = -1;
	Todo *todo;

	listIndex = listNameToIndex(listName);
	if (listIndex < 0) {
		return;
	}

	printf("View List: %s\n", listName);
	for(int n=0; n<LIST_SIZE; n++) {
		todo = global.todos[listIndex][n];

		if (todo == NULL) {
			continue;
		}
		printf("  index: %i\n", n);
		todoPrint(todo);
	}
}


void listDel(char *listName, char *listEntry) {
	int listIndex = -1;
	int listEntryIndex = -1;
	Todo *todo;

	listIndex = listNameToIndex(listName);
	if (listIndex < 0) {
		printf("Invalid list: %s\n", listName);
		return;
	}

	listEntryIndex = atoi(listEntry);

	todo = global.todos[listIndex][listEntryIndex];

	free(todo->body);
	free(todo);
	global.todos[listIndex][listEntryIndex] = NULL;

	printf("Deleted entry %i on list %s\n",
		listEntryIndex, listName);
}


void listAdd(char *dstListName, char *srcListName, char *srcListEntryIndex) {
	int dstList;
	int dstListEntry;
	int srcList;
	int srcListEntry;

	dstList = listNameToIndex(dstListName);
	if (dstList < 0) {
		printf("Destination list does not exist: %s\n", dstListName);
		return;
	}
	dstListEntry = listGetFreeEntryIndex(dstList);

	srcList = listNameToIndex(srcListName);
	if (srcList < 0) {
		printf("Source list does not exist: %s\n", dstListName);
		return;
	}
	srcListEntry = atoi(srcListEntryIndex);

	global.todos[dstList][dstListEntry] = global.todos[srcList][srcListEntry];

	printf("Added todo from %s:%s to %s:%i\n",
		srcListName, srcListEntryIndex, dstListName, dstListEntry);
}


int listNameToIndex(char *listName) {
	if (strcmp(listName, "work") == 0) {
		return 0;
	}

	if (strcmp(listName, "private") == 0) {
		return 1;
	}

	return -1;
}


int listGetFreeEntryIndex(int listIndex) {
	for(int n=0; n<LIST_SIZE; n++) {
		if (global.todos[listIndex][n] == NULL) {
			return n;
		}
	}

	return -1;
}


int alarmGetFreeEntryIndex() {
	for(int n=0; n<LIST_SIZE; n++) {
		if (global.alarms[n] == NULL) {
			return n;
		}
	}

	return -1;
}
