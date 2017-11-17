#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int devrand() {
  unsigned int randval;
  int fd;

  fd = open("/dev/random", O_RDONLY);
  read(fd, &randval, sizeof(randval));
  close(fd);

  return randval;
}

int main()
{
  printf("Parent: It's forking time!\n");

  pid_t f;
  f = fork();

  if (f) {
    f = fork();
  }

  if (f) {
    int status;
    printf("pid of completed child: %d\n", wait(&status));
    if (WIFEXITED(status)) {
      printf("The child was asleep for %d seconds.\n", WEXITSTATUS(status));
    } else {
      printf("The child process did not terminate normally.\n");
    }
    printf("Parent: My work here is done.\n");
  } else {
    int limit;
    int r;
    int slptime;

    srand(devrand());
    printf("Child: My pid is %d!\n", getpid());

    // Sleep for a random number of seconds in the range [5, 20]
    limit = RAND_MAX - (RAND_MAX % 16);
    while ((r = rand()) >= limit);
    slptime = (r % 16) + 5;
    sleep(slptime);

    printf("Child: I'm finished!\n");
    exit(slptime);
  }

  return 0;
}
