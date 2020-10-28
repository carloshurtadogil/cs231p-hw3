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
  struct sockaddr_in servaddr, cli;

  len = sizeof(cli);
  sock = socket(AF_INET, SOCK_STREAM, 0); // create socket for intramachine use
  if (sock == -1) {
    printf("Failed to create socket...\n");
    exit(0);
  }
  printf("Socket created successfully...\n");

  bzero(&servaddr, sizeof(servaddr)); // set values to 0

  // setup IP address and PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  // bind socket to a given IP address
  if ((bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
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
  connection = accept(sock, (struct sockaddr*)&cli, &len);
  if(connection < 0) {
    printf("Failed to connect with client...\n");
    close(sock);
    exit(0);
  }
  printf("Client accepted...\n");
  
  // begin communicating with the client
  communicate(connection);

  close(sock); // close socket
  exit(1);
}

/**
 * Communicate with a client via a connecting socket
 * 
 * @param connection Accepted data packet from client
*/
void communicate(int connection) {
  char buf[BUFFSIZE]; // array to store content of received message
  char response[] = "Message Received";
  int responseSize = sizeof(response);
  bool running = true;

  while(running) {
    bzero(buf, BUFFSIZE); // set all array values to 0

    read(connection, buf, sizeof(buf)); // read client message and store in buf
    printf("Buffer content: %s\n", buf);
    
    write(connection, response, responseSize); // send response to client
    
    // Client command to shutdown server
    if(strncmp("exit", buf, 4) == 0) {
      printf("Exiting server...\n");
      running = false;
    }
  }
}
