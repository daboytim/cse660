//Derek Boytim
//CSE 660
//Lab5
//PartB
//PipeW2.c
//gcc -o PipeW2 PipeW2.c

#include <stdio.h>
#include <unistd.h>
#define ASCII_ZERO 48
#define ASCII_CAPITAL_A 65

int main(int argCount, char *args[]) {
  int fd[2];
  fd[0] = atoi(args[0]);
  fd[1] = atoi(args[1]);

  close(fd[0]);
  char buffer[3];
  int i;
  for(i=0; i<260; i++) {
    buffer[0] = ASCII_CAPITAL_A + (i%26);
    buffer[1] = 'x';
    buffer[2] = ASCII_ZERO + i/26;

    write(fd[1], buffer, 3);

    if((i+1)%60 == 0) {
      sleep(2);
    }
  }
  close(fd[1]);
  
  exit(NULL);
}
