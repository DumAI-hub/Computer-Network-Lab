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

void byteStuffing(char *original, char *stuffed){
    int j=0;
    
    stuffed[j++] = '$';
    
    
    for(int i = 0; original[i] != '\0'; i++) {
        if(original[i] == '$' ) {
            
            stuffed[j++] = '$';
            stuffed[j++] = '$';
        }else {
            stuffed[j++] = original[i];
        }
    }
    
    stuffed[j++] = '$';
    stuffed[j] = '\0';
}

int main() {
    
    int sfd, cfd, rcv;
    char buff[max], original[max], stuffed[max];
    
    struct sockaddr_in s_addr;
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    socklen_t addr_len = sizeof(s_addr);
    
    
    if((cfd = connect(sfd, (struct sockaddr *)&s_addr, addr_len)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    
    printf("\nEnter data : ");
    scanf("%s", original);
    
    byteStuffing(original, stuffed);
    
    printf("\n%s\n", stuffed);
    
    if(send(sfd, stuffed, strlen(stuffed), 0) < 0) {
        perror("Sending failed");
        exit(EXIT_FAILURE);
    }
    
    if(( rcv = recv(sfd, buff, sizeof(buff), 0)) < 0) {
        perror("Receiving failed");
        exit(EXIT_FAILURE);
    }
    buff[rcv] = '\0';
    
    if(strstr(buff, original)) {
        printf("\nCorrect frame received\n");
    }

    close(sfd);
    close(cfd);

    return 0;

    
    
}