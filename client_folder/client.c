#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fileworker.h"

int main(int argc, char *argv[]) {

  const char *ip = "127.0.0.1";
  int port = 8087;
  int sockfd;

  if (argc > 1) {
    ip = argv[1];
  }

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Error in socket");
    exit(1);
  }

  printf("Server socket created successfully\n");

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("Error in socket");
    exit(1);
  }
  printf("Connected to Server\n");

  while (1) {
    send_file(sockfd);
  }

  printf("Closing the connection\n");
  close(sockfd);

  return 0;
}