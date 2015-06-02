/*************************************************************************
  > File Name: ./src/do_puts.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Fri 03 Apr 2015 07:30:19 PM CST
 ************************************************************************/

#include"FTP_client.h"
//client_puts
void client_puts(int fd_client, int role)
{
	if(role == 3){
		printf("you don't have permission!\n");
		return ;
	}else{
		char dir[128] = "0";
		chdir("../file");
		getcwd(dir, sizeof(dir));
		int send_len ;
		char name[128] = "0";
		char msg[1024] = "0";
		char file_name[128] = "0";
		memset(&name, 0 ,128);
		printf("please input the up file;\n");
		fflush(stdin);
		fgets(file_name, 128, stdin);

		send_len = strlen(file_name);
		send_buf(fd_client, (char*)&send_len, 4);
		send_buf(fd_client, file_name, send_len);
		sprintf(name,"%s/%s",dir,file_name);
		name[strlen(name) - 1] = '\0';
		printf("%s\n", name);
		int fd_file = open(name,O_RDONLY);
		if(fd_file == -1){
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
}

