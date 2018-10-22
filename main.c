#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int mySqrt(int *b) {
	*b = *b * *b;
	return 0;
}

int main(int argc, char *argv[]) {
	int processId = getpid();
	printf("Process Id: %d \n\n", processId);

	printf("We got %d arguments \n", argc);
	for (int pos = 0; pos < argc; ++pos) {
		printf("argv[%d] %s ref:%p \n", pos, argv[pos], &argv[pos]);
	}
	printf("\n");

	char *javaHome;
	javaHome = getenv("JAVA_HOME");
	printf("JAVA_HOME=%s ref:%p \n\n", javaHome, &javaHome);

	char *badPointer;
	printf("BadPointer ref:%p \n\n", &badPointer);

	int n = 28;
	int* p = &n;
	printf("init n:%d p:%d \n\n", n, *p);

	*p = 18;
	printf("2nd  n:%d p:%d \n\n", n, *p);

	n = 20;
	printf("3rd  n:%d p:%d \n\n", n, *p);

	int test = mySqrt(p);
	printf("4th  n:%d p:%d \n\n", n, *p);
	printf("test:%d \n\n", test);

	return 0;
}
