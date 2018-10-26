#ifndef TODO_H_ 
#define TODO_H_ 

struct Todo
{
	struct Guid *id;
	char *name;
};

struct Todo *create_todo(char *name);

#endif
