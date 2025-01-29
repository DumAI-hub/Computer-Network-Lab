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


void merge(int num, char str[], int sfd, struct sockaddr_in cl_sock1, struct sockaddr_in cl_sock2, socklen_t addr_len) {
   
    char result_str[max], num_str[20];
    
    
    //converts the integer to string
    sprintf(num_str, "%d", num);
    
    //Combine the two strings
    strcpy(result_str, str); //copy the string to the result buffer
    strcat(result_str, num_str); //concatinates the two string
    
    printf("\nMerged string : %s\n", result_str);
    
    //send to client 1
    if(sendto(sfd, result_str, strlen(result_str), 0, (struct sockaddr *)&cl_sock1, addr_len) < 0) {
        perror("sending to client 1 failed");
        exit(EXIT_FAILURE);
    }
    
    //send to client 2
    if(sendto(sfd, result_str, strlen(result_str), 0, (struct sockaddr *)&cl_sock2, addr_len) < 0) {
        perror("sending to client 2 failed");
        exit(EXIT_FAILURE);
    }
    
    
    
}

int main() {
    int sfd, number;
    char buff[max];
    
    struct sockaddr_in s_addr, cl_sock1, cl_sock2;

    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    
    socklen_t addr_len = sizeof(s_addr);
    
    if((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    if(bind(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0){
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    
    
    while(1){
        
        //reset the address lenght afte every receive
        addr_len = sizeof(s_addr);
        
        if(recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr *)&cl_sock1, &addr_len) < 0) {
            perror("Receiving error from client 1");
            exit(EXIT_FAILURE);
        }
        
        printf("\nReceived number from client 1 -> %s\n", buff);
        
        addr_len = sizeof(s_addr);
        if(recvfrom(sfd, &number, sizeof(number), 0, (struct sockaddr *)&cl_sock2, &addr_len) < 0) {
            perror("Receiving error from client 2");
            exit(EXIT_FAILURE);
        }
        
        printf("\nReceived string from client 2 -> %d\n", number);
        
        merge(number, buff, sfd, cl_sock1, cl_sock2, addr_len);
        
    } 
    
    return 0;
    
}