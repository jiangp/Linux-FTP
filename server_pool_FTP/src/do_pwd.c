/*************************************************************************
	> File Name: ./src/do_pwd.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:36:02 PM CST
 ************************************************************************/

#include"FTP_server.h"

//do_pwd
void do_pwd(int fd_client)
{
	char buf[128] = "0";
	getcwd(buf, sizeof(buf));
    send(fd_client,buf,sizeof(buf),0);
}
