/*************************************************************************
	> File Name: ./src/do_gets.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 07:28:38 PM CST
 ************************************************************************/

#include"FTP_client.h"
//client_gets
void client_gets(int fd_client)
{
	int recv_len ;
	int send_len ;
	char name[128] = "0";
	char msg[1024];
	char down_file[128] = "0";
	memset(&name, 0 ,128);
	printf("please input the down filed:\n");
	fflush(stdin);
	fgets(msg ,128, stdin);
	send_len = strlen(msg);
	send_buf(fd_client, (char*)&send_len, 4);
	send_buf(fd_client, msg, send_len);
	printf("pleace call in down file's name:\n");
	fflush(stdin);
    fgets(name, 128, stdin);
	name[strlen(name) - 1] = '\0';

	sprintf(down_file, "%s/%s", "../file/", name);
	int fd_file = open (down_file, O_WRONLY | O_CREAT, 0666);
	if(fd_file == -1)
	{
		perror("open\n");
		exit(1);
	}
	int recv_sum = 0 ;
	while(1)
	{
		memset(msg, 0 , 1024);
		recv_buf(fd_client, (char*)&recv_len, 4);
		if(recv_len == 0)
		{
			close(fd_file);
			break;
		}
		recv_sum += recv_buf(fd_client, msg, recv_len);
		write(fd_file, msg, recv_len );
		system("clear");
		printf("downloading...%.2fkbs\n",(double)recv_sum /1024);
	}
	printf("recv complient!\n");

}
