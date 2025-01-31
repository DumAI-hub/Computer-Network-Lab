/*
    Author : Dibakar Patar
    
    This is Server 2 of the distributed system that performs prime number checking.
    It receives odd numbers from Server 1 and sends results back to both Server 1 
    and directly to the client.
*/

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Constants for port numbers and buffer size
#define PORT2 4001      // Port for Server 2
#define CL_PORT 4002    // Port for client communication
#define max 1024        // Maximum buffer size

// Function to check if a number is prime
bool isPrime(int number) {
    if (number <= 1)
        return false;

    // Check for divisibility up to square root of number
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0)
            return false;
    }
    return true;
}

int main() {
    // Socket file descriptors and variables
    int sfd,           // Main server socket
        cl_sock,       // Socket for Server 1 connection
        client_sock,   // Socket for direct client connection
        number;        // Number to be checked
    char buff[max];    // Buffer for messages

    // Socket address structures
    struct sockaddr_in s_addr,      // Server 2 address
                      cl_addr,      // Server 1 address
                      client_addr;  // Client address
    socklen_t addr_len = sizeof(cl_addr);

    // Create main server socket
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure Server 2 address
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT2);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sfd, 3) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
    printf("\nServer listening on PORT : %d\n", PORT2);

    // Main server loop
    while (1) {
        // Accept connection from Server 1
        if ((cl_sock = accept(sfd, (struct sockaddr *)&cl_addr, &addr_len)) < 0) {
            perror("Accept error");
            exit(EXIT_FAILURE);
        }

        // Receive number from Server 1
        if (recv(cl_sock, &number, sizeof(number), 0) < 0) {
            perror("Receiving error");
            exit(EXIT_SUCCESS);
        }
        printf("Received number : %d\n", number);

        // Create socket for direct client communication
        if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Client socket creation failed");
            close(cl_sock);
            close(sfd);
            exit(EXIT_FAILURE);
        }

        // Configure client address for direct communication
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(CL_PORT);
        client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Connect to client
        if (connect(client_sock, (struct sockaddr *)&client_addr,
                    sizeof(client_addr)) < 0) {
            perror("Connection to client failed");
            close(client_sock);
            close(cl_sock);
            close(sfd);
            exit(EXIT_FAILURE);
        }

        // Check if number is prime and prepare response
        memset(buff, 0, sizeof(buff));
        if (isPrime(number)) {
            strcpy(buff, "The number is Prime");
        } else {
            strcpy(buff, "The number is Not Prime");
        }
        printf("\nResult: %s\n", buff);

        // Send result back to Server 1
        if (send(cl_sock, buff, strlen(buff), 0) < 0) {
            perror("Sending to Server 1 error");
            close(client_sock);
            close(cl_sock);
            close(sfd);
            exit(EXIT_FAILURE);
        }
        
        // Send result directly to client
        if (send(client_sock, buff, strlen(buff), 0) < 0) {
            perror("Sending to client error");
            close(client_sock);
            close(cl_sock);
            close(sfd);
            exit(EXIT_FAILURE);
        }
        printf("Response sent directly to client\n");

        // Close connection sockets
        close(client_sock);
        close(cl_sock);
    }

    // Close main server socket
    close(cl_sock);
    close(sfd);
    return 0;
}