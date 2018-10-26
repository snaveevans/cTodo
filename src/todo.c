#include <stdlib.h>
#include <string.h>
#include "guid/guid.h"
#include "todo.h"

struct Todo *create_todo(char *name)
{
	struct Todo *todo = calloc(1, sizeof(struct Todo));
	if (todo == NULL)
	{
		return NULL;
	}

	todo->name = calloc(strlen(name) + 1, sizeof(char));
	if (todo->name == NULL)
	{
		return NULL;
	}

	struct Guid *guid = new_guid();
	if (guid == NULL)
	{
		return NULL;
	}

	todo->id = guid;
	strcpy(todo->name, name);
	return todo;
}

struct Todo *get_todos()
{
	return NULL;
}

int write_todo(struct Todo *todo)
{
	return 0;
}

void free_todo(struct Todo *todo)
{
	free(todo->id->value);
	free(todo->id);
	free(todo->name);
	free(todo);
}
