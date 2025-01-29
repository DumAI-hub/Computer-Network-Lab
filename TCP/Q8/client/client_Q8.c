/*
    Author : Dibakar Patar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define max 1024
#define PORT 4000

int main() {
    int sfd, rcv;
    char source_file[max], dest_file[max], buff[max];
    
    struct sockaddr_in s_addr;
    socklen_t addr_len;
    
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    
    if(connect(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
        perror("Connection to server failed");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    
    printf("\nEnter the source filename : ");
    scanf(" %s", source_file);
    
    printf("\nEnter the destination filename : ");
    scanf(" %s", dest_file);
    
    if(send(sfd, source_file, strlen(source_file), 0) < 0) {
        perror("source filename Send failed");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    
    if(send(sfd, dest_file, strlen(dest_file), 0) < 0) {
        perror("destination filename Send failed");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    
    if((rcv = recv(sfd, buff, sizeof(buff), 0)) < 0 ) {
        perror("Receiving error");
        exit(EXIT_FAILURE);
    }else {
        printf("\nServer -> %s\n", buff);
    }
    
    if(strcmp(buff, "Source file not found") != 0 && strcmp(buff, "Cannot create destination file") != 0) {
        recv(sfd, buff, sizeof(buff), 0);
        printf("\nServer -> %s", buff);
    }
    
    
    close(sfd);

    return 0;
    
}