/*************************************************************************
	> File Name: ./include/FTP_server.h
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:15:53 PM CST
 ************************************************************************/

#ifndef _FTP_SERVER_H
#define _FTP_SERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<errno.h>
#include<signal.h>

/*** Macro defintion IP and PORT***/
//#define SER_IP "192.168.1."
//#define SER_PORT 1234

/***error handle mechanism ****/
#define MY_ASSERT(flag, msg) do{flag || (printf("%s\n",msg), exit(1), 0);}while(0)

typedef struct child_tag
{
	int child_fd;
	int child_pid;
	int child_busy;
}child_t, *pchild_t;

void make_child(pchild_t childs, int nchild);
void child_main(int fd_client);
void handle(int fd_client);
void send_fd(int sockfd, int fd);
void recv_fd(int sockfd, int *fd);
void do_ls(int fd_client);
void do_pwd(int fd_client);
void do_cd(int fd_client, char* buf,int len);
void do_gets(int fd_client);
void do_puts(int fd_client);
int do_remove(int fd_client);
int send_buf(int sfd, char *buf, int len);
int recv_buf(int sfd, char *buf, int len);


#endif
