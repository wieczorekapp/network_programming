#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(1236);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	printf("%s", gethostbyname(argv[1]));
    char buff[] = "";

    int fd = socket(PF_INET, SOCK_STREAM, 0);
    int on = 1;;
//lab-net-9.cs.put.poznan.pl
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    
    
    connect(fd, (struct sockaddr*) & addr, sizeof(addr));
    write(fd, "kek", 4);
    printf("Test: %s", buff);
    close(fd);
}
