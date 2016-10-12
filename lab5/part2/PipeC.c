//Derek Boytim
//CSE 660
//Lab5
//PartB
//PipeC.c
//gcc -o PipeC PipeC.c

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  int fd[2], b, c, d;
  char arg1[10];
  char arg2[10];
  if(pipe(fd) != 0) {
    printf("%s", "Error creating pipe.");
    exit(NULL);
  }
  sprintf(arg1, "%d", fd[0]);
  sprintf(arg2, "%d", fd[1]);
  b = fork();
  if(b==0) {
    execl("PipeW1", arg1, arg2, NULL);
  }
  c = fork();
  if(c==0) {
    execl("PipeW2", arg1, arg2, NULL);
  }
  d = fork();
  if(d==0) {
    execl("PipeR", arg1, arg2, NULL);
  }
  close(fd[0]);
  close(fd[1]);
  exit(NULL);
}
