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
#define PORT_NUMBER 4000
#define INET_ADDR "192.168.127.98"

int main() {
    int sfd , rcv, snd, slen;
    char buff[max], buff2[max];
    
    if((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(0);
    }
    
    struct sockaddr_in s;
    
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT_NUMBER);
    s.sin_addr.s_addr = inet_addr(INET_ADDR);
    
    slen = sizeof(s);
    
    printf("\n*** Palindrome checker ***\n");
    printf("Enter string here : ");
    scanf("%s", buff);
    
    printf("\nWaiting for server...\n");
    
    if(sendto(sfd, buff, strlen(buff), 0, (struct sockaddr *)&s, slen) < 0) {
        perror("Sending error");
        exit(0);
    }
    
    if(recvfrom(sfd, buff2, sizeof(buff2), 0, (struct sockaddr *)&s, (socklen_t *)&slen) < 0){
        perror("recieving error");
        exit(0);
    }
    
    printf("\nServer -> %s\n", buff2);
    
    
}