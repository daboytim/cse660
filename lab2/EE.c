//Derek Boytim
//CSE 660
//Lab2
//EE.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int FD_XYZ, pid, location, offset;
  char c;
  
  FD_XYZ = open("XYZ.txt", O_RDWR);
  pid = getpid();
  printf("\nPid: %d Code EE: This is what I have read from XYZ.txt:\n", pid);
  offset = -1;
  location = lseek(FD_XYZ, offset, SEEK_END);
  while(location >= 0) {
    read(FD_XYZ, &c, 1);
    printf("%c", c);
    offset--;
    location = lseek(FD_XYZ, offset, SEEK_END);
  }
  close(FD_XYZ);
  unlink("XYZ.txt"); 
  
  printf("\nPid: %d Code EE: Deleted XYZ.txt and I am terminating.\n", pid);

  return 0;
}
