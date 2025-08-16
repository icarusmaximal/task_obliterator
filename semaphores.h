#pragma once
#include <sys/sem.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

void sem_wait(int sem_id);
void sem_signal(int sem_id);
void sem_init(int sem_id, int value);
