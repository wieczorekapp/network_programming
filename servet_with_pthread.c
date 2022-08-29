#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

struct arg_struct{
    int cfd;
};

void *tests(void *arguments){
    struct arg_struct* argumenty = arguments;
	char ok[2] = "ok";
	char indeks[6];
	read(argumenty->cfd, &indeks, 6);
    printf("%s\n", indeks);
    printf("robie cos\n");
    write(argumenty->cfd, &ok, 2);
	close(argumenty->cfd);
    free(argumenty);
    return EXIT_SUCCESS;
    }

int main(int argc, char *argv[])
{
    struct sockaddr_in myaddr;
    myaddr.sin_family = PF_INET;
    myaddr.sin_port = htons(1237);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    struct sockaddr_in clientaddr;
    
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    int on =1;
    bind(fd, (struct sockaddr*) &myaddr, sizeof(myaddr));
    listen(fd, 10);
    socklen_t s = sizeof(clientaddr);
    pthread_t thread1;

        
    while(1)
    {
        struct arg_struct* struktura = malloc(sizeof(struct arg_struct));
        struktura->cfd = accept(fd, (struct sockaddr*) &clientaddr, &s);
        pthread_create(&thread1, NULL,tests, struktura);
      //  pthread_detach(thread1);
    }
    
    close(fd);
}
