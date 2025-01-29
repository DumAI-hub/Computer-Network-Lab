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
    int sfd, rcv, number ;
    char buff[max], buff1[max];
    struct sockaddr_in s_addr;
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    
    socklen_t addr_len = sizeof(s_addr);
    
    if((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    
    printf("\nEnter the number : ");
    scanf("%d", &number);
    
    
    if(sendto(sfd, &number, sizeof(number), 0, (struct sockaddr *)&s_addr, addr_len) < 0 ) {
        perror("Couldn't send to server.");
        exit(EXIT_FAILURE);
    }
    
    if((rcv = recvfrom(sfd, buff1, sizeof(buff1), 0, (struct sockaddr *)&s_addr, &addr_len)) < 0) {
        perror("Receiving from failed");
        exit(EXIT_FAILURE);
    }
    buff1[rcv] = '\0';
    
    printf("\nServer -> Merged string : %s\n", buff1);
    
    close(sfd);
    
    return 0;
}
