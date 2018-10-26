#ifndef TODO_H_ 
#define TODO_H_ 

struct Todo
{
	struct Guid *id;
	char *name;
};

struct Todo *create_todo(char *name);
struct Todo *get_todos();
int write_todo(struct Todo *todo);
void free_todo(struct Todo *todo);

#endif
