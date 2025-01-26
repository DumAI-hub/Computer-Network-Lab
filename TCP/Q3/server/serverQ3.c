/*
    Author : Dibakar Patar
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int sumOfDigits(int number) {
  int temp = number;
  int sum = 0;

  while (temp > 0) {
    sum += temp % 10;
    temp = temp / 10;
  }

  return sum;
}

int main() {

  int sfd, cfd, bi, li, rcv, snd, ac, slen;

  int buff;

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) {
    perror("Socket creation failed");
    exit(0);
  }

  struct sockaddr_in s;

  s.sin_family = AF_INET;
  s.sin_port = htons(4000);
  s.sin_addr.s_addr = inet_addr("192.168.127.98");

  slen = sizeof(s);

  bi = bind(sfd, (struct sockaddr *)&s, slen);
  if (bi < 0) {
    perror("binding error");
    exit(0);
  }

  li = listen(sfd, 6);
  if (li < 0) {
    perror("Binding error");
    exit(0);
  }

  while (1) {

    ac = accept(sfd, (struct sockaddr *)&s, (socklen_t *)&slen);
    if (ac < 0) {
      perror("accepting failed");
      exit(0);
    }

    rcv = recv(ac, &buff, sizeof(buff), 0);
    if (rcv < 0) {
      perror("recieving error");
      exit(0);
    }

    int sum = sumOfDigits(buff);

    snd = send(ac, &sum, sizeof(sum), 0);
    if (snd < 0) {
      perror("sending error");
      exit(0);
    }

    printf("\nThe sum of the digits of %d is %d\n", buff, sum);
  }
}
