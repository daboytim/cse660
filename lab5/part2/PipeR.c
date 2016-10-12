//Derek Boytim
//CSE 660
//Lab5
//PartB
//PipeR.c
//gcc -o PipeR PipeR.c

#include <stdio.h>
#include <unistd.h>

int main(int argCount, char *args[]) {
  int fd[2];
  fd[0] = atoi(args[0]);
  fd[1] = atoi(args[1]);

  close(fd[1]);
  int i, charRead=-1;
  char buffer[100];
  for(i=0; charRead != 0; i++) {
    charRead = read(fd[0], buffer, 100);
    int j;
    for(j=0; j<charRead; j++) {
      printf("%c", buffer[j]);
    }
    printf("%c", '\n');
    if((i+1)%30 == 0) {
      sleep(1);
    }
  }
  close(fd[0]);
  
  exit(NULL);
}
