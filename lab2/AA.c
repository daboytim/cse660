//Derek Boytim
//CSE 660
//Lab2
//AA.c
//used makefile to compile

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main() {
  int pid, B, C1, C1a, C2, C3, D, E, F, child, rtn;
  char *arg[2];

  pid = getpid();

  B = fork();
  if(B==0) {
    execv("BB", arg);
  }
    
  C1 = fork();
  if(C1==0) {
    execv("CC", arg);
  }

  C1a = fork();
  if(C1a==0) {
    execv("CC", arg);
  }

  printf("\nPid: %d Code AA: Created process Pid: %d (code BB), process Pid: %d (code CC) and process Pid: %d (code CC).\n", pid, B, C1, C1a);
  
  child = wait(&rtn);

  printf("\nPid: %d Code AA: Process Pid: %d terminated.\n", pid, child);

  D = fork();
  if(D==0) {
    execv("DD", arg);
  }
    
  C2 = fork();
  if(C2==0) {
    execv("CC", arg);
  }

  E = fork();
  if(E==0) {
    execv("EE", arg);
  }

  printf("\nPid: %d Code AA: Created process Pid: %d (code DD), process Pid: %d (code CC) and process Pid: %d (code EE).\n", pid, D, C2, C3);
  
  child = wait(&rtn);
  while(child != D) {
    printf("\nPid: %d Code AA: Process Pid: %d terminated (not D process).\n", pid, child);
    child = wait(&rtn);
  }

  printf("\nPid: %d Code AA: Process Pid: %d (code DD) terminated.\n", pid, D);

  printf("\nPid: %d Code AA: Killing process Pid: %d, process Pid: %d and process Pid: %d.\n", pid, C1, C1a, C2);

  rtn = kill(C1, SIGKILL);
  if(rtn == 0) {
    printf("\nPid: %d Code AA: Process Pid: %d terminated.\n", pid, C1);
  }
  
  rtn = kill(C1a, SIGKILL);
  if(rtn == 0) {
    printf("\nPid: %d Code AA: Process Pid: %d terminated.\n", pid, C1a);
  }
  
  rtn = kill(C2, SIGKILL);
  if(rtn == 0) {
    printf("\nPid: %d Code AA: Process Pid: %d terminated.\n", pid, C2);
  }
  
  printf("\nPid: %d Code AA: Input the character string: ", pid);
  
  scanf("%s", arg[0]);
  
  arg[1] = "Derek Boytim";

  F = fork();
  if(F==0) {
    execv("FF", arg);
  }

  printf("\nPid: %d Code AA: Created process Pid: %d (code FF) and terminating.\n", pid, F);

  return 0;
}
