//Derek Boytim
//CSE 660
//Lab5
//PartB
//PipeW1.c
//gcc -o PipeW1 PipeW1.c

#include <stdio.h>
#include <unistd.h>

int main(int argCount, char *args[]) {
  int fd[2];
  fd[0] = atoi(args[0]);
  fd[1] = atoi(args[1]);

  close(fd[0]);
  char buffer[6];
  int i;
  for(i=1; i<=300; i++) {
    sprintf(buffer, "%d", i);
    if(i<10) {
      buffer[2] = buffer[0];
      buffer[1] = '0';
      buffer[0] = '0';
    }else if(i<100) {
      buffer[2] = buffer[1];
      buffer[1] = buffer[0];
      buffer[0] = '0';
    }
    buffer[3] = 'a';
    buffer[4] = 'a';
    buffer[5] = 'a';

    write(fd[1], buffer, 6);

    if(i%50 == 0) {
      sleep(1);
    }
  }
  close(fd[1]);
  
  exit(NULL);
}
