//Derek Boytim
//CSE 660
//Lab5
//PartC
//Pipe.c
//gcc -o Pipe Pipe.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 100
#define TOKEN_SIZE 10

void getTokens(char *, char *, char *, char *, char *);

int main() {
  char buffer[BUFFER_SIZE];
  printf("%s\n", "'exit' to quit");
  printf("%s", "\nshell_prompt> ");
  gets(buffer);
  while(strcmp(buffer, "exit") != 0) {
    //printf("%s\n", buffer);
    char procA[TOKEN_SIZE], argsA[TOKEN_SIZE], procB[TOKEN_SIZE], argsB[TOKEN_SIZE];
    getTokens(buffer, procA, argsA, procB, argsB);
    //printf(":%s:%s:%s:%s:\n", procA, argsA, procB, argsB);
    int fd[2], a, b, child, rtn;;
    if(pipe(fd) != 0) {
      printf("%s", "Error creating pipe.");
      exit(NULL);
    }
    a = fork();
    if(a == 0) {
      dup2(fd[1], 1);
      close(fd[0]);
      execlp(procA, argsA, NULL); //known error; ignoring arguments
    }
    b = fork();
    if(b == 0) {
      dup2(fd[0], 0);
      close(fd[1]);
      execlp(procB, argsB, NULL); //known error; ignoring arguments
    }
    close(fd[0]);
    close(fd[1]);
    int i;
    for(i=0; i<BUFFER_SIZE; i++) { //clear the buffer
      buffer[i] = '\0';
    }
    child = wait(&rtn); //wait for second child to terminate
    while(child != b) {
      child = wait(&rtn);
    }
    printf("%s", "\nshell_prompt> ");
    gets(buffer);
  }
}

void getTokens(char *buffer, char *procA, char *argsA, char *procB, char *argsB) {
  int i, j;
  for(i=0, j=0; buffer[i] != ' '; i++, j++) {
    procA[j] = buffer[i];
  }
  procA[j] = '\0';
  i++;
  for(j=0; buffer[i] != '|'; i++, j++) {
    argsA[j] = buffer[i];
  }
  argsA[j] = '\0';
  i += 2; //skip '| '
  for(j=0; buffer[i] != ' ' && buffer[i] != '\0'; i++, j++) {
    procB[j] = buffer[i];
  }
  procB[j] = '\0';
  if(buffer[i] == '\0') {
    argsB[0] = '\0';
    return;
  }
  i++;
  for(j=0; buffer[i] != '\0'; i++, j++) {
    argsB[j] = buffer[i];
  }
  argsB[j] = '\0';
}
