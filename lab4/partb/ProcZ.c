//Derek Boytim
//CSE 660
//Lab3b
//ProcZ.c
//gcc -o ProcZ ProcZ.c ssem.o sshm.o

#include <stdio.h>

struct item1 {
  int value;
  char x1, x2;
};

struct item2 {
  char y1, y2, y3;
  int value;
};
int main() {
  int i, mid1, mid2, full1, full2, empty1, empty2;
  
  struct item1 *buffer1;
  struct item2 *buffer2;

  mid1 = shm_get(13579, (struct item1**)&buffer1, 20*sizeof(struct item1));
  mid2 = shm_get(24680, (struct item2**)&buffer2, 30*sizeof(struct item2));

  full1 = sem_create(123456, 0);
  full2 = sem_create(654321, 0);
  empty1 = sem_create(987654, 20);
  empty2 = sem_create(456789, 30);

  for(i=0; i<500; i++) {
    struct item1* c1 = (struct item1*) malloc(sizeof(struct item1));
    struct item2* c2 = (struct item2*) malloc(sizeof(struct item2));
    sem_wait(full1);
    sem_wait(full2);
    *c1 = buffer1[i];
    *c2 = buffer2[i];
    sem_signal(empty1);
    sem_signal(empty2);
    printf("%d%c%c ", c1->value, c1->x1, c1->x2);
    printf("%c%c%c%d ", c2->y1, c2->y2, c2->y3, c2->value);
    if(i%100 == 0) {
      sleep(1);
    }
  }
  
}
