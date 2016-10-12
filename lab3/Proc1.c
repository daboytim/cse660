//Derek Boytim
//CSE 660
//Lab3
//Proc1.c
//compiled with makefile

#include <stdio.h>

int main() {
  int i, internal_reg;

/* here create and initialize all semaphores */
  int s1, s2, s3, s4;
  s1 = sem_create(123456, 0);
  s2 = sem_create(234567, 0);
  s3 = sem_create(345678, 0);
  s4 = sem_create(456789, 0);

  int a0, a1, a2;
  a0 = sem_create(112233, 1);
  a1 = sem_create(223344, 1);
  a2 = sem_create(334455, 1);

/* here created: shared memory array Account of size 3 */
  int *Account, mid;
  mid = shm_get(987654, (void**)&Account, 3*sizeof(int));
  Account[0]=10000;
  Account[1]=10000;
  Account[2]=10000;

/* synchronize with Proc2, Proc3 and Proc4 (4 process 4 way synchronization)*/
  sem_signal(s2);
  sem_signal(s3);
  sem_signal(s4);
  sem_wait(s1);
  sem_wait(s1);
  sem_wait(s1);

  for (i = 0; i < 1000; i++) {
    sem_wait(a0);
    sem_wait(a1);
    internal_reg = Account [0];
    internal_reg = internal_reg - 200;
    Account[0] = internal_reg;

    /* same thing, except we're adding $100 to Account1 now... */
    internal_reg = Account [1];
    internal_reg = internal_reg + 200;
    Account[1] = internal_reg;
    sem_signal(a0);
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
    if(i==300 || i== 600) {
      sleep(1);
    }
  }
      /*     Here add a code that prints contents of each account
          and their sumafter 100th, 200th, 300th, ...., and 1000th iterations*/ 
  sem_wait(a0);
  sem_wait(a1);
  sem_wait(a2);
  printf("Total: %d\n\n", Account[0]+Account[1]+Account[2]);
  sem_signal(a0);
  sem_signal(a1);
  sem_signal(a2);
}

/*in the code above include some wait and signal operations on semaphores. Do not over-synchronize. */
