#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>
#include <signal.h>


// funkcja do obsługi sygnału SIGCHLD, odebranie go, by uniknąć zombi
void childend(int signo){ wait(NULL); printf("umar\n");}


int main(int argc, char *argv[])
{
    struct sockaddr_in myaddr;
    signal(SIGCHLD, childend);
    
    myaddr.sin_family = PF_INET;
    myaddr.sin_port = htons(1237);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    struct sockaddr_in clientaddr;
    
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    int on =1;
    bind(fd, (struct sockaddr*) &myaddr, sizeof(myaddr));
    listen(fd, 10);
    socklen_t s = sizeof(clientaddr);

    char indeks[6];
    char ok[2] = "ok";
    char error[6] = "error";

    while(1)
    {
    int cfd = accept(fd, (struct sockaddr*) &clientaddr, &s);
	if(fork() > 0){
		close(cfd);
	}else{
	    close(fd);
	    read(cfd, &indeks, 4);
	    printf("%s\n", indeks);
	    write(cfd, &ok, 2);
	    close(cfd);
	    exit(0);
	}
    }
   
    close(fd);
}
