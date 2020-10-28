#include <stdio.h> 
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <unistd.h>
#define PORT 8080 
#define SA struct sockaddr

void setup();

int main(int argc, char const *argv[]) {
  printf("Hello world\n");
  setup();
}

void setup() {
  int socket_fd, connection, len;
  struct sockaddr_in servaddr, cli;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0); // create socket for intramachine use
  if (socket_fd == -1) {
    printf("Failed to create socket...\n");
    exit(0);
  }

  printf("Socket created successfully...\n");
  bzero(&servaddr, sizeof(servaddr));

  // initialize IP address and PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  if ((bind(socket_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) { // bind socket
    printf("Failed to bind socket...\n");
    exit(0);
  }
  printf("Socket binded successfully...\n");
  

  close(socket_fd);
}

