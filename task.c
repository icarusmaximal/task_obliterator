#include "task.h"

void task_queue_init(task_queue_t *tq) {

  tq->front = 0;
  tq->rear = -1;
  tq->count = 0;
}
