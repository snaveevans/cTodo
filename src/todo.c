#include <stdlib.h>
#include <string.h>
#include "guid/guid.h"
#include "todo.h"

int createTodo(struct Todo *todo, char *name)
{
	struct Guid *guid = (struct Guid *)calloc(1, sizeof(struct Guid));

	newGuid(guid);
	todo->id = guid;
	todo->name = name;
	
	return 0;
}
