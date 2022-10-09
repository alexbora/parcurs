/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mutex1
 * @created     : Duminică Sep 11, 2022 22:14:09 EEST
 */

#include <pthread.h>
#include <stdlib.h>
/* #include <sys/_pthread/_pthread_mutex_t.h> */
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void *f1(void *p) {
  sleep(3);
  pthread_mutex_unlock(&m1);
  puts("f1\n");
  return NULL;
}

void *f2(void *p) {
  sleep(5);
  puts("f2\n");
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_mutex_lock(&m1);

  pthread_t t1;
  pthread_create(&t1, NULL, f2, NULL);
  f1(NULL);

  pthread_join(t1, NULL);

  return 0;

  pthread_mutex_t *mtx = NULL;
  pthread_mutex_init(mtx, NULL);
  return 0;
}
