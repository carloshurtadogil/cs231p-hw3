#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
#define SA struct sockaddr

void setup();

int main(int argc, char const *argv[]) {
  printf("Hello world\n");
  setup();
}

void setup() {
  int socket_fd, connection, len;
  struct sockaddr_un servaddr, cli;

  socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0); // create socket for intramachine use
  if (socket_fd == -1) {
    printf("Failed to create socket...\n");
    exit(0);
  }

  printf("Socket created successfully...\n");
  bzero(&servaddr, sizeof(servaddr));

  // initialize IP address and PORT
  servaddr.sun_family = AF_UNIX;
  servaddr.sun_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sun_port = htons(PORT);

  if ((bind(socket_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) { // bind socket
    printf("Failed to bind socket...\n");
    exit(0);
  }
  printf("Socket binded successfully...\n");
  

  close(socket_fd);
}

