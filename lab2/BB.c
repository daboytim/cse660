//Derek Boytim
//CSE 660
//Lab2
//BB.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int FD_XYZ, FD_x, charRead, pid;
  char buffer[200];
  
  pid = getpid();

  printf("\nPid: %d Code BB: Creating file XYZ.txt and writing 200 characters from file x.y\n", pid);

  FD_XYZ = creat("XYZ.txt", 384);
  FD_x = open("/usr/class/cis660/x.y", O_RDONLY);

  lseek(FD_x, -200, SEEK_END);
  charRead = read(FD_x, &buffer, 200);
  write(FD_XYZ, buffer, charRead);

  printf("\nPid: %d Code BB: Done and terminating.\n", pid);

  close(FD_x);
  close(FD_XYZ);

  return 0;
}
