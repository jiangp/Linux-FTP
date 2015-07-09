/*************************************************************************
  > File Name: main.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 2 mar 2015 09:41:29 AM CST
 ************************************************************************/
#include"FTP_server.h"
//main
int main(int argc ,  char *argv[])
{
	int fd_listen, fd_client;
	MY_ASSERT((fd_listen = socket(AF_INET, SOCK_STREAM , 0)) != -1 ,"listen socket init");//socket


	struct sockaddr_in seraddr, clientaddr;
	socklen_t sock_len = sizeof(clientaddr);
	memset(&seraddr, 0, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[2]) );
	seraddr.sin_addr.s_addr = inet_addr(argv[1]);
	MY_ASSERT(bind(fd_listen, (struct sockaddr*)&seraddr, sizeof(seraddr))==0, "bind");//bind

	MY_ASSERT(listen(fd_listen, 5) == 0, "listen");//listen


	while(1)
	{
		sock_len =sizeof(clientaddr);
		memset(&clientaddr, 0, sock_len);
		fd_client = accept(fd_listen ,(struct sockaddr*)&clientaddr, &sock_len );
		printf("client %s:%d connect!\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
        if(fork() == 0)
		{
			close(fd_listen);
			child_main(fd_client);
			close(fd_client);
			exit(1);
		}
		close(fd_client);
 
	}
}
