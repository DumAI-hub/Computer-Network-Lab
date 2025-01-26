/*
    Author : Dibakar Patar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<ctype.h>

#define max 1024
#define PORT_NUMBER 4000


int isVowel(char c) {
    
    c = tolower(c);
    
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    
}

int main(){
    
    int sfd,c1_sock, c2_sock, rcv, slen;
    
    char buff[max], consonants[max], vowels[max];
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        
        perror("Socket 1 creation failed");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in s;
    
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT_NUMBER);
    s.sin_addr.s_addr = INADDR_ANY;
    
    slen = sizeof(s);
    
    if(bind(sfd, (struct sockaddr *)&s, slen) < 0){
        perror("Binding failed with ");
        exit(EXIT_FAILURE);
    }
    
    if(listen(sfd, 6) < 0){
        perror("Listening failed");
        exit(0);
        
    }
    
    while (1) {
        
        if((c1_sock = accept(sfd, (struct sockaddr *)&s, (socklen_t *)&slen)) < 0) {
            perror("Acceping failed from client 1");
            exit(EXIT_FAILURE);
        }
        
        if((c2_sock = accept(sfd, (struct sockaddr *)&s, (socklen_t *)&slen)) < 0) {
            perror("Accepting failed from client 2");
            exit(EXIT_FAILURE);
        }
        
        
        if((rcv = recv(c1_sock, buff, sizeof(buff), 0)) < 0) {
            perror("Recieving error from client 1");
            exit(EXIT_FAILURE);
        }
        buff[rcv] = '\0';
        
        
        //create two separate varible for vowel and consonant
        
        int v =0, c = 0; 
        for(int i = 0; buff[i] != '\0'; i++) {
            
            //isalpha is provided by ctype.h, it checks whether the input is a alphabet or not
            //so if isalpha is true it will look for vowels and consonants
            if(isalpha(buff[i])){
                if(isVowel(buff[i])) {
                    vowels[v++] = buff[i];
                }else {
                    consonants[c++] = buff[i];
                }
                
                
            } 
            
        }
        
        vowels[v] = '\0';
        consonants[c] = '\0';
        
        if(send(c1_sock, vowels, strlen(vowels), 0) < 0) {
            perror("Sending to client 1 failed");
            exit(EXIT_FAILURE);
        }
        
        if(send(c2_sock, consonants, strlen(consonants), 0) < 0 ){
            perror("Sending to client 2 failed");
            exit(EXIT_FAILURE);
        }
        
        close(sfd);
        close(c1_sock);
        close(c2_sock);
        
        return 0;
        
    }
    
    
    
    
    
    
    
    
}