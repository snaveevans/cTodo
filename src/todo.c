#include <stdlib.h>
#include "guid/guid.h"
#include "todo.h"

int createTodo(struct Todo *todo, char *name) {
	struct Todo temp = { newGuid(), name };
	*todo = temp;
	return 0;
}
