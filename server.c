#include <stdio.h> 
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080 
#define BUFFSIZE 512

void communicate(int);

int main(int argc, char const *argv[]) {
  int socket_fd, connection_fd, len;
  struct sockaddr_in serveraddr, clientaddr;
  int addr_len = sizeof(struct sockaddr_in);
  int res = 0;


  socket_fd = socket(AF_INET, SOCK_STREAM, 0); // create socket
  if (socket_fd == -1) {
    printf("Failed to create socket...\n");
    return 0;
  }
  printf("Socket created successfully...\n");

  // setup IP address and PORT
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(PORT);
  

  // bind socket to a given IP address
  res = bind(socket_fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
  if (res < 0) {
    printf("Failed to bind socket...\n");
    close(socket_fd);
    return 0;
  }
  printf("Socket bound successfully...\n");
  
  // Set server to start listening for client
  res = listen(socket_fd, 1);
  if (res == -1) {
    printf("Server failed to listen...\n");
    close(socket_fd);
    return 0;
  }
  printf("Server is listening...\n");

  // Accept data packet from a client
  connection_fd = accept(socket_fd, (struct sockaddr*)&clientaddr, &addr_len);
  if (connection_fd < 0) {
    printf("Failed to connect with client...\n");
    close(socket_fd);
    return 0;
  }
  printf("Client accepted...\n");
  
  char buffer[1024];
  int bytes_read = recv(connection_fd, buffer, 1024, 0);
  printf("Got message from client: %s\n", buffer);
  char * response = "Message Received";
  send(connection_fd, response, strlen(response), 0);
  printf("Responded with: %s\n", response);
  
  close(socket_fd); // close socket
  return 0;
}

