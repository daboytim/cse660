//Derek Boytim
//CSE 660
//Lab2
//FF.c

#include <stdio.h> 
#include <unistd.h>

int main(int argCount, char *args[]) {
  int pid;

  pid = getpid();
  
  printf("\nPid: %d Code FF: Character string 1: %s. Character string 2: %s. Terminating.\n", pid, args[0], args[1]);
  
  return 0;
}
