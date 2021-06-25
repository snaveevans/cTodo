#include "guid/guid.h"
#include "todo.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char *name;
  char command = 0;
  const struct option longOptions[] = {{"new", required_argument, 0, 'n'},
                                       {"help", no_argument, 0, 'h'},
                                       {"list", no_argument, 0, 'l'},
                                       {"version", no_argument, 0, 'v'}};

  while (1) {
    int optionIndex = -1;
    int c = getopt_long(argc, argv, "n:hlv", longOptions, &optionIndex);

    if (c == -1) {
      break;
    }

    switch (c) {
    case 0:
      // long option hit
      command = longOptions[optionIndex].val;
      break;
    case 'n':
      command = c;
      name = optarg;
      break;
    case 'h':
      command = c;
      break;
    case 'l':
      command = c;
      break;
    case 'v':
      command = c;
      break;
    }

    if (command != 0) {
      break;
    }
  }

  switch (command) {
  case 'n': {
    Todo *todo = create_todo(name);
    if (todo == NULL) {
      return 1;
    }
    printf("Todo created id: %s name: %s \n", todo->id->value, todo->name);
    int result = append_todo(todo);
    if (result != 0) {
      printf("error: %d \n", result);
      return result;
    }
    free_todo(todo);
    break;
  }
  case 'h': {
    printf("help text \n");
    break;
  }
  case 'l': {
    int length = get_todos_length();
    printf("length: %d \n", length);
    Todo **todos = malloc(length * sizeof(Todo));
    int result = get_todos(todos, length) != 0;
    if (result != 0) {
      printf("error \n");
      printf("error: %d \n", result);
      return 1;
    }
    for (int pos = 0; pos < length; pos++) {
      printf("[%d] Id: %s -- Name: %s \n", pos, todos[pos]->id->value,
             todos[pos]->name);
    }
    free_todos(todos, length);

    break;
  }
  case 'v': {
    printf("version text \n");
    break;
  }
  }

  return 0;
}
