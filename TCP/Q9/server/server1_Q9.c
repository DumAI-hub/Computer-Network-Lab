/*
    Author : Dibakar Patar
    
    This is Server 1 of the distributed system that handles initial number processing.
    It determines if a number is even or odd and forwards odd numbers to Server 2
    for prime number checking.
*/

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Constants for buffer size and port numbers
#define max 1024        // Maximum buffer size
#define PORT 4000      // Port number for Server 1
#define PORT2 4001     // Port number for Server 2

// Function to check if a number is even
bool isEven(int number) { return (number % 2 == 0); }

int main() {
    // Socket file descriptors and variables
    int sfd,           // Main server socket
        sfd2,          // Socket for Server 2 connection
        cfd,           // Client connection socket
        number;        // Number received from client
    char buff[max];    // Buffer for messages

    // Socket address structures
    struct sockaddr_in s_addr,    // Server address
                      cl_addr,    // Client address
                      s2_addr;    // Server 2 address
    socklen_t addr_len;

    // Create main server socket
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
        perror("binding error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sfd, 5) < 0) {
        perror("listening error");
        exit(EXIT_FAILURE);
    } else {
        printf("\nserver listening on PORT : %d", PORT);
    }

    // Main server loop
    while (1) {
        addr_len = sizeof(cl_addr);
        // Accept client connection
        if ((cfd = accept(sfd, (struct sockaddr *)&cl_addr, &addr_len)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        } else {
            printf("\nClient connected\n");
        }

        // Receive number from client
        if (recv(cfd, &number, sizeof(number), 0) < 0) {
            perror("receiving from the client failed");
            exit(EXIT_FAILURE);
        } else {
            printf("\nClient -> %d\n", number);

            // Handle even numbers
            if (isEven(number)) {
                const char *even = "even";
                printf("\n%s\n", even);
                if (send(cfd, even, strlen(even), 0) < 0) {
                    perror("Send to client failed");
                }
            } 
            // Handle odd numbers
            else {
                // Inform client about forwarding to Server 2
                char *message = "Number is ODD. Sending to server 2";
                printf("\n%s\n", message);
                if (send(cfd, message, strlen(message), 0) < 0) {
                    perror("Send to client failed");
                }

                // Create socket for Server 2 connection
                if ((sfd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                    perror("server 2 socket creation failed");
                    close(cfd);
                    exit(EXIT_SUCCESS);
                }

                // Configure Server 2 address
                memset(&s2_addr, 0, sizeof(s2_addr));
                s2_addr.sin_family = AF_INET;
                s2_addr.sin_port = htons(PORT2);
                s2_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

                // Connect to Server 2
                if ((connect(sfd2, (struct sockaddr *)&s2_addr, sizeof(s2_addr))) < 0) {
                    perror("Connection to server 2 failed");
                    close(sfd2);
                    close(cfd);
                    exit(EXIT_FAILURE);
                }

                // Send number to Server 2
                if (send(sfd2, &number, sizeof(number), 0) < 0) {
                    perror("Send to server 2 failed");
                    exit(EXIT_FAILURE);
                }

                // Confirm to client that number is being processed
                const char *msg = "Number sent to Server 2 for prime check";
                if (send(cfd, msg, strlen(msg), 0) < 0) {
                    perror("Send to client failed");
                }
                
                //receives result from server 2
                if(recv(cfd, buff, sizeof(buff), 0) < 0) {
                    perror("receiving from server 2 failed");
                }

                close(sfd2);  // Close Server 2 connection
            }
        }
    }

    // Close main server socket
    close(sfd);
    return 0;
}