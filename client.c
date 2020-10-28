#include <stdio.h> 
#include <errno.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080
#define SERVER_ADDR "192.168.100.4"

int main(int argc, char const * argv[]) {
    int socket_fd = 0;
    char *hello = "Hello from client";
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("Socket creation failed... \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Set up server address format
    if (inet_pton(AF_INET, SERVER_ADDR, &serv_addr.sin_addr) <= 0){
        printf("Invalid server address... \n");
        return -1;
    }

    if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        printf("Failed to connect to server... %s \n", strerror(errno));
        return -1;
    }
    send(socket_fd, hello, strlen(hello), 0);
    printf("Sent message: %s\n", hello);
    int bytes_read = recv(socket_fd, buffer, 1024, 0);
    printf("Got message: %s\n", buffer);
    return 0;
}
