/*
    Author : Dibakar Patar - 22BTechIT26
    
    This is the Client program.
*/



#include <stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define max 100
int main(){
    
    int sfd, cfd, snd, rcv, slen;
    char buff[max], buff2[max];
    
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0) {
        perror("socketing error");
        exit(0);
    }
    
    struct sockaddr_in s;
    
    s.sin_family = AF_INET;
    s.sin_port = htons(4000); //Use your desired port number
    s.sin_addr.s_addr = inet_addr("192.168.127.98"); //use your own inet address
    

    slen = sizeof(s);
    
    cfd = connect(sfd, (struct sockaddr *)&s, slen);
    if(cfd < 0){
        perror("connecting error");
        exit(0);
    }
    
    printf("client -> ");
    scanf("%s", buff);
    
    snd = send(sfd, buff, strlen(buff), 0);
    if(snd < 0){
        perror("sending erorr");
        exit(0);
    
    }
    
    rcv = recv(sfd, buff2, sizeof(buff2), 0);
    if(rcv < 0){
        perror("receving error");
        exit(0);
    }
    
    printf("server -> %s", buff2);
    
    close(sfd);
    close(cfd);
    close(snd);
    close(rcv);
    
    
    
}