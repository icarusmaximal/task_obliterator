#pragma once
#define MAX_TASKS 100

typedef struct {
  int task_id;
  char cmd[256];
  int status;
} task_t;

typedef struct {
  task_t tasks[MAX_TASKS];
  int front;
  int rear;
  int count;

} task_queue_t;

void task_queue_init(task_queue_t *tq);
