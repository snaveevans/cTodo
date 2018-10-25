#ifndef TODO_H_ 
#define TODO_H_ 

struct Todo
{
	struct Guid *id;
	char *name;
};

int createTodo(struct Todo *todo, char *name);

#endif
