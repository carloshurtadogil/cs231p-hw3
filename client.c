#include <stdio.h> 
#include <errno.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080
#define SERVER_ADDR "192.168.100.4"

int main(int argc, char const * argv[]) {
    // The fd of the yet to be created socket.
    int socket_fd = 0;
    // The message we will send.
    char *hello = "Hello from client";
    // A struct to hold data about the server to which we will connect.
    struct sockaddr_in serv_addr;
    // A buffer to hold incoming data.
    char buffer[1024] = {0};

    // Create a socket that can talk over ipv4 using TCP.
    // 0 implies automatic protocol choice, but SOCK_STREAM makes that be TCP.
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("Socket creation failed... \n");
        close(socket_fd);
        return -1;
    }

    // Set up server information to be ipv4 and the desired server port.
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Correctly format server ip address and place it in serv_addr,
    if (inet_pton(AF_INET, SERVER_ADDR, &serv_addr.sin_addr) <= 0){
        printf("Invalid server address... \n");
        close(socket_fd);
        return -1;
    }

    // Attempt to establish a connection between our socket_fd and the server.
    if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        printf("Failed to connect to server... %s \n", strerror(errno));
        close(socket_fd);
        return -1;
    }
    
    // Send the string message.
    send(socket_fd, hello, strlen(hello), 0);
    printf("Sent message: %s\n", hello);
    // Receive a message back from the server.
    int bytes_read = recv(socket_fd, buffer, 1024, 0);
    printf("Got message: %s\n", buffer);
    close(socket_fd);
    return 0;
}
