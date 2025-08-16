#include "task.h"
#include <stdio.h>
#include <stdlib.h>

void task_queue_init(task_queue_t *tq) {
  if ((void *)tq == (void *)-1) {
    perror("shmat");
    exit(1);
  }

  tq->front = 0;
  tq->rear = -1;
  tq->count = 0;
}
