/*
    Author : Dibakar Patar
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define max 1024

int main(){
    
    int sfd, number, rcv;
    char buff[max];
    
    struct sockaddr_in s_addr;
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    socklen_t addr_len = sizeof(s_addr);
    
    if(connect(sfd, (struct sockaddr *)&s_addr, addr_len) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    
    printf("\nEnter the number : ");
    scanf("%d", &number);
    
    
    
    if(send(sfd, &number, sizeof(number),  0) < 0) {
        perror("Sending error");
        exit(EXIT_FAILURE);
    }
    
    if((rcv = recv(sfd, buff, sizeof(buff), 0)) < 0) {
        perror("Receiving failed");
        exit(EXIT_FAILURE);
    }
    buff[rcv] = '\0';
    
    printf("\nServer -> %s\n", buff);
    
    close(sfd);
    
    return 0;
    
}
