#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IP 100

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "expects atleast one argument");
    return 1;
  }

  char *host = argv[1];

  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET6_ADDRSTRLEN];
  char visited[MAX_IP][INET6_ADDRSTRLEN];
  int count = 0;

  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_UNSPEC;

  if ((status = getaddrinfo(host, NULL, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
  }

  printf("The Ip addresses for host:%s\n", host);

  for (p = res; p != NULL; p = p->ai_next) {
    void *addr;
    char *ipver;

    if (p->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);

    int is_visited = 1;
    for (int i = 0; i < count; ++i) {
      if (strcmp(ipstr, visited[i]) == 0) {
        is_visited = 0;
        break;
      }
    }

    if (is_visited && count < MAX_IP) {
      strcpy(visited[count], ipstr);
      printf("%s: %s\n", ipver, ipstr);
      count++;
    }
  }

  freeaddrinfo(res);
  return 0;
}
