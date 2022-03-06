/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : opt2
 * @created     : Luni Feb 28, 2022 16:20:01 EET
 */

#include "json-c/json_object.h"
#include "json-c/json_types.h"
#include <curl/curl.h>
#include <json-c/json.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /* socket, connect */
#include <time.h>
#include <unistd.h>

static inline int get_year() {
  struct tm *tm = localtime(&(time_t){time(0)});
  return tm->tm_year + 1900;
}

int parse_json(const char *in) {
  /* char buf[] = */
  /* "{ \"name\": \"xxxxx\", \"Id\": 101, \"Voting_eligible\": true }"; */
  const char *buffer = in;
  json_object *tmp, *obj_name, *obj_date,
      *root_obj = json_tokener_parse(buffer);
#if 0
  obj_name = json_object_object_get(root_obj, "name");
  const char *name = json_object_get_string(obj_name);
  /* printf("Name: %s\n", name); */

  obj_date = json_object_object_get(root_obj, "date");
  const char *date = json_object_get_string(obj_date);

  struct Holiday {
    char name[64], date[64];
    int day, month, year;
  } holiday;
  /* strcpy(holiday.name, name); */
  /* strcpy(holiday.date, date); */
  holiday.day = atoi(date);
  const char *da = (date + 3);
  holiday.month = atoi(da);
  /* printf("Name: %s\n", name); */
  /* printf("Date string: %s\n", holiday.date); */
  printf("day int: %d\n", holiday.day);
  printf("month int: %d\n", holiday.month);

  /*   if (json_object_object_get_ex(root_obj, "name", &tmp)) { */
  /*     // Key Name exists */
  /*     printf("Name: %s\n", json_object_get_string(tmp)); */
  /*     // Name: xxxxx */
  /*     return 0; */
  /*   } */
  /*   /1* printf("\nFOO: %s\n", foo_val); *1/ */
  /*   puts("\nnot found\n"); */
#endif
  json_object *new = json_object_new_object(),
              *jarray = json_object_new_array(),
              *jstring1 = json_object_new_string(in);

  json_object_array_add(jarray, jstring1);
  json_object_object_add(new, "Year", jarray);
  /* printf("The json object created: %s\n", json_object_to_json_string(new));
   */

  json_object *name = json_object_object_get(new, "Year");
  printf("%s\n", json_object_get_string(name));
  return 0;
}

char *get_json() {
  char *response = malloc(4096);
  char *header = "GET /index.html HTTP/1.1\r\nHost: "
                 "www.example.com\r\n\r\n";
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct hostent *server = gethostbyname("www.example.com");
  struct sockaddr_in serv_addr = {.sin_family = AF_INET, .sin_port = htons(80)};
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  int x = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  write(sockfd, header, strlen(header));
  read(sockfd, response, 4096);
  close(sockfd);
  return response;
}

char *get_json2() {
  struct addrinfo hints = {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM},
                  *res;
  char *buf = malloc(2056);
  int x = getaddrinfo("us-central1-romanian-bank-holidays.cloudfunctions.net",
                      "80", &hints, &res);
  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  char *header =
      "GET /romanian_bank_holidays/?year=2022 HTTP/1.1\r\nHost: "
      "us-central1-romanian-bank-holidays.cloudfunctions.net\r\n\r\n";
  send(sockfd, header, strlen(header), 0);
  int received = recv(sockfd, buf, 2056, 0);
  close(sockfd);
  /* printf("%s", buf); */

  /* BUN !!!!*/
  /* char* p = strstr(buf, "name"); */
  /* return p - 3; */
  for (unsigned i = 0; i < received * sizeof(char); i++) {
    if (buf[i] == '[')
      return &buf[i];
    /* return &buf[i + 1]; */
  }
  return NULL;
}

int main(int argc, char **argv) {
  puts("----------\n");
  /* puts(result); */
  /* parse_json(result); */
  /* puts(get_json()); */
  puts(get_json2());
  parse_json(get_json2());
  return 0;
}
