/*
    Author : Dibakar Patar
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<stdbool.h>

#define max 1024
#define PORT_NUMBER 4000
#define INET_ADDR "192.168.127.98"

bool isPalindrome(char *word) { 
    int length = strlen(word);
    
    for(int i = 0, j = length -1; i < j; i++, j--){
        if(word[i] != word[j]){
           return false;
        }
    }
    

    return true;
    
}

int main() {
    
    int sfd, bi, rcv, snd, slen;
    char buff[max];
    
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sfd < 0){
        perror("Socket creation failed");
        exit(0);
    }
    
    struct sockaddr_in s;
    
    s.sin_family = AF_INET;
    s.sin_port = htons(PORT_NUMBER);
    s.sin_addr.s_addr = inet_addr(INET_ADDR);
    
    slen = sizeof(s);
    
    
    if((bind(sfd, (struct sockaddr *)&s, slen)) < 0) {
        perror("Binding error");
        exit(0);
    }
    
    
    while(1){
        
        if( (recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr *)&s, (socklen_t *)&slen)) < 0) {
            perror("Recieing error");
            exit(0);
        }
        
        if( isPalindrome(buff)){
            char result[] = "Input string is a palindrome";
            printf("\n%s\n", result);
            
            if((sendto(sfd, result, strlen(result), 0, (struct sockaddr *)&s, slen))<0){
                perror("sending error");
                exit(0);
            }
            
        }else {
            char result[] = "Input string is not a Palindrom";
            printf("\n%s\n", result);
            snd = sendto(sfd, result, strlen(result), 0, (struct sockaddr *)&s, slen);
        }
    }
 }
