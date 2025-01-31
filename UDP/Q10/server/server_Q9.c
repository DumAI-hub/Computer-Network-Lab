/*
    Author : Dibakar Patar
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

// Function to reverse the number
int revNum(int number) {
  int rev = 0;
  while (number > 0) {
    rev = rev * 10 + number % 10; // gets last digit and adds to reversed number
    number = number / 10;         // removes last digit from number
  }
  return rev;
}

int main() {

  int sfd, number, res, cl_sock;

  struct sockaddr_in s_addr;
  socklen_t addr_len;

  // Creating socket file descriptor
  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);
  s_addr.sin_addr.s_addr = INADDR_ANY;

  addr_len = sizeof(s_addr);

  if (bind(sfd, (struct sockaddr *)&s_addr, addr_len) < 0) {
    perror("Binding fialed");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on PORT : %d", PORT);

  while (1) {
    if (recvfrom(sfd, &number, sizeof(number), 0, (struct sockaddr *)&s_addr,
                 &addr_len) < 0) {
      perror("Receiving from server failed");
      close(sfd);
      exit(EXIT_FAILURE);
    }

    printf("\nClient -> %d\n", number);

    res = revNum(number);

    printf("\nReversed number : %d\n", res);

    if (sendto(sfd, &res, sizeof(res), 0, (struct sockaddr *)&s_addr,
               addr_len) < 0) {
      perror("Semding failed");
      close(sfd);
      exit(EXIT_FAILURE);
    }
  }

  close(sfd);
  return 0;
}
