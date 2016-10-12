//Derek Boytim
//CSE 660
//Lab3b
//ProcX.c
//gcc -o ProcX ProcX.c ssem.o sshm.o

#include <stdio.h>

struct item1 {
  int value;
  char x1, x2;
};

int main() {
  int i, mid, full1, empty1;
  
  struct item1* buffer;

  mid = shm_get(13579, (struct item1**)&buffer, 20*sizeof(struct item1));

  full1 = sem_create(123456, 0);
  empty1 = sem_create(987654, 20);
  
  for(i=1; i<=500; i++) {
    struct item1* p = (struct item1*) malloc(sizeof(struct item1));
    p->value = i;
    p->x1 = 'x';
    p->x2 = 'x';
    sem_wait(empty1);
    buffer[i] = *p;
    sem_signal(full1);
    if(i%100 == 0) {
      sleep(1);
    }
  }
  shm_rm(mid);
  shm_rm(shm_get(24680, (struct item**)&buffer, 30*sizeof(struct item1)));
  sem_rm(full1);
  sem_rm(sem_open(654321));
  sem_rm(empty1);
  sem_rm(sem_open(456789));
}
