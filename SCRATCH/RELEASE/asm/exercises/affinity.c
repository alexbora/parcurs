/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : affinity
 * @created     : Vineri Iul 08, 2022 19:09:26 EEST
 */

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_t.h>

void SetThreadAffinity(pthread_t *t, int cpu);
#if __APPLE__
#include <mach/mach.h>
#include <mach/thread_act.h>
#include <sched.h>
#endif

void SetThreadAffinity(pthread_t *t, int cpu)
{
  thread_affinity_policy_data_t policy = {cpu};
  thread_policy_set(pthread_mach_thread_np(t->native_handle()),
                    THREAD_AFFINITY_POLICY, (thread_policy_t)&policy, 1);
}
