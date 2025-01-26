/*
    Author : Dibakar Patar - 22BTechIT26
    
    This is the Server program.
*/


#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>



int main(){

   int sfd, li, bi, ac, snd, rcv, slen;
    char buff[100];

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0){
        perror("Socketing error");
        exit(0);
    }

    struct sockaddr_in  s;

    s.sin_family = AF_INET;
    s.sin_port = htons(4000);
    s.sin_addr.s_addr = inet_addr("192.168.127.98");

    slen = sizeof(s);

    bi = bind(sfd, (struct sockaddr *)&s, slen);
    if(bi < 0){
        perror("binding error");
        exit(0);
    }

    li = listen(sfd, 5);
    if(li < 0 ){
        perror("Listening error");
        exit(0);
    }
    while(1){
        ac = accept(sfd, (struct sockaddr *)&s, (socklen_t *)&slen);
        if(ac < 0){
            perror("accepting error");
            exit(0);
        }

        rcv = recv(ac, buff, sizeof(buff), 0);
        buff[rcv] = '\0';
        if(rcv < 0){
            perror("recieving error");
            exit(0);
        }

        snd = send(ac, buff, strlen(buff), 0);
        if(snd < 0){
            perror("sending error");
            exit(0);
        }

        return 0;

    }



}
