#include <stdio.h> 
#include <errno.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080

int main(int argc, char const * argv[]) {
    int sock = 0, valread;
    char *hello = "Hello from client";
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("\n Socket create failed \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    if (inet_pton(AF_INET, "192.168.100.4", &serv_addr.sin_addr) <= 0){
        printf("\n invalid address \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        printf("\n failed to connect %s \n", strerror(errno));
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    valread = read(sock, buffer, 1024);
    printf("Got message: %s\n", buffer);
    return 0;
}
