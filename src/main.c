#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"
#include "guid/guid.h"

int main(int argc, char **argv)
{

	struct Guid *guid = (struct Guid *)calloc(1, sizeof(struct Guid));
	newGuid(guid);
	printf("guid: %s \n", guid->value);
	free(guid->value);
	free(guid);

	char *test = calloc(12, sizeof(char));
	strcpy(test, "Hello World");
	struct Todo *todo = calloc(1, sizeof(struct Todo));;
	createTodo(todo, test);

	printf("id: %s name: %s \n", todo->id->value, todo->name);

	free(todo->id->value);
	free(todo->id);
	free(todo->name);
	free(todo);

	return 0;
}
