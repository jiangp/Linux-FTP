/*************************************************************************
	> File Name: ./src/do_remove.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:40:36 PM CST
 ************************************************************************/

#include"FTP_server.h"

//remove
int do_remove(int fd_client)
{
	char dir[128] = "0";
	getcwd(dir, sizeof(dir));
	int recv_len ;
	char name[128] = "0";
	char file_name[128] = "0";
	recv_buf(fd_client, (char*)&recv_len, 4);
	recv_buf(fd_client, file_name, recv_len);

	sprintf(name,"%s/%s",dir,file_name);
	name[strlen(name)-1] = '\0';

	remove(name);
	recv_buf(fd_client, (char*)&recv_len, 4);
	if(recv_len == 0)
	{
		return 0;
	}
	return 0;	
}
