#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<string.h>
#include <sys/types.h>
#include <stdint.h>
#include <fcntl.h>

#define N 128
#define SERVERDEV "rgb_server_socket"
#define CLIENTDEV "jt808_client_socket"


//设置非阻塞
static void setnonblocking(int sockfd) {
    int flag = fcntl(sockfd, F_GETFL, 0);
    if (flag < 0) {
        perror("fcntl F_GETFL fail");
        return;
    }
    if (fcntl(sockfd, F_SETFL, flag | O_NONBLOCK) < 0) {
        perror("fcntl F_SETFL fail");
    }
}

//设置超时
static void settimeout(int sockfd) {
   // 设置超时
    struct timeval timeout;
    timeout.tv_sec = 1;//秒
    timeout.tv_usec = 0;//微秒
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
        perror("setsockopt failed:");
    }
	return;
}

int main(int argc, const char *argv[])
{
	int N = 128;
	int n = 0;
	struct linger ling1;
	struct sockaddr_un serveraddr, clientaddr;
    int sockfd;
    char buf[N];
	socklen_t len = sizeof(serveraddr);
	unlink(CLIENTDEV);
    sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("fail to sockfd");
        return -1;
    }
	//setnonblocking(sockfd);
	settimeout(sockfd);
	ling1.l_onoff = 1;
	ling1.l_linger = 0;
	setsockopt(sockfd,SOL_SOCKET,SO_LINGER ,(const char*)&ling1,sizeof(ling1));

    serveraddr.sun_family = AF_LOCAL;
    strcpy(serveraddr.sun_path, SERVERDEV);

    clientaddr.sun_family = AF_LOCAL;
    strcpy(clientaddr.sun_path, CLIENTDEV);

    if(bind(sockfd, (struct sockaddr*)&clientaddr, sizeof(clientaddr)) < 0)
    {
        perror("fail to bind");
        return -1;
    }

    while(1)
    {
        printf("<client>");
        fgets(buf, N, stdin);
        if(sendto(sockfd, buf, N, 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
        {
            perror("fail to sendto");
            return -1;
        }
        if(strncmp(buf, "quit", 4) == 0)
        {
            break;
        }
		n = recvfrom(sockfd, buf, N, 0, (struct sockaddr*)&serveraddr, &len);
        if(n < 0)
        {
			printf("can not find data\n");
			continue;
        }
        printf("buf:%s\n", buf);
    }
	unlink(CLIENTDEV);
    close(sockfd);

    return 0;
}