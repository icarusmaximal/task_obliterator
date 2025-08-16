#include "semaphores.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

void sem_wait(int sem_id) {
  struct sembuf sem_op;
  sem_op.sem_num = 0;
  sem_op.sem_op = -1;
  sem_op.sem_flg = 0;
  semop(sem_id, &sem_op, 1);
}

void sem_signal(int sem_id) {
  struct sembuf sem_op;
  sem_op.sem_num = 0;
  sem_op.sem_op = 1;
  sem_op.sem_flg = 0;
  semop(sem_id, &sem_op, 1);
}

void sem_init(int sem_id, int value) {
  union semun arg;
  arg.val = value;
  if (semctl(sem_id, 0, SETVAL, arg) == -1) {
    perror("semctl");
    exit(1);
  }
}
