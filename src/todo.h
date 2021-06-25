#ifndef TODO_H_
#define TODO_H_
#include "guid/guid.h"

typedef struct {
  Guid *id;
  char *name;
} Todo;

Todo *create_todo(char *name);
Todo** get_todos(int *length);
int append_todo(Todo *todo);
void free_todo(Todo *todo);
void free_todos(Todo **todos, int length);

#endif
