#include "semaphores.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void main() {
  key_t key = ftok("scheduler.c", 'R');
  int shmid = shmget(key, sizeof(task_queue_t), IPC_CREAT | 0666);
  if (shmid == -1) {
    perror("shmget");
    exit(1);
  }
  task_queue_t *tq = (task_queue_t *)shmat(shmid, NULL, 0);
  if ((void *)tq == (void *)-1) {
    perror("shmat");
    exit(1);
  }

  int sem_id = semget(key, 0, 0);
  if (sem_id == -1) {
    perror("semget");
    exit(1);
  }

  while (1) {

    sem_wait(sem_id);

    if (!tq->count) {
      printf("nothing to do");
      sem_signal(sem_id);
      sleep(1);

    } else {
      task_t current_task = tq->tasks[tq->front];
      printf("task taken: %s", current_task.cmd);
      tq->front = (tq->front + 1) % MAX_TASKS;
      tq->count--;

      sem_signal(sem_id);

      system(current_task.cmd);
    }
  }
  shmdt(tq);
}
