/*************************************************************************
	> File Name:Socket.h
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Mon 27 Apr 2015 10:17:57 AM CST
 *********************************************************************/
#ifndef _SOCKET_H
#define _SOCKET_H

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>

#endif

int Socket(char *IP, char *PORT)
{

	int fd_listen;
	if((fd_listen = socket(AF_INET,SOCK_STREAM , 0)) == -1){
		perror("socket\n");
		exit(1);
	}

	/*bind the ip and port*/
	struct sockaddr_in seraddr;
	memset(&seraddr, 0, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(PORT));
	seraddr.sin_addr.s_addr = inet_addr(IP);
	if(bind(fd_listen, (struct sockaddr*)&seraddr, sizeof(seraddr)) == -1) {
		perror("bind\n");
		exit(1);
	}

	if(listen(fd_listen, 5) == -1){
		perror("listen\n");
		exit(1);
	}
	return fd_listen ;
}
