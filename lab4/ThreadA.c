//Derek Boytim
//CSE 660
//Lab4
//ThreadA.c
//gcc -o ThreadA ThreadA.c -lpthread -lrt

#include <stdio.h>
#define _REENTRANT  
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#define NUM_THREADS 4

void *thread1(void *);
void *thread2(void *);
void *thread3(void *);
void *thread4(void *);

int Account[3];
pthread_t tid[NUM_THREADS];
sem_t s1, s2, s3, s4, mutex;

//-------------------------------------------------

int main() {
    int i;
  
    i = sem_init(&s1, 0, 0);
    i = sem_init(&s2, 0, 0);
    i = sem_init(&s3, 0, 0);
    i = sem_init(&s4, 0, 0);

    i = sem_init(&mutex, 0, 1);

    Account[0]=10000;
    Account[1]=10000;
    Account[2]=10000;
  
    i = pthread_create(&tid[0], NULL, thread1, NULL);
    i = pthread_create(&tid[1], NULL, thread2, NULL);
    i = pthread_create(&tid[2], NULL, thread3, NULL);
  
    for(i=0; i<NUM_THREADS; i++) {
        pthread_join(tid[0], NULL);
    }
    pthread_exit(NULL);
}

//-------------------------------------------------

void *thread1(void *arg) {
    int i, internal_reg;

    i = pthread_create(&tid[3], NULL, thread4, NULL);

    sem_post(&s2);
    sem_post(&s3);
    sem_post(&s4);
    sem_wait(&s1);
    sem_wait(&s1);
    sem_wait(&s1);
  
    for (i = 0; i < 1000; i++) {
        sem_wait(&mutex);
        internal_reg = Account [0];
        internal_reg = internal_reg - 200;
        Account[0] = internal_reg;

        internal_reg = Account [1];
        internal_reg = internal_reg + 200;
        Account[1] = internal_reg;
        sem_post(&mutex);

        if( (i+1)%100 == 0) {
            int x, y, z;
            sem_wait(&mutex);
            x = Account[0];
            y = Account[1];
            z = Account[2];
            sem_post(&mutex);
            printf("Thread:%d ", pthread_self());
            printf("Account[0]:%d ", x);
            printf("Account[1]:%d ", y);
            printf("Account[2]:%d ", z);
            printf("Sum: %d\n\n", x+y+z);
        }
        if(i==500) {
	      sleep(1);
        }
    }
    pthread_exit(NULL);
}

//-------------------------------------------------

void * thread2(void *arg) {
    int i, internal_reg;
  
    sem_post(&s1);
    sem_post(&s3);
    sem_post(&s4);
    sem_wait(&s2);
    sem_wait(&s2);
    sem_wait(&s2);
  
    for (i = 0; i < 1000; i++) {
        sem_wait(&mutex);
        internal_reg = Account [1];
        internal_reg = internal_reg - 200;
        Account[1] = internal_reg;

        internal_reg = Account [2];
        internal_reg = internal_reg + 200;
        Account[2] = internal_reg;
        sem_post(&mutex);

        if( (i+1)%100 == 0) {
            int x, y, z;
            sem_wait(&mutex);
            x = Account[0];
            y = Account[1];
            z = Account[2];
            sem_post(&mutex);
            printf("Thread:%d ", pthread_self());
            printf("Account[0]:%d ", x);
            printf("Account[1]:%d ", y);
            printf("Account[2]:%d ", z);
            printf("Sum: %d\n\n", x+y+z);
        }
        if(i==550) {
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

//-------------------------------------------------

void * thread3(void *arg) {
    int i, internal_reg;
  
    sem_post(&s1);
    sem_post(&s2);
    sem_post(&s4);
    sem_wait(&s3);
    sem_wait(&s3);
    sem_wait(&s3);
  
    for(i=0; i<1000; i++) {
        sem_wait(&mutex);
        internal_reg = Account [2];
        internal_reg = internal_reg - 200;
        Account[2] = internal_reg;

        internal_reg = Account [0];
        internal_reg = internal_reg + 200;
        Account[0] = internal_reg;
        sem_post(&mutex);

        if((i+1)%100 == 0) {
            int x, y, z;
            sem_wait(&mutex);
            x = Account[0];
            y = Account[1];
            z = Account[2];
            sem_post(&mutex);
            printf("Thread:%d ", pthread_self());
            printf("Account[0]:%d ", x);
            printf("Account[1]:%d ", y);
            printf("Account[2]:%d ", z);
            printf("Sum: %d\n\n", x+y+z);
        }
        if(i==650) {
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

//-------------------------------------------------

void * thread4(void *arg) {
    int i, timesChecked=0, timesNEqual=0;
  
    sem_post(&s1);
    sem_post(&s2);
    sem_post(&s3);
    sem_wait(&s4);
    sem_wait(&s4);
    sem_wait(&s4);
  
    for(i=0; i<5000; i++) {
        int x, y, z;
        sem_wait(&mutex);
        x = Account[0];
        y = Account[1];
        z = Account[2];
        sem_post(&mutex);
        if(x+y+z != 30000) {
            timesNEqual++;
        }
        timesChecked++;
        if(i==2500) {
            sleep(1);
        }
    }
    printf("Times Checked: %d\n", timesChecked);
    printf("Times Not Equal: %d\n", timesNEqual);
    exit(0);
}

