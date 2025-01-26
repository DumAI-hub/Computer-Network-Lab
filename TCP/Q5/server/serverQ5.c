/*
    Author : Dibakar Patar
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define max_qoute 5
#define PORT_NUMBER 4000
#define INET_ADDR "192.168.127.98"

void handle_client(int client_socket) {

  const char *qoutes[max_qoute] = {
      "Connection established! Let’s hope it’s not like my last relationship.",
      "Welcome, client! Don’t worry, I won’t socket to you too hard.",
      "Hello! I see you’re here to download my sense of humor... good luck!",
      "Server says: 'Connection successful! Now let’s make it awkward.",
      "Welcome to CornHub! Please have some Corn"};

  const char *random_qoute = qoutes[rand() % max_qoute];

  printf("\nServer -> %s\n", random_qoute);
  if (send(client_socket, random_qoute, strlen(random_qoute), 0) < 0) {
    perror("Socketing failed");
    exit(0);
  }

  close(client_socket);
}

int main() {

  int socket_fd, client_socket, snd, slen;

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket creation failed");
    exit(0);
  }

  struct sockaddr_in s;

  s.sin_family = AF_INET;
  s.sin_port = htons(PORT_NUMBER);
  s.sin_addr.s_addr = INADDR_ANY;

  slen = sizeof(s);

  if (bind(socket_fd, (struct sockaddr *)&s, slen) < 0) {
    perror("Binding failed");
    exit(0);
  }

  if (listen(socket_fd, 5) < 0) {
    perror("Listening failed");
    exit(0);
  }

  printf("\nServer listening on port : %d\n", PORT_NUMBER);

  while ((client_socket = accept(socket_fd, (struct sockaddr *)&s,
                                 (socklen_t *)&slen)) >= 0) {

    printf("\nNew client connection\n");
    handle_client(client_socket);
  }

  if (client_socket < 0) {
    perror("Accepting failed");
    exit(0);
  }

  close(socket_fd);
}
