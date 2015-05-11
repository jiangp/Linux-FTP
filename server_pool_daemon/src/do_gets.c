/*************************************************************************
	> File Name: ./src/do_gets.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:42:11 PM CST
 ************************************************************************/

#include"FTP_server.h"

//do_gets
void do_gets(int fd_client)
{
	char dir[128] ="0";
	getcwd(dir,sizeof(dir));

	int recv_len;
	int send_len;
	char file_name[128]="0";
	char name[128] ="0";
	char msg[1024];
	memset(&file_name, 0 , 128);
	recv_buf(fd_client, (char*)&send_len, 4);
	recv(fd_client, file_name, send_len, 0);
	sprintf(name,"%s/%s",dir, file_name);

	name[strlen(name) - 1] = '\0';
	int fd_file = open(name,O_RDONLY);
	if(fd_file == -1)
	{
		perror("fd_file\n");
		exit(1);
	}
	while(memset(&msg,0,1024), (send_len = read(fd_file, msg, 1024) )!= 0)
	{
		if(send_len ==-1){

			perror("read\n");
			exit(1);
		}

		send_buf(fd_client, (char*)&send_len,4);
		send_buf(fd_client,msg,send_len);
	}
	send_len = 0;
	send_buf(fd_client, (char*)&send_len,4);

}
