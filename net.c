#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Hello World");

  struct sockaddr_in sa;

  inet_pton(AF_INET, "10.12.100.57", &(sa.sin_addr));
  char ip4[INET_ADDRSTRLEN];

  inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

  printf("The IPv4 address is: %s\n", ip4);
}
