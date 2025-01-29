/*
    Author : Dibakar Patar
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define max 1024
#define PORT 4000

void copyFile(int cl_sock) {
    
    char source_file[max];
    char dest_file[max];
    char buff[max];
    FILE *source, *dest;
    size_t bytes_read;
    
    if(recv(cl_sock, source_file, sizeof(source_file), 0) >= 0) {
        printf("\nSource file : %s\n", source_file);
    }else{
        perror("Receiving failed.");
        exit(EXIT_FAILURE);
    }
    
    if(recv(cl_sock, dest_file, sizeof(dest_file), 0) >= 0) {
        printf("\nDestination file : %s\n", dest_file);
    }else{
        perror("Receiving failed.");
        exit(EXIT_FAILURE);
    }
    
    source = fopen(source_file, "rb");
    if(source == NULL) {
        char *error = "Source file not found";
        if(send(cl_sock, error, strlen(error), 0) < 0) {
            perror("sending error");
            exit(EXIT_FAILURE);
        }
    }
    
    dest = fopen(dest_file,"wb");
    if(dest == NULL){
        char *error = "Cannot create destination file";
        printf("\n%s\n", error);
        send(cl_sock, error, strlen(error), 0);
        
        /* 
        if(creat(dest_file, 7777) < 0) {
            char *error = "file creation failed";
            perror(error);
            send(cl_sock, error, strlen(error), 0);
            exit(EXIT_FAILURE);
        }
        */
    }
    
    char *success = "File copy started";
    send(cl_sock, success, strlen(success), 0);
    
    while( (bytes_read = fread(buff, 1, max, source)) > 0) {
        fwrite(buff, 1, bytes_read, dest);
    }
    
    fclose(source);
    fclose(dest);
    
    char *complete = "File copy completed";
    send(cl_sock, complete, strlen(complete), 0);
    
    close(cl_sock);
    
}

int main() {
  int sfd, cfd;
  char buff[max];

  struct sockaddr_in s_addr, cl_addr;
  socklen_t addr_len;

  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);
  s_addr.sin_addr.s_addr = INADDR_ANY;


  if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket creation failed");
    close(sfd);
    exit(EXIT_FAILURE);
  }

  if (bind(sfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) {
    perror("Binding failed");
    exit(EXIT_FAILURE);
  }

  if (listen(sfd, 5) >= 0) {

    printf("Server listening on port : %d", PORT);

  } else {
    perror("Couldn't listen");
    exit(EXIT_FAILURE);
  }

  while (1) {
      
      addr_len = sizeof(cl_addr);
      if((cfd = accept(sfd, (struct sockaddr *)&cl_addr, &addr_len )) >= 0){
          printf("Client connected");
          copyFile(cfd);
          close(cfd);
          printf("client disconnected");
          
      } else {
          perror("Could not connect to client");
          exit(EXIT_FAILURE);
      }
  }
  
  close(sfd);
  
  return 0;
}
