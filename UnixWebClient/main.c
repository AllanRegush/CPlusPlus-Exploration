#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>

const int SERVER_PORT = 80;
const int MAXLINE = 4086;
const int TCP = 0;

int main(int argc, char **argv)
{
  if(argc != 2)
  {
    printf("usage: %s <server address\n", argv[0]);
    return 1;
  }

  int sockfd; 
  if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "ERROR: could not create socket\n");
    return 2;
  }

  struct sockaddr_in serveradder = {0};
  bzero(&serveradder, sizeof(serveradder));
  serveradder.sin_family = AF_INET;
  serveradder.sin_port = htons(SERVER_PORT);

  if(inet_pton(AF_INET, argv[1], &serveradder.sin_addr) <= 0)
  {
    fprintf(stderr, "ERROR: inet_pton %s\n", argv[1]);
    return 3;
  }

  if(connect(sockfd, (struct sockaddr *) &serveradder, sizeof(serveradder)) < 0)
  {
    fprintf(stderr, "ERROR: Could not connect\n");
    return 4;
  }
  char sendline[MAXLINE];
  sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
  int sendbytes = strlen(sendline);

  if(write(sockfd, sendline, sendbytes) != sendbytes)
  {
    fprintf(stderr, "ERROR: writing failed\n");
    return 5;
  }

  char rxline[MAXLINE];
  rxline[0] = '\0';
  int n = 0;
  while( (n = read(sockfd, rxline, MAXLINE - 1)) > 0)
  {
    printf("%s", rxline);
    memset(rxline, 0, MAXLINE);
  }

  if(n < 0)
  {
    fprintf(stderr, "ERROR: read failed");
    return 6;
  }
  
  return 0;
}