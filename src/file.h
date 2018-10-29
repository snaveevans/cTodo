#ifndef FILE_H_ 
#define FILE_H_ 
#include <stdio.h>

static const char *TODO_FILE_NAME = ".todo";

char *get_todo_file_location();
FILE *get_todo_file(char *mode);

#endif
