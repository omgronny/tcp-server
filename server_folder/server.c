#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "routine.h"

#define SIZE 1024

int main(int argc, char *argv[]) {

  int port = 8087;
  int socket_fd;
  const char *ip = "127.0.0.1";
  char directory[SIZE];

  if (argc > 1) {
    port = atoi(argv[1]);
  }

  if (argc > 2) {
    strcpy(directory, argv[2]);
    strcat(directory, "/\0");
    printf("%s\n", directory);
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = port;
  address.sin_addr.s_addr = inet_addr(ip);

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  printf("Server socket created successfully\n");

  if (bind(socket_fd, (struct sockaddr *)&address, sizeof address) == -1) {
    perror("bind");
    exit(1);
  }

  if (listen(socket_fd, 10) == -1) {
    perror("listen");
    exit(1);
  }
  printf("Listening...\n");

  while (1) {
    init_thread_and_start(socket_fd, directory);
  }

  return 0;
}