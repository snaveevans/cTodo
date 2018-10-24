#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "todo.h"
#include "guid/random.h"
#include "guid/guid.h"

int testGlobal;

int main(int argc, char *argv[]) {
	int processId = getpid();
	printf("Process Id: %d \n\n", processId);

	struct Todo *todo = calloc(1, sizeof(struct Todo));;
	createTodo(todo, "hello world");

	printf("id: %s name: %s \n", todo->id, todo->name);

	static int foo = 1000;
	free(todo);

	return 0;
}
