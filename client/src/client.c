/*************************************************************************
  > File Name: client.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Fri 27 Feb 2015 10:43:15 AM CST
 ************************************************************************/

#include"FTP_client.h"
int main(int argc ,  char *argv[])
{
//  config("../confg"); 
	int fd_client;
	MY_ASSERT((fd_client = socket(AF_INET,SOCK_STREAM ,0))!=-1 ,"listen socket init");
	struct sockaddr_in cliaddr;
	memset(&cliaddr, 0, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(atoi(argv[2]));
	cliaddr.sin_addr.s_addr = inet_addr(argv[1]);

	MY_ASSERT(connect(fd_client, (struct sockaddr*)&cliaddr,sizeof(cliaddr)) ==0,"connect");
	chdir("../file");
	/*Mysql init*/
	do_init(fd_client);
	return 0;
}

