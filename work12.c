#include <stdio.h>
#include <stdlib.h>
#include <random.h>
#include <unistd.h>
#include <time.h>

int main()
{
  printf("initial message prior to forking");

  pid_t f0;
  f0 = fork();
  if (f0) {
    pid_t f1;
    f1 = fork();
  }

  if (f0 || f1) {
    int status;
    printf("pid of completed child: %d", wait(&status));
    printf("The child was asleep for %d seconds.", status);
  } else {
    srand(time(NULL));
    printf("pid of this child: %d", getpid());
    sleep(rand()); // change to be [5, 20] http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Randomization.html
  }

  return 0;
}
