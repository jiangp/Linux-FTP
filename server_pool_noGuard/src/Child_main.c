/*************************************************************************
	> File Name: ./src/Child_main.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Mon 06 Apr 2015 02:02:15 PM CST
 ************************************************************************/

#include"FTP_server.h"
void child_main(int fd_read)
{
	int fd_client;
	char flag = 1;
	while(1)
	{		
		recv_fd(fd_read, &fd_client);		
		handle(fd_client);
		write(fd_read, &flag, sizeof(flag));
		return ;
	}
}
