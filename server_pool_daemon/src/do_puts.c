/*************************************************************************
	> File Name: ./src/do_puts.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:44:12 PM CST
 ************************************************************************/

#include"FTP_server.h"
//do_puts
void do_puts(int fd_client)
{
	char dir[128] = "0";
	getcwd(dir, sizeof(dir));
	int recv_len ;
	char name[128] = "0" ;
	char msg[1024] = "0" ;
	char file_name[128] = "0";
	
	/*get name*/
	memset(&file_name, 0, 128);
	recv_buf(fd_client, (char*)&recv_len, 4);
	recv_buf(fd_client, file_name, recv_len);

	sprintf(name ,"%s/%s", dir, file_name);
	name[strlen(name) - 1] = '\0';
	
	/*open file*/
	int fd_file = open(name, O_WRONLY | O_CREAT, 0666);
	if(fd_file == -1)
	{
		perror("error open\n");
		exit(1);
	}

	/*download*/
	int recv_sum = 0;
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
		printf("downloading...%.2fkbs\n", (double)recv_sum /1024);
	}
	printf("recv complient!\n");

}
