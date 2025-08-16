#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int ct = atoi(argv[1]);
  int dur = atoi(argv[2]);

  for (int i = 0; i < ct; i++) {
    sleep(dur);
    printf("hello\n");
  }
  return 0;
}
