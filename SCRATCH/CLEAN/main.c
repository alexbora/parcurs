#include "main.h"

#include <stdlib.h>

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
}

void stop_low_latency(void)
{
  if (pm_qos_fd >= 0)
    close(pm_qos_fd);
}
#endif

#ifdef __linux__
#define LOW_LATENCY start_low_latency();
#define NO_LATENCY  stop_low_latency();
#else
#define LOW_LATENCY
#define NO_LATENCY
#endif

extern int           dayz_in_mon;
extern char          attachment[128];
extern unsigned char arr[32];

int main(int argc, char *argv[])
{

  LOW_LATENCY

  init_time(argc, argv);

  mix();

  get_km(argc > 3 ? argv[argc - 1] : NULL);

  write_excel();

  write_km();

  mail_me(attachment);

  NO_LATENCY

  return 0;
}
