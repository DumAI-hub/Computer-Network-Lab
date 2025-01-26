/*
    Author : Dibakar Patar
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

#define max 1024
#define PORT_NUMBER 4000
#define INET_ADDR "192.168.127.98"

int main() {
    int socket_fd, cfd, rd, slen;
    char buff[max];
    
    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation failed");
        exit(0);
    }
    
    struct sockaddr_in s;
    
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT_NUMBER);
    s.sin_addr.s_addr = inet_addr(INET_ADDR);
    
    slen = sizeof(s);
    
    if((cfd = connect(socket_fd, (struct sockaddr *)&s, slen)) < 0){
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }
    
    if((rd = read(socket_fd, buff, sizeof(buff))) < 0) {
        perror("Recieving error");
        exit(EXIT_FAILURE);
    }
    
    buff[rd] = '\0';
    
    printf("\nServer -> %s\n", buff);
    
    close(socket_fd);
    close(cfd);
    close(rd);
    
}