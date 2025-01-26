/*
    Author : Dibakar Patar
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
    
    int sfd, cfd, snd, rcv, slen;
    int buff, result;
 
    
    sfd =  socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0){
        perror("socket creation failed");
        exit(0);
    }
    
    struct sockaddr_in s;
    
    s.sin_family = AF_INET;
    s.sin_port = htons(4000);
    s.sin_addr.s_addr = inet_addr("192.168.127.98");
    
    slen = sizeof(s);
    
    
    printf("\nEnter a two digit number\n");
    printf("Client -> ");
    scanf("%d", &buff);
    
    cfd = connect(sfd, (struct sockaddr *)&s, slen);
    if(cfd < 0){
        perror("connection failed");
        exit(0);
    }
    
    snd = send(sfd, &buff, sizeof(buff), 0);
    if(snd < 0){
        perror("Sending error");
        exit(0);
    }
    
    rcv = recv(sfd, &result, sizeof(result), 0);
    if(rcv < 0){
        perror("Reciving error");
        exit(0);
    }
    
    printf("\nServer -> Sum of the digits of %d is : %d\n", buff, result );
    
    close(sfd);
    close(cfd);
    close(snd);
    close(rcv);
    
    
}