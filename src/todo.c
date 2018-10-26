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

	struct Guid *guid = new_guid();
	if (guid == NULL)
	{
		return NULL;
	}

	todo->id = guid;
	todo->name = name;
	return todo;
	
	return 0;
}

int get_todos(struct Todo **todos)
{
	return 0;
}
