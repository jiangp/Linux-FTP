/*************************************************************************
	> File Name: ./src/Child_main.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Mon 06 Apr 2015 02:02:15 PM CST
 ************************************************************************/

#include"FTP_server.h"
void child_main(int fd)//add a pro socket
{
	int fd_client;
	char flag = 1;
	while(1)
	{
		recv_fd(fd, &fd_client);
		if(signal(SIGCHLD, SIG_IGN) == SIG_ERR)
			return ;

		handle(fd_client);	
		write(fd, &flag, sizeof(flag));	
		//the pipe child -> father is close
	    //should try fcntl beacse is not jam 
		//the pipo ls jam  epoll errpor  
		//the sockpair also error  T_T 
		//popen .....
		//mkfifo ... 
		//fcntl is ok
	}
}
