/*
    Author : Dibakar Patar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define max 1024

void bitDestuffing(char *stuffedData, char *deStuffedData) {
    int count = 0;
    int j = 0;
    
    for(int i=0; stuffedData[i] != '\0'; i++ ) {
        if(stuffedData[i] == '1') {
            count++;
            deStuffedData[j] = stuffedData[i];
            j++;
        }else {
            count = 0;
            deStuffedData[j] = stuffedData[i];
            j++;
        }
        
        if(count == 5) {
            if(stuffedData[i+1] == '0') {
                i++;
            }
            count = 0;
        }
    }
    
    deStuffedData[j] = '\0';
}

int main() {
    
    int sfd, rcv;
    char buff[max], destuffedData[max];
    
    struct sockaddr_in s_addr;
    socklen_t addr_len;
    
    if((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    
    addr_len = sizeof(s_addr);
    if(bind(sfd, (struct sockaddr *)&s_addr, addr_len) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    
    printf("\nServer running...waiting for data...\n");
    
    while(1) {
        if((rcv = recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr *)&s_addr, &addr_len))<0){
            perror("Reciving error");
            exit(EXIT_FAILURE);
        }    
        buff[rcv] = '\0';
        
        bitDestuffing(buff, destuffedData);
        
        printf("\nStuffed data : %s\nStuffed data length : %ld\nOriginal frame : %s\nOrigial frame length : %ld\n\n", buff, strlen(buff),destuffedData, strlen(destuffedData));
        
        if(sendto(sfd, destuffedData, strlen(destuffedData), 0, (struct sockaddr *)&s_addr, addr_len) < 0) {
            perror("Sending error");
            exit(EXIT_FAILURE);
        }
    }
    
    close(sfd);
    
    return 0;
}