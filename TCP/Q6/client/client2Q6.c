/*
    Author : Dibakar Patar
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define max 1024
#define PORT 4000




int main(){
    int sfd, cfd, rcv, slen;
    char buff[max], buff1[max];
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socketing failed");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    
    slen = sizeof(s_addr);
    
    if((cfd = connect(sfd, (struct sockaddr *)&s_addr,slen)) < 0) {
        perror("Could not connect to server.");
        exit(EXIT_FAILURE);
    }
    
    if((rcv = recv(sfd, buff, sizeof(buff1), 0)) < 0){
        perror("recieving error");
        exit(EXIT_FAILURE);
    }
    buff[rcv] = '\0';
    
    if((rcv = recv(sfd, buff1, sizeof(buff1), 0)) < 0){
        perror("recieving error");
        exit(EXIT_FAILURE);
    }
    buff1[rcv] = '\0';
    
    printf("\nServer -> String sent by client 1 : %s\nConsonants : %s\n", buff, buff1);
    return 0;

   
}