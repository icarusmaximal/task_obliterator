CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lrt -pthread

SRCS_SCHEDULER = scheduler.c task.c semaphores.c
SRCS_WORKER = worker.c task.c semaphores.c
SRCS_CLIENT = client.c task.c semaphores.c

all: scheduler worker client

scheduler: $(SRCS_SCHEDULER)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

worker: $(SRCS_WORKER)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

client: $(SRCS_CLIENT)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: all clean

clean:
	rm -f scheduler worker client
