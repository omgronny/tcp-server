#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileworker.h"

void send_file(const int sockfd) {

  printf("%s", "Enter the name of the file\n");
  char filename[SIZE] = "";
  fgets(filename, SIZE, stdin);

  if (strlen(filename) == 1) {
    return;
  }
  filename[strlen(filename) - 1] = '\0';

  send(sockfd, filename, sizeof(filename), 0);

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error in reading file");
    return;
  }
  int n;
  char data[SIZE] = {0};

  memset(&data, '\0', sizeof(data));
  while (fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("Error in sending file");
      exit(1);
    }
    bzero(data, SIZE);
  }
  char enddata[SIZE] = "EOF";
  send(sockfd, enddata, sizeof(enddata), 0);
  fclose(fp);

  printf("File data sent successfully\n");

  memset(&data, '\0', sizeof(data));
  bzero(data, SIZE);
}