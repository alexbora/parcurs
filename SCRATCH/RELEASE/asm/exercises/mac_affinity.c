/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : mac_affinity
 * @created     : Sâmbătă Iul 09, 2022 07:57:14 EEST
 */

#include <mach/mach.h>
#include <mach/thread_act.h>
#include <pthread.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_t.h>
#include <sys/sysctl.h>
#include <sys/types.h>

#define SYSCTL_CORE_COUNT "machdep.cpu.core_count"

typedef struct cpu_set {
  uint32_t count;
} cpu_set_t;

static inline void CPU_ZERO(cpu_set_t *cs)
{
  cs->count = 0;
}

static inline void CPU_SET(int num, cpu_set_t *cs)
{
  cs->count |= (1 << num);
}

static inline int CPU_ISSET(int num, cpu_set_t *cs)
{
  return (cs->count & (1 << num));
}

int sched_getaffinity(cpu_set_t *cpu_set)
{
  int32_t core_count = 0;
  size_t  len        = sizeof(core_count);
  int     ret        = sysctlbyname(SYSCTL_CORE_COUNT, &core_count, &len, 0, 0);
  if (ret) {
    printf("error while get core count %d\n", ret);
    return -1;
  }
  cpu_set->count = 0;
  for (int i = 0; i < core_count; i++) {
    cpu_set->count |= (1 << i);
  }

  return 0;
}

int pthread_setaffinity_np(pthread_t thread)
{
  thread_port_t mach_thread;
  int           core = 0;

  thread_affinity_policy_data_t policy = {core};
  mach_thread                          = pthread_mach_thread_np(thread);
  thread_policy_set(mach_thread, THREAD_AFFINITY_POLICY,
                    (thread_policy_t)&policy, 1);
  return 0;
}

int main(int argc, char *argv[])
{
  pthread_t t1 = NULL;
  pthread_setaffinity_np(t1);
  cpu_set_t cpu_set;
  sched_getaffinity(&cpu_set);
  printf("%d\n", cpu_set.count);

  return 0;
}
