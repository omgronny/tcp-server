#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

void send_file(int sockfd) {

  printf("%s", "Enter name of the file\n");	
  char filename[SIZE] = "";
  fgets(filename, SIZE, stdin);
  filename[strlen(filename) - 1] = '\0';

  send(sockfd, filename, sizeof(filename), 0);

  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }

  int n;
  char data[SIZE] = {0};

  memset(&data, '\0', sizeof(data));
  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }

  printf("[+]File data sent successfully.\n");
  
  memset(&data, '\0', sizeof(data));
  
//   if (recv(sockfd, data, SIZE, 0) < 0) {
//     perror("[-]Error in reading response.");
//     exit(1);
//   }

//   printf("%s", data);

  bzero(data, SIZE);

}

void request(int sockfd) {
  while (1) {
	send_file(sockfd);
	}
}

int main(){
  char *ip = "127.0.0.1";
  int port = 8087;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
	printf("[+]Connected to Server.\n");

  // можно запустить беск цикл общения прямо внутри send'a 
  // точнее сделать обертку над send и в нем крутиться

	request(sockfd);

	printf("[+]Closing the connection.\n");
  close(sockfd);

  return 0;
}