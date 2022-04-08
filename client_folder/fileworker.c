#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileworker.h"

int read_name_of_file(char filename[SIZE]) {
  fgets(filename, SIZE, stdin);

  if (strlen(filename) == 1) {
    return -1;
  }
  filename[strlen(filename) - 1] = '\0';
  return 1;
}

void send_file(const int sockfd) {

  printf("%s", "Enter the name of the file (on server)\n");
  char filename[SIZE] = "";
  read_name_of_file(filename);
  send(sockfd, filename, sizeof(filename), 0);

  printf("%s", "Enter the name of the file (local)\n");
  read_name_of_file(filename);

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