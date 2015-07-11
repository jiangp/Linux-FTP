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

/***error handle mechanism ****/
#define MY_ASSERT(flag, msg) do{flag || (printf("%s\n",msg), exit(1), 0);}while(0)

/*the child sate*/
typedef struct child_tag
{
	int child_fd;
	int child_pid;
	int child_busy;
	struct child_tag *m_next;
	struct child_tag *m_head;
}child_t, *pchild_t;

/*the account infor*/
typedef struct account
{
	char m_name[128];
	char m_passwd[128];
	int m_role;
	struct account *m_next;
}ACCOUNT, *pACCOUNT;

/*the user's information*/
typedef struct user_infor
{
	char m_name[128];
	char m_passwd[128];
	char m_path[128];
	struct user_infor *m_next;
}USER, *pUSER;


void child_main(int fd_read);
void make_child(pchild_t *phead_child, int nchild, int n);
void handle(int fd_client);
void send_fd(int sockfd, int fd);
void recv_fd(int sockfd, int *fd);
void do_ls(int fd_client);
void do_pwd(int fd_client);
void do_cd(int fd_client, char *buf);
void do_gets(int fd_client, int role);
void do_puts(int fd_client, int role);
void do_remove(int fd_client, char *buf, int role);
void do_mkdir(int fd_client, char *buf, int role);
void do_rmdir(int fd_client, char *buf, int role);
void do_person(int role, char *path);
int send_buf(int sfd, char *buf, int len);
int recv_buf(int sfd, char *buf, int len);


#endif
