#include "main.h"

#include <stdlib.h>

/*------------------------------------------------------------*/
#ifdef __linux__
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#ifdef LOW_LATENCY
static int pm_qos_fd = -1;
#endif

void
start_low_latency(void)
{
  int target = 0;
  if (pm_qos_fd >= 0) return;
  pm_qos_fd = open("/dev/cpu_dma_latency", O_RDWR);
  write(pm_qos_fd, &target, sizeof(target));
  __asm__ volatile("cli"); // disable interrupts
}

void
stop_low_latency(void)
{
  if (pm_qos_fd >= 0) close(pm_qos_fd);
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
int fd_;
void
init_fd(void)
{
  fd_ = open("log", O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0664);
}
void
close_fd(void)
{
  close(fd_);
}
#endif
/*--------------------------------------------------------------*/

#ifdef CACHE
#include <string.h>
#define FLUSH_CACHE flush_cache();
static void
flush_cache()
{
  char input[1 << 26], output[1 << 26];
  memcpy(output, input, 1 << 26);
}
#else
#define FLUSH_CACHE
#endif

extern int           dayz_in_mon;
extern char          attachment[128];
extern unsigned char arr[32];

int
main(int argc, char* argv[])
{
  INIT_FD

  LOW_LATENCY

  mix();

  init_time(argc, argv);

  get_km(argc > 3 ? argv[argc - 1] : NULL);

  write_excel();

  write_km();

  FLUSH_CACHE

  mail_me(attachment);

  NO_LATENCY

  CLOSE_FD

  return 0;
}
