#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc == 2) {
    printf("Usage: %s seed arraysize\n", argv[0]);
    return 1;
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    //дочерний процесс: заменяем себя программой sequential_min_max
    char *args[] = {"./sequential_min_max", argv[1], argv[2], NULL};
    execv(args[0], args);
    perror("execv");
    exit(1);
  }

  //родитель ждёт завершения потомка
  int status;
  waitpid(pid, &status, 0);
  if (WIFEXITED(status))
    printf("sequential_min_max finished with code %d\n", WEXITSTATUS(status));
  return 0;
}