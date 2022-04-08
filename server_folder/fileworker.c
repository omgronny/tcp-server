#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "fileworker.h"

inline int write_line(const int sockfd, FILE *fp) {
  char buffer[SIZE];
  recv(sockfd, buffer, SIZE, 0);
  if (!strcmp(buffer, "EOF")) {
    return -1;
  }
  fprintf(fp, "%s", buffer);
  bzero(buffer, SIZE);
  return 0;
}

int write_file(const int sockfd, char *directory) {

  int n;
  FILE *fp;
  char filename[SIZE];
  char dir_plus_file[4 * SIZE];

  recv(sockfd, filename, SIZE, 0);
  if (!strlen(filename)) {
    return -1;
  }
  filename[strlen(filename)] = '\0';

  strcpy(dir_plus_file, directory);
  printf("%s %zu\n", filename, strlen(filename));

  strncat(dir_plus_file, filename, strlen(filename));

  fp = fopen(dir_plus_file, "w");
  while (1) {
    if (write_line(sockfd, fp) == -1) {
      break;
    }
  }

  fclose(fp);
  printf("The data was written successfully.\n");
  bzero(filename, SIZE);

  return 0;
}