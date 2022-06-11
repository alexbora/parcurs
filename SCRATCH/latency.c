/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : latency
 * @created     : sâmbătă iun 11, 2022 21:02:00 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int target = 0;
  int fd = open("/dev/cpu_dma_latency", O_RDWR);
  write(fd, &target, sizeof(target));
  return 0;
}

static int pm_qos_fd = -1;

void start_low_latency(void) {
  s32_t target = 0;

  if (pm_qos_fd >= 0)
    return;
  pm_qos_fd = open("/dev/cpu_dma_latency", O_RDWR);
  if (pm_qos_fd < 0) {
    fprintf(stderr, "Failed to open PM QOS file: %s", strerror(errno));
    exit(errno);
  }
  write(pm_qos_fd, &target, sizeof(target));
}

void stop_low_latency(void) {
  if (pm_qos_fd >= 0)
    close(pm_qos_fd);
}
