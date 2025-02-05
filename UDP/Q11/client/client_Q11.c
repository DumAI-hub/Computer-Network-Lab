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

void bitStuffing(char *input, char *output) {
    int count = 0, j = 0;
    
    for(int i = 0; input[i] != '\0'; i++) {
        if(input[i] == '1') {
            count++;
            output[j] = input[i];
            j++;
        }else{
            count = 0;
            output[j] = input[i];
            j++;
        }
        
        if(count == 5) {
            output[j] = '0';
            j++;
            count = 0;
        }
    }
    
    output[j] = '\0';
}

int main() {
    int sfd, rcv;
    
    char buff[max], input[max], stuffedData[max];
    struct sockaddr_in s_addr;
    socklen_t addr_len;
    
    if((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    addr_len = sizeof(s_addr);
    
    printf("\nEnter the frame : ");
    scanf("%s", input);
    
    bitStuffing(input, stuffedData);
    
    printf("\nStuffed data : %s\n", stuffedData);
    
    if(sendto(sfd, stuffedData, strlen(stuffedData), 0, (struct sockaddr *)&s_addr, addr_len) < 0) {
        perror("Sending error");
        exit(EXIT_FAILURE);
    }
    
    
    if((rcv = recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr *)&s_addr, &addr_len)) < 0) {
        perror("Receiving error");
        exit(EXIT_FAILURE);
    }
    buff[rcv] = '\0';
    
    if(strstr(input, buff)) {
        printf("\nframe received and destuffed succesfully\n");
    }
    
    
    return 0;
}