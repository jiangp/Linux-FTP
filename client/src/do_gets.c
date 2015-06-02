/*************************************************************************
  > File Name: ./src/do_gets.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Fri 03 Apr 2015 07:28:38 PM CST
 ************************************************************************/

#include"FTP_client.h"

void down_dir(int fd_client, char *dir_name);
void down_file(int fd_client, char *name);
//client_gets
void client_gets(int fd_client, int role)
{
	if(role == 3){
		printf("you don't have permission!\n");
		return;
	}else{
		int send_len ;
		char name[256] = "0";
		char msg[1024] = "0";
		char dir[8] = "0";
		memset(&name, 0 ,256);
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
		recv(fd_client, dir, 8 , 0);

		if(strncmp(dir, "dir", 3) == 0){
			if(-1 == mkdir(name, 0777)){
				perror("makedir!\n");
				exit(1);
			}

			if(-1 == chdir(name)){
				perror("chdir!\n");
				exit(1);
			}
			down_dir(fd_client, name);
			//		chdir("..");
			printf("break a dir!\n");
		}
		else{
			down_file(fd_client, name);
		}
		printf("recv complient!\n");
	}
}

void down_dir(int fd_client, char *dir_name)
{
	char over[8] = "0";
	char dir[8] = "0";	
	char name[256] ="0";
	while(1){
		memset(over, 0, 8);
		recv(fd_client, over, 8, 0);
		if(strncmp(over, "over" ,4) == 0)
			break;
		recv(fd_client, dir, 8, 0);
		if(strncmp(dir, "nodir", 5) == 0){
			continue;	
		}
		else if(strncmp(dir, "dir", 3) == 0){
			memset(name, 0, 256);
			recv(fd_client, name, 256, 0);
			//			printf("%s: %d\n", name, sizeof(name));
			mkdir(name, 0777);
			chdir(name);
			down_dir(fd_client, name);
		}
		else{
			down_file(fd_client, dir_name);
		}
	}
	chdir("..");
}


void down_file(int fd_client, char *name)
{
	int recv_len;
	char msg[1024]= "0";
	char down_file[246] = "0";
	memset(name, 0 ,256);
	recv(fd_client, name, 256, 0);
	sprintf(down_file, "%s/%s", getcwd(NULL, 0), name);
	int fd_file = open (down_file, O_WRONLY | O_CREAT, 0666);
	if(fd_file == -1){
		perror("open fail\n");
		exit(1);
	}
	int recv_sum = 0 ;
	while(1){
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
}

