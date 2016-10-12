//Derek Boytim
//CSE 660
//Lab5
//PartA
//PipeRW.c
//gcc -o PipeRW PipeRW.c

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#define ASCII_ZERO 48
#define ASCII_CAPITAL_A 65

int main() {
  int fd[2], b, c;
  if(pipe(fd) != 0) {
    printf("%s", "Error creating pipe.");
    exit(NULL);
  }
  b = fork();
  if(b==0) {  //Process B
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
  c = fork();
  if(c==0) {  //Process C
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
  //Process A
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
