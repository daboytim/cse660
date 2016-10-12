//Derek Boytim
//CSE 660
//Lab3
//Proc4.c

#include <stdio.h>

int main() {
  int i, timesChecked=0, timesNEqual=0;
  int s1, s2, s3, s4;
  s1 = sem_open(123456);
  s2 = sem_open(234567);
  s3 = sem_open(345678);
  s4 = sem_open(456789);

  int a0, a1, a2;
  a0 = sem_open(112233);
  a1 = sem_open(223344);
  a2 = sem_open(334455);

  int *Account, mid;
  mid = shm_get(987654, (void**)&Account, 3*sizeof(int));

  sem_signal(s1);
  sem_signal(s2);
  sem_signal(s3);
  sem_wait(s4);
  sem_wait(s4);
  sem_wait(s4);

  for(i=0; i<5000; i++) {
    sem_wait(a0);
    sem_wait(a1);
    sem_wait(a2);
    timesChecked++;
    if(Account[0]+Account[1]+Account[2] != 30000) {
      timesNEqual++;
    }
    sem_signal(a0);
    sem_signal(a1);
    sem_signal(a2);
    if(i==4000) {
      sleep(1);
    }
  }
  printf("Times Checked: %d\n", timesChecked);
  printf("Times Not Equal: %d\n", timesNEqual);

  shm_rm(mid);
  sem_rm(s1);
  sem_rm(s2);
  sem_rm(s3);
  sem_rm(s4);
  sem_rm(a0);
  sem_rm(a1);
  sem_rm(a2);
}
