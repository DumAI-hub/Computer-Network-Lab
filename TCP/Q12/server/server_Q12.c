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

void byteDestuffing(char *stuffed, char *deStuffed) {
    int j = 0;
    
    for(int i = 0 ; stuffed[i] != '\0' ; i++) {
        if(stuffed[i] == '$' && stuffed[i+1] == '$') {
            deStuffed[j++] = '$';
            i++;
        }else {
            deStuffed[j++] = stuffed[i];
        }
    }
    
    deStuffed[j] = '\0';

}

int main() {
    
    int sfd, cfd, rcv;
    char stuffed[max], deStuffed[max];
    struct sockaddr_in s_addr;
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    s_addr.sin_family = AF_INET;    
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    
    socklen_t addr_len = sizeof(s_addr);
    
    if(bind(sfd, (struct sockaddr *)&s_addr, addr_len) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    
    if(listen(sfd, 3) < 0 ) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
    
    printf("\nServer listening on port : %d\n", PORT);
    
    while(1) {
        if( (cfd = accept(sfd, (struct sockaddr *)&s_addr, &addr_len)) < 0 ) {
            perror("Accepting failed");
        }
        
        printf("\nClient connected...\n");
        
        if((rcv = recv (cfd, stuffed, sizeof(stuffed), 0)) < 0) {
            perror("Receiving error");
            exit(EXIT_FAILURE);
        }
        stuffed[rcv] = '\0';
        
        printf("\nStuffed frame : %s\n", stuffed);
        
        byteDestuffing(stuffed, deStuffed);
        
        printf("\nOriginal frame : %s\n", deStuffed);
        
        if(send(cfd, deStuffed, strlen(deStuffed), 0) < 0 ) {
            perror("Sending failed");
            continue;
        }
    }
    
    close(sfd);
    close(cfd);
    
    return 0;
}