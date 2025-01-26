/*
    Author : Dibakar Patar

    This is the server program
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define max 100

int main() {

  int sfd, bi, snd, rcv;
  char buff[max];

  sfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sfd < 0) {
    perror("socketing error");
    exit(0);
  }

  struct sockaddr_in s;

  s.sin_family = AF_INET;
  s.sin_port = htons(4000);
  s.sin_addr.s_addr = inet_addr("192.168.127.98");

  int slen = sizeof(s);
  bi = bind(sfd, (struct sockaddr *)&s, sizeof(s));
  if (bi < 0) {
    perror("binding error");
    exit(0);
  }

  while (1) {

    // Unlike in TCP we use recvfrom() instead of recv() in UDP
    rcv = recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr *)&s,
                   (socklen_t *)&slen);
    buff[rcv] = '\0';
    if (rcv < 0) {
      perror("Recieving error");
      exit(0);
    }

    printf("Client -> %s", buff);

    // And sendto() instead of send()
    snd = sendto(sfd, buff, strlen(buff), 0, (struct sockaddr *)&s, slen);
    if (snd < 0) {
      perror("sending error");
      exit(0);
    }
  }
}
