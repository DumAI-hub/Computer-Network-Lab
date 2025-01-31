/*
    Author : Dibakar Patar
    
    This is the Client program that interacts with both Server 1 and Server 2.
    It sends numbers to Server 1 for even/odd checking and receives prime number
    results from Server 2 for odd numbers.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

// Constants for buffer size and port numbers
#define max 1024      // Maximum buffer size
#define PORT 4000     // Port for Server 1
#define CL_PORT 4002  // Port for receiving Server 2 responses

int main() {
    // Socket file descriptors and variables
    int sfd,          // Socket for Server 1 connection
        li_sock,      // Listening socket for Server 2
        rcv,          // Received bytes count
        cl_sock,      // Accept socket for Server 2
        number;       // Number to be processed
    char buff[max];   // Buffer for messages
    
    // Socket address structures
    struct sockaddr_in s_addr,      // Server 1 address
                      listen_addr,   // Client listening address
                      s2_addr;      // Server 2 address
    socklen_t addr_len;
    
    // Create socket for Server 1 connection
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Configure Server 1 address
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Connect to Server 1
    if(connect(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
        perror("connection to server failed");
        exit(EXIT_FAILURE);
    }else {
        printf("\nConnection established\n");
    }
    
    // Create listening socket for Server 2 responses
    if((li_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        perror("Listening socket creation failed");
        close(sfd);
        exit(EXIT_FAILURE);
    }
    
    // Configure listening address
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(CL_PORT);
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    
    // Bind listening socket
    if(bind(li_sock, (struct sockaddr *)&listen_addr, sizeof(listen_addr))<0) {
        perror("Binding failed");
        close(sfd);
        close(li_sock);
        exit(EXIT_FAILURE);
    }
    
    // Listen for Server 2 connections
    if(listen(li_sock, 1) < 0) {
        perror("Listening error");
        close(sfd);
        close(li_sock);
        exit(EXIT_FAILURE);
    }
    
    printf("\nListening for Server2 response on PORT : %d\n", CL_PORT);
    
    // Get input from user
    printf("\nEnter the number : ");
    //validate if the input is number or not
    if(scanf("%d", &number) != 1) {
        printf("Invalid input");
        close(sfd);
        close(li_sock);
        exit(EXIT_FAILURE);
    }
    
    // Send number to Server 1
    if(send(sfd, &number, sizeof(number), 0) < 0) {
        perror("Sending failed");
        close(sfd);
        close(li_sock);
        exit(EXIT_FAILURE);
    }
    
    // Receive response from Server 1
    if((rcv = recv(sfd, buff, sizeof(buff)-1, 0)) < 0) {
        perror("Receiving from the server failed");
        close(sfd);
        close(li_sock);
        exit(EXIT_FAILURE);
    }
    buff[rcv] = '\0';
    printf("\nServer 1 -> %s\n", buff);
    
    // Handle response based on even/odd status
    if(strstr(buff, "even")) {
        printf("\nNumber is even, no need to wait for Server 2\n");
    } else {
        // Wait for Server 2 response for odd numbers
        printf("\nWaiting for prime check from Server2...\n");
        
        addr_len = sizeof(s2_addr);
        if((cl_sock = accept(li_sock, (struct sockaddr *)&s2_addr, &addr_len)) < 0) {
            perror("Accept failed");
            close(sfd);
            close(li_sock);
            exit(EXIT_FAILURE);
        }
        
        // Receive prime number check result from Server 2
        memset(buff, 0, sizeof(buff));
        if((rcv = recv(cl_sock, buff, sizeof(buff)-1, 0)) < 0 ){
            perror("Receiving error");
            close(sfd);
            close(li_sock);
            exit(EXIT_FAILURE);
        }
        buff[rcv] = '\0';
        
        printf("\nServer 2 -> %s\n", buff);
    }
    
    // Close all sockets
    close(sfd);
    close(li_sock);
    return 0;
}