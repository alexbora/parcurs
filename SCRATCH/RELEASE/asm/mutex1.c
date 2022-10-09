/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mutex1
 * @created     : Duminică Sep 11, 2022 22:14:09 EEST
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <sys/_pthread/_pthread_cond_t.h>
#endif
#include <unistd.h>

static pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t c1 = PTHREAD_COND_INITIALIZER;
static int cnd = 0;

static void *f1(void *p) {
  (void)p;
  sleep(2);
  {
    cnd = 1;
    pthread_mutex_unlock(&m1);
    /* pthread_cond_broadcast(&c1); */
    pthread_cond_signal(&c1);
  }
  puts("f1\n");

  return NULL;
}

static void *f2(void *p) {
  (void)p;
  sleep(2);
  puts("f2 init\n");

  {
    while (cnd == 0)
      pthread_cond_wait(&c1, &m1);
  }

  sleep(2);
  puts("f2 continue\n");

  return NULL;
}

int main(void) {
  pthread_mutex_lock(&m1);

  pthread_t t1;
  pthread_create(&t1, NULL, f2, NULL);
  f1(NULL);

  pthread_join(t1, NULL);
  puts("now main thread\n");

  pthread_mutex_destroy(&m1);
  pthread_cond_destroy(&c1);
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_cancel(t1);

  return 0;
}
