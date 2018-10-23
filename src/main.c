#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "todo.h"
#include "guid/random.h"
#include "guid/guid.h"

int testGuids(char **guids, int start, int end) {
	int i1, i2;
	char *guid1, *guid2;
	for (i1 = start; i1 < end; i1++) {
		guid1 = guids[i1];
		if (i1 % 10000 == 0) {
			printf("%d guids compared \n", i1 - start);
		}
		for (i2 = i1; i2 < end; i2++) {
			guid2 = guids[i2];
			if (strcmp(guid1, guid2) == 0 && i1 != i2) {
				printf("Guids are equal: [%d]:%s -- [%d]:%s \n", i1, guid1, i2, guid2);
				return 1;
			}
		}
	}

	return 0;
}

int main(int argc, char *argv[]) {
	int processId = getpid();
	printf("Process Id: %d \n\n", processId);

	/*printf("We got %d arguments \n", argc);*/
	/*for (int pos = 0; pos < argc; ++pos) {*/
		/*printf("argv[%d] %s ref:%p \n", pos, argv[pos], &argv[pos]);*/
	/*}*/
	/*printf("\n");*/

	/*char *javaHome;*/
	/*javaHome = getenv("JAVA_HOME");*/
	/*printf("JAVA_HOME=%s ref:%p \n\n", javaHome, &javaHome);*/

	/*char *badPointer;*/
	/*printf("BadPointer ref:%p \n\n", &badPointer);*/

	/*int n = 28;*/
	/*int* p = &n;*/
	/*printf("init n:%d p:%d \n\n", n, *p);*/

	/**p = 18;*/
	/*printf("2nd  n:%d p:%d \n\n", n, *p);*/

	/*n = 20;*/
	/*printf("3rd  n:%d p:%d \n\n", n, *p);*/

	/*int test = mySqrt(p);*/
	/*printf("4th  n:%d p:%d \n\n", n, *p);*/
	/*printf("test:%d \n\n", test);*/

	/*int fooTest = foo(8);*/
	/*printf("fooTest: %d \n", fooTest);*/

	/*int size = 10;*/
	/*int randomNumbers[size];*/
	/*for (int pos = 0; pos < size; pos++) {*/
		/*randomNumbers[pos] = getRandomBetween(1, 16);*/
		/*printf("randomNumber: %d \n", randomNumbers[pos]);*/
	/*}*/
	/*printf("\n");*/
	
	/*char *guid = newGuid();*/
	/*char *test1 = "hello";*/
	/*char *test2 = "hello1";*/

	/*printf("'%s' size: %zd \n", guid, strlen(guid));*/
	/*printf("'%s' size: %zd \n", test1, strlen(test1));*/
	/*printf("'%s' size: %zd \n", test2, strlen(test2));*/

	/*if (strcmp(test1, test2) != 0) {*/
		/*printf("strings are not equal \n");*/
	/*}*/

	/*unsigned int runs = 4294967295;*/
	const int childProcesses = 10;
	const unsigned int runs = 10000000;
	const unsigned int compareSize = runs / childProcesses;
	const int guidSize = 36;
	char **guids = (char **)malloc(sizeof(char)*guidSize*runs);
	int num;
	for (num = 0; num < runs; num++) {
		guids[num] = newGuid();
	}
	printf("%d guids generated \n", num);

	for (num = 0; num < childProcesses; num++) {
		pid_t pid = fork();
		if (pid == 0) {
			// child
			const int childNum = num;
			int start = childNum  * compareSize;
			int end = ((childNum  + 1) * compareSize) -1;
			testGuids(guids, start, end);
			exit(0);
		}
	}

	for (num = 0; num < childProcesses; num++) {
		wait(NULL);
		printf("%d child processes have completed \n", num + 1);
	}

	return 0;
}
