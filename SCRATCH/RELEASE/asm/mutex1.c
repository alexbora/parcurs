/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mutex1
 * @created     : Duminică Sep 11, 2022 22:14:09 EEST
 */

#include <pthread.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>

int main(int argc, char *argv[])
{
  pthread_mutex_t *mtx = NULL;
  pthread_mutex_init(mtx, NULL);
  return 0;
}
