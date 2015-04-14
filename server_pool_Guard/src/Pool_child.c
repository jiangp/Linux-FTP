/*************************************************************************
	> File Name: ./src/Pool_child.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Mon 06 Apr 2015 01:34:56 PM CST
 ************************************************************************/

#include"FTP_server.h"
#include<fcntl.h>
void make_child(pchild_t childs, int nchild)
{
	int index = 0;
	while(nchild > 0)
	{
		int fds[2];
		if(-1 == socketpair(AF_LOCAL, SOCK_STREAM, 0, fds))
		{
			perror("socketpair!\n");
			exit(1);
		}
		pid_t pid = fork();
		if(pid == 0)
		{	
			close(fds[1]);
			child_main(fds[0]);
			exit(1);
		}
		close(fds[0]);
		childs[index].child_pid = pid;
		childs[index].child_fd = fds[1];
		childs[index].child_busy = 0;
		index++;
		nchild--;
	}
}
