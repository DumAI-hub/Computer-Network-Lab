/*
    Author : Dibakar Patar
    
    This is the client program
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define max 100
int main() {
    int sfd, snd, rcv, slen;
    char buff[max], buff2[max];
    
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sfd < 0){
        perror("Socketing error");
        exit(0);
    }
    
    struct sockaddr_in s;
    
    s.sin_family = AF_INET;
    s.sin_port = htons(4000);
    s.sin_addr.s_addr = inet_addr("192.168.127.98");
    
    slen = sizeof(s);
    
    printf("Client -> ");
    scanf("%[^\n]s", buff);
    
    snd = sendto(sfd, buff, strlen(buff), 0, (struct sockaddr *)&s, slen);
    if(snd < 0){
        perror("Sending error");
        exit(0);
    }
    
    rcv = recvfrom(sfd, buff2, sizeof(buff2), 0, (struct sockaddr *)&s, (socklen_t *)&slen);
    if(rcv < 0){
        perror("receiveing error");
        exit(0);
    }
    
    printf("Server -> %s ", buff2);
    
    close(sfd);
    close(snd);
    close(rcv);
}