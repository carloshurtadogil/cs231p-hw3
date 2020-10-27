#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

void setup();

int main(int argc, char const *argv[]) {
  printf("Hello world\n");
  setup();
}

void setup() {
  int socket_fd, connection, len;
  struct sockaddr_in server_addr, cli;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    printf("Failed to create socket...\n");
    exit(0);
  }

  printf("Socket created successfully...\n");
  bzero(&server_addr, sizeof(server_addr));

  close(socket_fd);
}

