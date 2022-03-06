/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : opt2
 * @created     : Luni Feb 28, 2022 16:20:01 EET
 */

#include <json-c/json.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>
#define _GNU_SOURCE  // cause stdio.h to include vasprintf #include <stdio.h>
                     // //printf, vasprintf
#include <assert.h>
#include <stdlib.h>  //system
#define System_w_printf(outval, ...)            \
  {                                             \
    char* string_for_systemf;                   \
    asprintf(&string_for_systemf, __VA_ARGS__); \
    outval = system(string_for_systemf);        \
    free(string_for_systemf);                   \
  }

#include <curl/curl.h>
#include <stddef.h>
#include <time.h>

struct Mem {
  char *in, *out;
};

static void callback(void* in, size_t size, size_t nmemb, void* user) {
  /* strcpy(in, out); */
  /* printf("OUT: %s\n", in); */
  /* struct Mem* p = (struct Mem*)user; */
  char** p = (char**)user;
  /* *p = strndup(in, (size_t)(size * nmemb)); */
  memcpy(*p, in, nmemb);
  /* *p = strndup((char*)in, strlen((char*)in)); */
  /* strcpy(*p, in); */
  /* strcpy((char*)user, in); */
}

static char* fetch(int year) {
  const char* url =
      "https://us-central1-romanian-bank-holidays.cloudfunctions.net/"
      "romanian_bank_holidays/?year=";
  char destination[128];
  char* result = malloc(1024);
  strcpy(destination, url);
  sprintf(destination + strlen(url), "%d", year);
  /* memcpy(destination + strlen(url), "2023", 4); */
  /* printf("%s\n", destination); */

  /* struct Mem chunk = {malloc(1024), malloc(1024)}; */

  CURL* curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, destination);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&result);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return result;
}

static inline int get_year() {
  struct tm* tm = localtime(&(time_t){time(0)});
  return tm->tm_year + 1900;
}

int parse_json(const char* in) {
  /* char buf[] = */
  /* "{ \"name\": \"xxxxx\", \"Id\": 101, \"Voting_eligible\": true }"; */
  const char* buffer = in;
  json_object *tmp, *obj_name, *obj_date,
      *root_obj = json_tokener_parse(buffer);

  obj_name = json_object_object_get(root_obj, "name");
  const char* name = json_object_get_string(obj_name);
  /* printf("Name: %s\n", name); */

  obj_date = json_object_object_get(root_obj, "date");
  const char* date = json_object_get_string(obj_date);

  struct Holiday {
    char name[64], date[64];
    int day, month, year;
  } holiday;
  /* strcpy(holiday.name, name); */
  /* strcpy(holiday.date, date); */
  holiday.day = atoi(date);
  const char* da = (date + 3);
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
  return 0;
}

char* get_json() {
  char* response = malloc(4096);
  char* header =
      "GET /index.html HTTP/1.1\r\nHost: "
      "www.example.com\r\n\r\n";
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct hostent* server = gethostbyname("www.example.com");
  struct sockaddr_in serv_addr = {.sin_family = AF_INET, .sin_port = htons(80)};
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  int x = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  write(sockfd, header, strlen(header));
  read(sockfd, response, 4096);
  close(sockfd);
  return response;
}

char* get_json2() {
  struct addrinfo hints = {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM},
                  *res;
  char* buf = malloc(2056);
  /* buf[0] = '\0'; */
  int x = getaddrinfo("us-central1-romanian-bank-holidays.cloudfunctions.net",
                      "80", &hints, &res);
  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  char* header =
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
    if (buf[i] == '[') return &buf[i + 1];
  }
  return NULL;
}

int main(int argc, char** argv) {
  char* result = fetch(get_year());
  puts("----------\n");
  /* puts(result); */
  /* parse_json(result); */
  free(result);
  /* puts(get_json()); */
  puts(get_json2());
  parse_json(get_json2());

  struct H {
    int year;
    int days[2];
  } h[] = {get_year(), {1, 1}};

  return 0;
  /* assert(argc == 2); */

  int out;
  /* System_w_printf(out, "ls %s", argv[1]) return out; */

  struct Data {
    int a, b;
    char* z;
  } data = {7, 8, "z"};

  int x = offsetof(struct Data, b);
  char* p = (char*)&data;
  int y = *(int*)(p + x);  // 4
  printf("%d\n", y);

  int zp = offsetof(struct Data, z);
  char** pz = (char**)(p + zp);
  printf("%s\n", *pz);

#define pointcontents \
  { double x, y; }
  struct pointcontents point;

  typedef struct list {
    char* title;
    char** songs;
    void (*print)(struct list*);
  } list;

  list l1 = {"title", (char*[]){"a", "b", "c"}, NULL};

  int cores = system("sysctl hw.logicalcpu");
  printf("cores: %d\n", cores);
  return 0;
}
