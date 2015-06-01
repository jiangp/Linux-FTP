/*************************************************************************
	> File Name: ./include/FTP_client.h
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 07:24:52 PM CST
 ************************************************************************/

#ifndef _FTP_CLIENT_H
#define _FTP_CLIENT_H

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<dirent.h>
#include<fcntl.h>
//#define SER_IP "192.168.1.78"
//#define SER_PORT 1234

#define MY_ASSERT(flag, msg) do{flag || (printf("%s\n",msg), exit(1), 0);}while(0)	


void do_init(int fd_client);
void user_login(int fd_client);
void do_commind(int fd_client);
void vector_do_commind(int fd_client);
void client_cd(int fd_client);
void client_gets(int fd_client);
void client_puts(int fd_client);
void client_remove(int fd_client);
void client_mkdir(int fd_client);
void client_rmdir(int fd_client);
void do_cd(char *buf);
int send_buf(int sfd, char *buf, int len);
int recv_buf(int sfd, char *buf, int len);
#endif
