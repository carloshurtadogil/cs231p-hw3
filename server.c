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
  int sock, connection, len;
  struct sockaddr_in serveraddr, clientaddr;
  int opt = 1;

  len = sizeof(serveraddr);
  sock = socket(AF_INET, SOCK_STREAM, 0); // create socket
  if (sock == -1) {
    printf("Failed to create socket...\n");
    exit(0);
  }

  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
  { 
      perror("setsockopt"); 
      exit(EXIT_FAILURE); 
  }
  printf("Socket created successfully...\n");

  bzero(&serveraddr, sizeof(serveraddr)); // set values to 0

  // setup IP address and PORT
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(PORT);

  // bind socket to a given IP address
  if ((bind(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr))) < 0) {
    printf("Failed to bind socket...\n");
    close(sock);
    exit(0);
  }
  printf("Socket binded successfully...\n");
  
  // Set server to start listening for client
  if (listen(sock, 1) == -1) {
    printf("Server failed to listen...\n");
    close(sock);
    exit(0);
  }
  printf("Server is listening...\n");

  // Accept data packet from a client
  connection = accept(sock, (struct sockaddr*)&serveraddr, &len);
  if(connection < 0) {
    printf("Failed to connect with client...\n");
    close(sock);
    exit(0);
  }
  printf("Client accepted...\n");
  
  char buffer[1024];
  int valread = read(connection, buffer, 1024);
  printf("%s\n", buffer);
  char *response = "Message Reveived";
  send(connection, response, strlen(response), 0);
  printf("Responded\n");
  return 0;

  // begin communicating with the client
  communicate(connection);

  close(sock); // close socket
  exit(1);
}

