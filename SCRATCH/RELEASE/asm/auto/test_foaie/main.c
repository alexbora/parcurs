#include "main.h"

#include <pthread.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <sys/_pthread/_pthread_types.h>
#endif
/*------------------------------------------------------------*/
#ifdef __linux__
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

static int pm_qos_fd = -1;

void start_low_latency(void)
{
  int target = 0;
  if (pm_qos_fd >= 0)
    return;
  pm_qos_fd = open("/dev/cpu_dma_latency", O_RDWR);
  write(pm_qos_fd, &target, sizeof(target));
  /* __asm__ volatile("cli"); // disable interrupts */
}

void stop_low_latency(void)
{
  if (pm_qos_fd >= 0)
    close(pm_qos_fd);
  __asm__ volatile("sti");
}

#define LOW_LATENCY start_low_latency();
#define NO_LATENCY  stop_low_latency();
#else
#define LOW_LATENCY
#define NO_LATENCY
#endif
/*-------------------------------------------------------------*/
#ifdef LOG
int  fd_;
void init_fd(void)
{
  fd_ = open("log", O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0664);
}
void close_fd(void)
{
  close(fd_);
}
#endif
/*--------------------------------------------------------------*/

#ifdef CACHE
#include <string.h>
#define FLUSH_CACHE flush_cache();
static void flush_cache()
{
  char input[1 << 26], output[1 << 26];
  memcpy(output, input, 1 << 26);
}
#else
#define FLUSH_CACHE
#endif

extern int dayz_in_mon;
char       attachment[128];
/* extern char          attachment[128]; */
extern unsigned char arr[32];
#ifdef USE_ASM
extern void inline check_alignment(void);
#endif

#ifndef USE_ASM
#define CHECK_ALIGNMENT()                                                      \
  __asm__ inline("pushf\n"                                                     \
                 "orl $0x40000, (%rsp)\n"                                      \
                 "popf");
#endif
#ifndef USE_ASM
#define CHECK_ALIGNMENT2()                                                     \
  __asm__ inline("pushq %rax\n"                                                \
                 "lahf\n"                                                      \
                 "orq $0x4, %rax\n"                                            \
                 "sahf\n"                                                      \
                 "popq %rax\n");
#endif

void *send_mail(void *p)
{
  (void)p;
  mail_me();
  return NULL;
}

unsigned        cond = 0;
pthread_mutex_t m1   = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  c1   = PTHREAD_COND_INITIALIZER;
pthread_t       t1;

int main(int argc, char *argv[])
{

  pthread_mutex_lock(&m1);
  pthread_create(&t1, NULL, send_mail, NULL);

  /* __asm__("pushf\n" */
  /*         "orl $0x40000, (%rsp)\n" */
  /*         "popf"); */

  /* __asm__("pushq %rax\n" */
  /*         "lahf\n" */
  /*         "orq $0x4, %rax\n" */
  /*         "sahf\n" */
  /*         "popq %rax\n"); */

#ifdef USE_ASM
  check_alignment();
#else
  /* CHECK_ALIGNMENT2(); */
#endif

  INIT_FD

  /* LOW_LATENCY */

  mix();

  init_time(argc, argv);

  get_km(argc > 3 ? argv[argc - 1] : NULL);

  write_excel();
  cond = 1;
  pthread_cond_signal(&c1);
  pthread_cond_destroy(&c1);
  pthread_join(t1, NULL);
  pthread_cancel(t1);

  write_km();

  /* FLUSH_CACHE */
  mail_me();

  /* NO_LATENCY */

  CLOSE_FD

  return 0;
}