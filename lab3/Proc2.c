//Derek Boytim
//CSE 660
//Lab3
//Proc2.c

#include <stdio.h>

int main() {
  int i, internal_reg;
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

/* synchronize with Proc1, Proc3 and Proc4 (4 process 4 way synchronization)*/
  sem_signal(s1);
  sem_signal(s3);
  sem_signal(s4);
  sem_wait(s2);
  sem_wait(s2);
  sem_wait(s2);

  for (i = 0; i < 1000; i++) {
    sem_wait(a2);
    sem_wait(a1);
    internal_reg = Account[1];      /*Proc3 takes from Account[2]*/          
    internal_reg = internal_reg - 200;
    Account[1] = internal_reg;

    /* same thing, except we're adding $200 to Account2 now... */
    internal_reg = Account[2];      /*Proc3 adds into Account[0]*/
    internal_reg = internal_reg + 200;
    Account[2] = internal_reg;
    sem_signal(a2);
    sem_signal(a1);

    if( (i+1)%100 == 0) {
      sem_wait(a0);
      sem_wait(a1);
      sem_wait(a2);
      printf("Account[0]: %d\n", Account[0]);
      printf("Account[1]: %d\n", Account[1]);
      printf("Account[2]: %d\n", Account[2]);
      printf("Sum: %d\n\n", Account[0]+Account[1]+Account[2]);
      sem_signal(a0);
      sem_signal(a1);
      sem_signal(a2);
    }
    if(i==400 || i== 700) {
      sleep(1);
    }
  }
       /*     Here add a code that prints contents of each account
          and their sum after 100th, 200th, 300th, ...., and 1000th iterations*/
  sem_wait(a0);
  sem_wait(a1);
  sem_wait(a2);
  printf("Total: %d\n\n", Account[0]+Account[1]+Account[2]);
  sem_signal(a0);
  sem_signal(a1);
  sem_signal(a2);
}
/*in the code above include some wait and signal operations on semaphores. Do not over-synchronize. */
