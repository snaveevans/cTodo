#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"
#include "guid/guid.h"

int main(int argc, char **argv)
{
	char *name;
	char command;
	const struct option longOptions[] = 
	{
		{"new", required_argument, 0, 'n'},
		{"help", no_argument, 0, 'h'},
		{"version", no_argument, 0, 'v'}
	};

	while (1) {
		int optionIndex = -1;
		int c= getopt_long(argc, argv, "n:hv", longOptions, &optionIndex);

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
			case 'v':
				command = c;
				break;
		}

		if (command)
		{
			break;
		}
	}

	switch (command)
	{
		case 'n':
			{
				struct Todo *todo = calloc(1, sizeof(struct Todo));
				createTodo(todo, name);
				printf("Todo created id: %s name: %s \n", todo->id->value, name);
				break;
			}
		case 'h':
			printf("help text \n");
			break;
		case 'v':
			printf("version text \n");
			break;
	}

	return 0;
}
