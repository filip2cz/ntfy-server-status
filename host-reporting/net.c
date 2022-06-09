
/* Socket and relative networking functions demonstration for ETC */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <arpa/inet.h>
#include <stdlib.h> /* exit() */
#include <netdb.h>  /* gethostbyname */


int main (int argc, char ** argv) {

#define BUF_LEN 8192

  int debug=0;
/*
3 values of debug:
0 = no debug messages
1 = only some debug messages, external bash script is still working
2 = everything, but the external bash script will not work
*/

  int sfd, afd, pid;
  struct sockaddr_in saddr;
  socklen_t acc_len;
  struct hostent *hen;
  extern int h_errno;

  if (argc!=3) {
    fprintf(stderr,"Usage: %s <host>|-l port\n", argv[0]);
    return 1;
  }

  if ((sfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror("nd: socket()");
    return 5;
  }

  if ((debug == 2)) {
      printf("Socket created, fd=%d.\n", sfd);
    }

  memset(&saddr, 0, sizeof(struct sockaddr_in)); 

  saddr.sin_family=AF_INET;
  saddr.sin_port=htons(atoi(argv[2]));

  if (!strcmp(argv[1],"-l")) { /* Listen (server) side */
    
    if ((debug >= 1)) {
      printf("Initiating the server side.\n");
    }

    saddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sfd, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in)) <0) {
      perror("nd: bind()");
      return 5;
    }
    
    if ((debug >= 1)) {
      printf("Socket bound successfully.\n");
    }
    

    if (listen(sfd, 1) <0) {
      perror("nd: listen()");
      return 5;
    }
    
    if ((debug >= 1)) {
      printf("Now we are listening.\n");
    }

again:

    acc_len=sizeof(struct sockaddr_in);
    if ((afd=accept(sfd, (struct sockaddr *) &saddr, &acc_len)) <0) {
      perror("nd: accept()");
      return 5;
    }

    if (!(pid=fork())) { /* I'm the child */
      int myafd;
      char buf[256];
      int len;

      myafd=afd;
      write(myafd, "1", 1);

      len=read(myafd, &buf, 255);
      printf("%s", &buf);
      
  
      shutdown(myafd, SHUT_RDWR);

      close(myafd);

      exit(0);

    } else { /* I'm the father */

      if ((debug >= 1)) {
        printf("We just accepted the connection, fd=%d\n", afd);
      }
      close(afd);
      goto again;

    }
    
  } else { /* Active (client) side */

    char buf[256];
    int len;

    if (!(hen=gethostbyname(argv[1]))) {
      herror("nd: gethostbyname()");
      return 5;
    }

    memcpy(&saddr.sin_addr.s_addr, hen->h_addr, sizeof(saddr.sin_addr.s_addr));
    
    if (connect(sfd, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in)) <0) {
      perror("nd: connect()");
      return 5;
    }
    
    len=read(sfd, &buf, 255);
    printf("%s", &buf);
    
    if ((debug >= 1)) {
        write(sfd,"Hello server, thank you for accepting my connection.\r\n",54);
    }
    shutdown(sfd, SHUT_RDWR);
    close(sfd);

  }
}