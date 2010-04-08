/* Simple UDP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// *** CONFIGURE ME:
#define LISTEN_PORT 27072             // udp listen port
#define LOG_FILE_NAME "udps.log"      // log file name

int main(int argc, char**argv) {

  int sockfd,n;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t len;
  char mesg[1000];
  char cli[32];
  char datetime[24];

  time_t rawtime;
  struct tm * timeinfo;

  sockfd = socket(AF_INET,SOCK_DGRAM,0);

  FILE *fp = fopen(LOG_FILE_NAME, "ab");

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(LISTEN_PORT);
  bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  for (;;) {
    len = sizeof(cliaddr);
    n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *)&cliaddr, &len);

    // truncate data
    mesg[n] = 0;

    // get addr for logging
    inet_ntop(AF_INET, &cliaddr.sin_addr, cli, 32);

    // get the time
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(datetime,24,"%F %T",timeinfo);

    fprintf(fp, "%s:%s:%s\n", cli, datetime,  mesg);
    fflush(fp);
  }

  fclose(fp);
}
