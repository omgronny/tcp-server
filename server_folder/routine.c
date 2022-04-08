#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fileworker.h"
#include "routine.h"

void *consumer_routine(void *arg) {

  consumer_arguments *pthread_arg = (consumer_arguments *)arg;
  int new_socket_fd = pthread_arg->new_socket_fd;
  struct sockaddr_in client_address = pthread_arg->client_address;
  char *directory = pthread_arg->directory;

  while (1) {
    if (write_file(new_socket_fd, directory) == -1) {
      break;
    }
  }

  close(new_socket_fd);
  return NULL;
}

int init_thread_and_start(const int socket_fd, char *directory) {

  pthread_t consumer;
  consumer_arguments *pthread_arg =
      (consumer_arguments *)malloc(sizeof *pthread_arg);
  socklen_t client_address_len = sizeof(struct sockaddr_in);
  pthread_arg->directory = directory;

  int new_socket_fd =
      accept(socket_fd, (struct sockaddr *)&pthread_arg->client_address,
             &client_address_len);
  if (new_socket_fd == -1) {
    perror("accept");
    free(pthread_arg);
    return -1;
  }
  pthread_arg->new_socket_fd = new_socket_fd;

  pthread_create(&consumer, NULL, consumer_routine, (void *)pthread_arg);

  return 1;
}