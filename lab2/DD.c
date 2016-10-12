//Derek Boytim
//CSE 660
//Lab2
//DD.c

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main() {
  int pid, C3, ps, child, rtn;
  char *arg[0];

  pid = getpid();

  C3 = fork();
  if(C3==0) {
    execv("CC", arg); 
  }
  
  printf("\nPid: %d Code DD: Creaded process Pid: %d (code CC) and waiting for 4 seconds.\n", pid, C3);

  sleep(4);

  ps = fork();
  if(ps==0) {
    execl("/bin/ps", "ps", "-u", "boytim", NULL);
  }

  printf("\nPid: %d Code DD: 4 sec elapsed. Created process Pid: %d (ps) and waiting for it to terminate.\n", pid, ps);

  child = wait(&rtn);
  while(child != ps) {
    child = wait(&rtn);
  }

  printf("\nPid: %d Code DD: Process Pid: %d (ps) terminated.\n", pid, ps);

  printf("\nPid: %d Code DD: Killing priocess Pid: %d (code CC).\n", pid, C3);

  rtn = kill(C3, SIGKILL);
  if(rtn==0) {
    printf("\nPid: %d Code DD: Process Pid: %d terminated.\n", pid, C3);
  }

  printf("\nPid: %d Code DD: Terminating.\n", pid);

  return 0;
}
