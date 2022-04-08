#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

void write_file(int sockfd) {
  int n;
  FILE *fp;
  char filename[SIZE];
  char buffer[SIZE];

  recv(sockfd, filename, SIZE, 0);
  filename[strlen(filename)] = '\0';

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0) {
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
	printf("[+]Data written in the file successfully.\n");
    bzero(buffer, SIZE);
  }

  printf("[+]Data written in the file successfully.\n");

  char data[1024] = "recieved\n";

	if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);

  return;
}

void response(int sockfd) {
  while (1) {
  	write_file(sockfd);
  }
}


int main(){
  char *ip = "127.0.0.1";
  int port = 8087;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");

  if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		perror("[-]Error in listening");
    exit(1);
	}

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

  response(new_sock);

  return 0;
}