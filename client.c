#include "semaphores.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <task_command>\n", argv[0]);
    return 1;
  }

  key_t key = ftok("scheduler.c", 'R');

  int shmid = shmget(key, 0, 0);
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
    perror("semget: Semaphore not found. Is the scheduler running?");
    exit(1);
  }

  task_t new_task;
  new_task.task_id = getpid();
  strncpy(new_task.cmd, argv[1], sizeof(new_task.cmd) - 1);
  new_task.cmd[sizeof(new_task.cmd) - 1] = '\0';

  printf("Client %d attempting to submit task: '%s'\n", getpid(), new_task.cmd);

  sem_wait(sem_id);
  if (tq->count < MAX_TASKS) {
    tq->rear = (tq->rear + 1) % MAX_TASKS;
    tq->tasks[tq->rear] = new_task;
    tq->count++;
    printf("Task #%d submitted successfully.\n", new_task.task_id);
  } else {
    printf("Task queue is full. Task not submitted.\n");
  }
  sem_signal(sem_id);

  shmdt(tq);

  return 0;
}
