#include "semaphores.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define NUM_WORKERS 5

int main() {
  // Generate unique IPC key, assigned to shared memory
  key_t key = ftok("scheduler.c", 'R');

  // Create shared memory segment for the task queue
  int shmid = shmget(key, sizeof(task_queue_t), IPC_CREAT | 0666);
  if (shmid == -1) {
    perror("shmget");
    exit(1);
  }

  // 3. Attach shared memory
  task_queue_t *tq = (task_queue_t *)shmat(shmid, NULL, 0);
  if ((void *)tq == (void *)-1) {
    perror("shmat");
    exit(1);
  }

  // 4. Initialize the queue
  task_queue_init(tq);

  // 5. Create a semaphore
  int sem_id = semget(key, 1, IPC_CREAT | 0666);
  if (sem_id == -1) {
    perror("semget");
    exit(1);
  }

  // 6. Initialize the semaphore value to 1 (acting as a mutex)
  union semun arg;
  arg.val = 1;
  if (semctl(sem_id, 0, SETVAL, arg) == -1) {
    perror("semctl");
    exit(1);
  }

  printf("Scheduler running. Shared memory and semaphore created.\n");
  printf("Shared Memory ID: %d, Semaphore ID: %d\n", shmid, sem_id);

  while (1) {
    sleep(5);
  }
}
