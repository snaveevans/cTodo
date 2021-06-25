#ifndef TODO_H_
#define TODO_H_
#include "guid/guid.h"

typedef struct {
  Guid *id;
  char *name;
} Todo;

Todo *create_todo(char *name);
int get_todos_length();
int get_todos(Todo **todos, int length);
int write_todo(Todo *todo);
void free_todo(Todo *todo);
void free_todos(Todo **todos, int length);

#endif
