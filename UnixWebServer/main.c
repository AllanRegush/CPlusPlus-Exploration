#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

const int SERVER_PORT = 8000;
const int MAXLINE = 4086;

void send_error(int fd, char *error_number, char *short_msg, char *msg)
{
  char buff[MAXLINE];
  snprintf((char *) buff, sizeof(buff), "HTTP/1.0 %s %s\r\n\r\n%s", error_number, short_msg, msg);
  write(fd, (char *) buff, strlen((char *) buff));
  close(fd);
}


int main(void)
{
  int                listenfd;
  struct sockaddr_in serveraddr;

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "ERROR: Could not create socket\n");
    return 1;
  }

  struct sockaddr_in serveradder = {0};
  serveraddr.sin_family      = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port        = htons(SERVER_PORT);

  if ((bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr))) < 0)
  {
    fprintf(stderr, "ERROR: Could not bind to port %d\n", SERVER_PORT);
  }
  
  if((listen(listenfd, 10)) < 0)
  {
    fprintf(stderr, "ERROR: could not listen on PORT: %s\n", SERVER_PORT);
  }

  int connfd;
  char rxline[MAXLINE];
  while(1)
  {
    struct sockaddr_in addr;
    socklen_t addr_len;

    printf("Waiting for connection on port %d\n", SERVER_PORT);
    fflush(stdout);
    connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

    memset(rxline, 0, MAXLINE);
    int n;
    int err = 0;
    while ((n = read(connfd, rxline, MAXLINE - 1)) > 0)
    {
      char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
      sscanf(rxline, "%s %s %s", method, uri, version);

      if(strcmp(method, "GET"))
      {
        send_error(connfd, "501", "Not Implemented", "501 Not Implemented");
        err = 1;
        break;
      }

      if(strcmp(uri, "/"))
      {
        send_error(connfd, "404", "Not Found", "404 Not Found");
        err = 1;
        break;
      }

      if(rxline[n - 1] == '\n')
      {
        break;
      }
      memset(rxline, 0, MAXLINE);
    }

    if (n < 0)
    {
      fprintf(stderr, "ERROR: Could not read");
    }

    if (err)
    {
      continue;
    }
    
    char buff[MAXLINE], body[MAXLINE];
    
    sprintf(body, "<html><title>Hello World</title>");
    sprintf(body, "%s<body>\r\n", body);
    sprintf(body, "%s<h1 style=\"color:blue;\" >Hello, World from C</h1>", body);
    sprintf(body, "%s</body>\r\n", body);
    sprintf(body, "%s</html>\r\n", body);

    snprintf((char *) buff, sizeof(buff), "HTTP/1.0 200 OK\r\n");
    write(connfd, (char *) buff, strlen((char *) buff));

    snprintf((char *) buff, sizeof(buff), "Content-type: text/html\r\n");
    write(connfd, (char *) buff, strlen((char *) buff));

    snprintf((char *) buff, sizeof(buff), "Content-length: %d\r\n\r\n", strlen(body));
    write(connfd, (char *) buff, strlen((char *) buff));

    write(connfd, (char *) body, strlen((char *) body));
    close(connfd);
  }

  return 0;
}