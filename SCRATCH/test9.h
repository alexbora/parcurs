#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

#ifdef LOG
extern int fd;
#define INIT_FD init_fd();
#define CLOSE_FD close_fd();
void init_fd(void);
void close_fd(void);

#else
#define INIT_FD
#define CLOSE_FD
#define fd 2
#endif

#define PRINT_(a) write(fd, a, strlen(a));

void f1(void);
