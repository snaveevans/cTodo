#include "file.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_todo_file_location() {
  char *homeDirectory = getenv("HOME");
  char *todoFile =
      calloc(strlen(homeDirectory) + strlen(TODO_FILE_NAME) + 2, sizeof(char));
  strcpy(todoFile, homeDirectory);
  strcat(todoFile, "/");
  strcat(todoFile, TODO_FILE_NAME);
  return todoFile;
}

FILE *get_todo_file(char *mode) {
  char *todoFile = get_todo_file_location();
  FILE *file = NULL;
  file = fopen(todoFile, mode);
  free(todoFile);
  return file;
}
