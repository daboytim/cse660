//Derek Boytim
//CSE 660
//Lab3b
//ProcY.c
//gcc -o ProcY ProcY.c ssem.o sshm.o

#include <stdio.h>

struct item2 {
  char y1, y2, y3;
  int value;
};

int main() {
  int i, mid, full2, empty2;

  struct item2 *buffer;

  mid = shm_get(24680, (struct item2**)&buffer, 20*sizeof(struct item2));

  full2 = sem_create(654321, 0);
  empty2 = sem_create(456789, 30);

  for(i=1; i<=500; i++) {
    struct item2* p = (struct item2*) malloc(sizeof(struct item2));
    p->y1 = 'Y';
    p->y2 = 'Y';
    p->y3 = 'Y';
    p->value = i;
    sem_wait(empty2);
    buffer[i] = *p;
    sem_signal(full2);
    if(i%75 == 0) {
      sleep(2);
    }
  }
  
}
