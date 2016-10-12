//Derek Boytim
//CSE 660
//Lab4
//ThreadB.c
//gcc -o ThreadB ThreadB.c -lpthread -lrt

#include <stdio.h>
#define _REENTRANT  
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#define NUM_THREADS 3

void *thread1(void *);
void *thread2(void *);
void *thread3(void *);

struct item1 {
    int value;
    char x1, x2;
};

struct item2 {
    char y1, y2, y3;
    int value;
};

pthread_t tid[NUM_THREADS];

struct item1 buffer1[20];
struct item2 buffer2[30];

sem_t full1, full2, empty1, empty2;

//-------------------------------------------------

int main() {
    int i;

    i = sem_init(&full1, 0, 0);
    i = sem_init(&full2, 0, 0);
    i = sem_init(&empty1, 0, 20);
    i = sem_init(&empty2, 0, 30);

    i = pthread_create(&tid[0], NULL, thread1, NULL);
    i = pthread_create(&tid[1], NULL, thread2, NULL);
    i = pthread_create(&tid[2], NULL, thread3, NULL);
  
    pthread_exit(NULL);
}

//-------------------------------------------------

void *thread1(void *arg) {
    int i;
    for(i=1; i<=500; i++) {
        struct item1* p = (struct item1*) malloc(sizeof(struct item1));
        p->value = i;
        p->x1 = 'x';
        p->x2 = 'x';
        sem_wait(&empty1);
        buffer1[(i-1)%20] = *p;
        sem_post(&full1);
        if(i%50 == 0) {
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

//-------------------------------------------------

void *thread2(void *arg) {
    int i;
    for(i=1; i<=500; i++) {
        struct item2* p = (struct item2*) malloc(sizeof(struct item2));
        p->y1 = 'Y';
        p->y2 = 'Y';
        p->y3 = 'Y';
        p->value = i;
        sem_wait(&empty2);
        buffer2[(i-1)%30] = *p;
        sem_post(&full2);
        if(i%75 == 0) {
            sleep(2);
        }
    }
    pthread_exit(NULL);
}

//-------------------------------------------------

void *thread3(void *arg) {
    int i;
    for(i=0; i<500; i++) {
        struct item1* c1 = (struct item1*) malloc(sizeof(struct item1));
        struct item2* c2 = (struct item2*) malloc(sizeof(struct item2));
        sem_wait(&full1);
        sem_wait(&full2);
        *c1 = buffer1[i%20];
        *c2 = buffer2[i%30];
        sem_post(&empty1);
        sem_post(&empty2);
        printf("%d%c%c ", c1->value, c1->x1, c1->x2);
        printf("%c%c%c%d ", c2->y1, c2->y2, c2->y3, c2->value);
        if(i%50 == 0) {
            sleep(1);
        }
    }
    exit(NULL);
}
