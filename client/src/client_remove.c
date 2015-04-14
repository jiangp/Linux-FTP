/*************************************************************************
	> File Name: ./src/client_remove.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 07:33:29 PM CST
 ************************************************************************/

#include"FTP_client.h"

//client_remove
void client_remove(int fd_client)
{
	int send_len ;
	char file_name[128] = "0";
	printf("please input dele file_name:\n");
	fflush(stdin);
	fgets(file_name, 128, stdin);

    send_len = strlen(file_name);
	send_buf(fd_client, (char*)&send_len, 4);
	send_buf(fd_client, file_name, send_len);

	printf("remove over!\n");
	send_len = 0;
	send_buf(fd_client,(char*)&send_len,4);
}


