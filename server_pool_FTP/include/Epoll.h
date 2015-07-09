/*************************************************************************
	> File Name:Epoll.h
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Mon 27 Apr 2015 11:23:35 AM CST
 ************************************************************************/

#ifndef EPOLL_H
#define EPOLL_H
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<sys/types.h>

#endif

int Epoll_init(int fd_listen, int size)
{
	int epoll_fd;
	if((epoll_fd = epoll_create(size)) == -1){
		perror("epool_create\n");
		exit(1);
	}
	struct epoll_event my_event;
	my_event.events = EPOLLIN;
	my_event.data.fd = fd_listen;
	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd_listen, &my_event) == -1){
		perror("epoll_ctl\n");
		exit(1);
	}
	return epoll_fd;
}


/*
int Epoll_wait(int epoll_fd)
{
	int ready_events;
	memset(&my_events, 0, sizeof(my_events));
	if((ready_events = epoll_wait(epoll_fd, my_events, 1024, -1)) == -1){
		perror("epoll_wait\n");
		continue;
	}
	return ready_events;
}*/
