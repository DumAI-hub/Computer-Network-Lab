/*
    Author : Dibakar Patar
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
  int sfd, number, res;

  struct sockaddr_in s_addr;
  socklen_t addr_len;

  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Socket creation failed");
    close(sfd);
    exit(EXIT_FAILURE);
  }

  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);
  s_addr.sin_addr.s_addr = INADDR_ANY;

  addr_len = sizeof(s_addr);

  printf("\nEnter the numer : ");
  if (scanf("%d", &number) == 0) {
    perror("Invalid input");
    exit(EXIT_FAILURE);
  }

  if (sendto(sfd, &number, sizeof(number), 0, (struct sockaddr *)&s_addr,
             addr_len) < 0) {
    perror("Send failed");
    exit(EXIT_FAILURE);
  }

  if (recvfrom(sfd, &res, sizeof(res), 0, (struct sockaddr *)&s_addr,
               &addr_len) < 0) {
    perror("Receiving error");
    exit(EXIT_FAILURE);
  }

  printf("\nReversed number : %d\n", res);

  close(sfd);

  return 0;
}
