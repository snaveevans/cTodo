#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"
#include "guid/guid.h"

int main(int argc, char **argv)
{
	char command;
	const struct option longOptions[] = 
	{
		{"help", no_argument, 0, 'h'},
		{"version", no_argument, 0, 'v'}
	};

	while (1) {
		int optionIndex = -1;
		int c= getopt_long(argc, argv, "hv", longOptions, &optionIndex);

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
			case 'h':
				command = 'h';
				break;
			case 'v':
				command = 'v';
				break;
		}

		if (command)
		{
			break;
		}
	}

	switch (command)
	{
		case 'h':
			printf("help text \n");
			break;
		case 'v':
			printf("version text \n");
			break;
	}

	return 0;
}
