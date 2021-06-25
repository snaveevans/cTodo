#include <stdlib.h>
#include <time.h>

int isInitialized = 0;

int getRandomBetween(int min, int max) {
  if (isInitialized == 0) {
    srand(time(0));
    isInitialized = 1;
  }

  int num = (rand() % (max - min + 1)) + min;
  return num;
}
