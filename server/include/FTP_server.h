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

/*** Macro defintion IP and PORT***/
//#define SER_IP "192.168.1."
//#define SER_PORT 1234

/***error handle mechanism ****/
//#define ADDR "../file/addr.txt"
#define MY_ASSERT(flag, msg) do{flag || (printf("%s\n",msg), exit(1), 0);}while(0)



void child_main(int fd_client);
void do_ls(int fd_client);
void do_pwd(int fd_client);
void do_cd(int fd_client, char* buf,int len);
void do_gets(int fd_client);
void do_puts(int fd_client);
int do_remove(int fd_client);
int send_buf(int sfd, char *buf, int len);
int recv_buf(int sfd, char *buf, int len);


#endif
