/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : err
 * @created     : Sâmbătă Sep 24, 2022 08:48:30 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_ssize_t.h>
#include <unistd.h>
#define TOR_SIGSAFE_LOG_MAX_FDS 4

static int sigsafe_log_fds[TOR_SIGSAFE_LOG_MAX_FDS] = {STDERR_FILENO};
static int n_sigsafe_log_fds                        = 1;

static int tor_log_err_sigsafe_write(const char s[static 1])
{
  size_t len = strlen(s);
  int    err = 0;
  for (int i = 0; i < n_sigsafe_log_fds; ++i) {
    ssize_t r = write(sigsafe_log_fds[i], s, len);
    err += (r != (ssize_t)len);
  }
  printf(" -- %d\n", err);
  return err ? -1 : 0;
}

int main(int argc, char *argv[])
{
  tor_log_err_sigsafe_write("text");
  return 0;
}
