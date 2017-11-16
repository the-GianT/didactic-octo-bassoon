#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
  printf("initial message prior to forking\n");

  pid_t f;
  f = fork();

  if (f) {
    f = fork();
  }

  if (f) {
    int status;
    printf("pid of completed child: %d\n", wait(&status));
    printf("The child was asleep for %d seconds.\n", status);
    printf("Parent: My work here is done.\n");
  } else {
    int limit;
    int r;

    srand(time(NULL));
    printf("Child: My pid is %d!\n", getpid());

    // Sleep for a random number of seconds in the range [5, 20]
    limit = RAND_MAX - (RAND_MAX % 16);
    while ((r = rand()) >= limit);
    sleep((r % 16) + 5);

    printf("Child: I'm finished!");
  }

  return 0;
}
