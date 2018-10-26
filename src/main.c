#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cjson/cJSON.h>
#include "todo.h"
#include "guid/guid.h"

const char *TODO_FILE_NAME = ".todos";

int _createTodos(struct Todo **todos, int count)
{
	char *nameTemplate = "Hello World - ";
	for (int i = 0; i < count; i++)
	{
		char *name = calloc(strlen(nameTemplate) + 2, sizeof(char));
		char *temp = calloc(2, sizeof(char));;

		strcpy(name, nameTemplate);
		sprintf(temp, "%d", i);
		strcat(name, temp);

		struct Todo *todo = create_todo(name);
		todos[i] = todo;

		free(temp);
	}
	return 0;
}

int main(int argc, char **argv)
{
	char *name;
	char command = 0;
	const struct option longOptions[] = 
	{
		{"new", required_argument, 0, 'n'},
		{"help", no_argument, 0, 'h'},
		{"list", no_argument, 0, 'l'},
		{"version", no_argument, 0, 'v'}
	};

	while (1) {
		int optionIndex = -1;
		int c= getopt_long(argc, argv, "n:hlv", longOptions, &optionIndex);

		if (c== -1)
		{
			break;
		}

		switch (c)
		{
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

		if (command != 0)
		{
			break;
		}
	}

	switch (command)
	{
		case 'n':
			{
				struct Todo *todo = create_todo(name);
				if (todo == NULL)
				{
					return 1;
				}
				printf("Todo created id: %s name: %s \n", todo->id->value, todo->name);
				free(todo->id->value);
				free(todo->id);
				// no need to free name, it belongs to the thread's stack
				free(todo);
				break;
			}
		case 'h':
			printf("help text \n");
			break;
		case 'l':
			{
				/*char *homeDirectory= getenv("HOME");*/
				/*char *todoFile = calloc(strlen(homeDirectory) + strlen(TODO_FILE_NAME) + 2, sizeof(char));*/
				/*strcpy(todoFile, homeDirectory);*/
				/*strcat(todoFile, "/");*/
				/*strcat(todoFile, TODO_FILE_NAME);*/
				/*puts(todoFile);*/
				/*free(homeDirectory);*/

				/*FILE *file = NULL;*/
				/*int hasAccess = access(todoFile, R_OK|W_OK);*/
				/*file = fopen(todoFile, "a+");*/
				/*if (file != NULL)*/
				/*{*/
					/*if (hasAccess == 0)*/
					/*{*/
						/*// file already exists read in existing data*/
					/*}*/

					/*// initalize*/
					/*fclose(file);*/
				/*}*/

				/*free(todoFile);*/
				int size = 5;
				struct Todo **todos = (struct Todo **)calloc(size, sizeof(struct Todo));
				_createTodos(todos, size);
				for (int pos = 0; pos < size; pos++)
				{
					printf("Todo id: %s name: %s \n", todos[pos]->id->value, todos[pos]->name);
					free(todos[pos]->id->value);
					free(todos[pos]->id);
					free(todos[pos]->name);
					free(todos[pos]);
				}
				free(todos);
				break;
			}
		case 'v':
			printf("version text \n");
			break;
	}

	return 0;
}
