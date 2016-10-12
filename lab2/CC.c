//Derek Boytim
//CSE 660
//Lab2
//CC.c

#include <stdio.h>
#include <unistd.h>
#define TRUE 1

int main() {
  int pid = getpid();
  printf("\nPid: %d Code CC: Entering infinite loop.\n", pid);
  while(TRUE) {
    sleep(1);
  }
  return 0;
}
