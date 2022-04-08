#ifndef ROUTINE
#define ROUTINE

#include <pthread.h>
#include <netinet/in.h>

typedef struct consumer_arguments {
  int new_socket_fd;
  struct sockaddr_in client_address;
  char* directory;
} consumer_arguments;


int init_thread_and_start(const int socket_fd, char* directory);

#endif // ROUTINE