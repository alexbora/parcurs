/**
 * @author      : alex (alex@T400)
 * @file        : server
 * @created     : miercuri oct 26, 2022 20:49:14 EEST
 */

#include <netinet/in.h>
/* #define _GNU_SOURCE */

#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef __linux__
#include <sys/sendfile.h>
#endif
#include <errno.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef NDEBUG
#define STOP_IF                                                                \
  {}
#else
static FILE *error_log;
static unsigned char error_mode;
#define STOP_IF(assertion, error_action, ...)                                  \
  {                                                                            \
    if (assertion) {                                                           \
      fprintf(error_log ? error_log : stderr, __VA_ARGS__);                    \
      fprintf(error_log ? error_log : stderr, "\n");                           \
      if (error_mode == 'x')                                                   \
        abort();                                                               \
      else {                                                                   \
        error_action;                                                          \
      }                                                                        \
    }                                                                          \
  }
#endif

static pthread_t t1;
static int sock;

static void *foo(void *in) {
  puts("connected\n");

  int sockfd = *(int *)in;

  send(sockfd, "Hello, world!\n", 13, 0);

  char client_request[BUFSIZ];
  recv(sockfd, client_request, 8192, 0);
  printf("client request: %s\n", client_request);
  return NULL;
}

static void getip(int s, int *ip) {
  socklen_t size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  getsockname(s, (struct sockaddr *)&addr, &size);

  char *host = inet_ntoa(addr.sin_addr);
  sscanf(host, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
}

int pollForData(int sock) {
  struct pollfd pollSock;
  pollSock.fd = sock;
  pollSock.events = POLLIN;
  return poll(&pollSock, 1, 10);
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int[]){1}, sizeof(int));

  const struct sockaddr_in server = {.sin_family = AF_INET,
                                     .sin_addr.s_addr = INADDR_ANY,
                                     .sin_port = htons(8080)};

  struct sockaddr_in client;

  int b = bind(sock, (const struct sockaddr *)&server, sizeof(server));

  STOP_IF(b < 0, return EXIT_FAILURE, "could not bind to socket\n");

  listen(sock, 3);
  int conn = 0;
  while (1) {
    conn = accept(sock, (struct sockaddr *)&client,
                  (socklen_t *)(sizeof(struct in_addr)));

    /* const char *reply = "HTTP/1.1 200 OK\n" */
    /*                     "Date: Thu, 19 Feb 2009 12:27:04 GMT\n" */
    /*                     "Server: Apache/2.2.3\n" */
    /*                     "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n" */
    /*                     "ETag: \"56d-9989200-1132c580\"\n" */
    /*                     "Content-Type: text/html\n" */
    /*                     "Content-Length: 15\n" */
    /*                     "Accept-Ranges: bytes\n" */
    /*                     "Connection: close\n" */
    /*                     "\n" */
    /*                     "sdfkjsdnbfkjbsf"; */
    /* send(conn, reply, strlen(reply), 0); */
    /* char buf[2048]; */
    /* memset(buf, '\0', 2048); */
    /* read(conn, buf, 2048); */
    /* puts(buf); */
    /* write(conn, "200 \r\n", 6); */

    printf("server: got connection from %s port %d\n",
           inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    send(conn, "Hello, world!\n", 13, 0);

    char c_msg[256];
    read(conn, c_msg, 255);
    printf("Here is the message: %s\n", c_msg);

    const char *response =
        "HTTP/1.1 200 OK\r\nStatus: 200 OK\r\nContent-Length: "
        "0\r\nContent-Type: text/plain\r\n\r\n";

    /* sendto(sock, response, strlen(response), 0, (struct sockaddr *)&client,
     */
    /* (socklen_t)(sizeof(struct in_addr))); */

    write(conn, response, strlen(response));

    time_t tim = time(0);
    struct tm tm1 = *localtime(&tim);
    send(conn, asctime(&tm1), 16, 0);

    /* int ip[4]; */
    /* getip(sock, ip); */
    /* printf("Connection from: [%d.%d.%d.%d]\n", ip[0], ip[1], ip[2], ip[3]);
     */
    /* if (conn) { */
    pthread_create(&t1, NULL, foo, &conn);
    pthread_join(t1, NULL);
    /* int pid = fork(); */
    /* } */
  }

  shutdown(conn, 2);
  close(conn);
  shutdown(sock, 2);
  close(sock);

  return EXIT_SUCCESS;
}
