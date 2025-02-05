/*
    Author : Dibakar Patar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

#define PORT 8080
#define max 1024
#define max_clients 50

int isPalindrome(int num) {
    int reversed=0, original = num;
    
    while(num > 0) {
        reversed = reversed * 10 + num%10;
        num /= 10;
    }
    
    return (original == reversed);
}

struct client_data {
    int client_socket;
};

void *handle_client(void *arg) {
    struct client_data *data = (struct client_data *)arg;
    int client_sock = data->client_socket;
    int number;
    char response[50];
    
    
    if(recv(client_sock, &number, sizeof(number), 0) < 0) {
        perror("Receiving error");
        exit(EXIT_FAILURE);
    }
    printf("\nReceived number : %d\n", number);
    
    if(isPalindrome(number)) {
        sprintf(response, "%d is a palindrome number.", number);
    }else {
        sprintf(response, "%d is not a palindrome number.", number);
    }
    
    printf("\n%s\n", response);
    
    if(send(client_sock, response, strlen(response), 0) < 0) {
        perror("Sending failed");
        exit(EXIT_FAILURE);
    } 
    
    close(client_sock);
    free(data);
    pthread_exit(NULL);
    
}


int main() {
    
    int sfd, client_sock;
    
    struct sockaddr_in s_addr;
    pthread_t thread_id;
    
    if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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
    
    if(listen(sfd, max_clients) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("\nServer lisrtening on :  %d\n", PORT);
    
    while(1) {
        if((client_sock = accept(sfd, (struct sockaddr *)&s_addr, &addr_len)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        
        struct client_data *data = malloc(sizeof(struct client_data));
        data->client_socket = client_sock;
        
        if(pthread_create(&thread_id, NULL, handle_client, (void *)data) < 0) {
            perror("Thread creation failed");
            free(data);
            close(client_sock);
            continue;
        }
        
        pthread_detach(thread_id);
        
        
    }
 
    close(sfd);
    return 0;
}