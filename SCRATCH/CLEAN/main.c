#include "main.h"

#include <stdlib.h>

/*------------------------------------------------------------*/
#ifdef __linux__
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

static int pm_qos_fd = -1;

void
start_low_latency(void)
{
  int target = 0;
  if (pm_qos_fd >= 0) return;
  pm_qos_fd = open("/dev/cpu_dma_latency", O_RDWR);
  write(pm_qos_fd, &target, sizeof(target));
}

void
stop_low_latency(void)
{
  if (pm_qos_fd >= 0) close(pm_qos_fd);
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

extern int           dayz_in_mon;
extern char          attachment[128];
extern unsigned char arr[32];

#ifndef USE_GUI
int
main(int argc, char** argv)
{

  INIT_FD

  LOW_LATENCY
  mix();

  init_time(argc, argv);

  get_km(argc > 3 ? argv[argc - 1] : NULL);

  write_excel();

  write_km();

  mail_me(attachment);

  NO_LATENCY

  CLOSE_FD

  return 0;
}

#else
size_t
write(int, const void*, size_t);
#include <stdio.h>
int
mainx(void* p)
{

  char** argv = (char**) p;
  /* argv[0]     = "iun"; */
  argv[1] = "22";
  argv[2] = "100";
  init_time(3, argv);

  /*   struct Data { */
  /*     const char* txt; */
  /*     int         len; */
  /*   }; */
  /*   struct Data* data = (struct Data*) p; */
  /*   write(1, data->txt, data->len); */
  /*   write(1, "\n", 1); */

  return 0;
}
#endif
