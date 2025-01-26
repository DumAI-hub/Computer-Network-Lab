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

struct sockaddr_in s_addr;


int main(){
    int sfd, cfd, slen;
    char buff[max];
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socketing failed");
        exit(EXIT_FAILURE);
    }
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    
    slen = sizeof(s_addr);
    printf("\nEnter the string here : ");
    scanf("%s", buff);
    
    if((cfd = connect(sfd, (struct sockaddr *)&s_addr,slen)) < 0) {
        perror("Could not connect to server.");
        exit(EXIT_FAILURE);
    }
    
    if(send(sfd, buff, strlen(buff), 0) < 0) {
        perror("Sending failed");
        exit(EXIT_FAILURE);
    }
    
    return 0;
    
   
}