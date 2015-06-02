/*************************************************************************
  > File Name: ./src/client_remove.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Fri 03 Apr 2015 07:33:29 PM CST
 ************************************************************************/

#include"FTP_client.h"

//client_remove
void client_remove(int fd_client, int role)
{
	if(role == 3){
		printf("you don't have permission!\n");
		return ;
	}else{
		char buf[8] = "0";
		recv(fd_client, buf, sizeof(buf), 0);
		if(strncmp(buf, "no file", 7) == 0)
			printf("no the name's file!\n");
		else
			return ;
	}
}


//clinet_mkdir
void client_mkdir(int fd_client,int role)
{
	if(role == 3){
		printf("you don't have permission!\n");
		return ;
	}else{
		char buf[8] = "0";
		recv(fd_client, buf, sizeof(buf), 0);
		if(strncmp(buf, "have", 6) == 0)
			printf("have the name's dirent!\n");
		else if(strncmp(buf, "fail",4) == 0)
			printf("you dont have permition!\n");
		else if(strncmp(buf, "success", 7) == 0)
			return ;
	}
}

//client_rmdir
void client_rmdir(int fd_client, int role)
{
	if(role == 3){
		printf("you don't have permission!\n");
		return;
	}else{
		char buf[8] = "0";
		recv(fd_client, buf, sizeof(buf), 0);
		if(strncmp(buf, "no dir", 6) == 0)
			printf("no the name's dirent!\n");
		else
			return ;
	}
}

//client_person
void client_person(int role)
{
	if(role == 3){
		printf("please enroll!\n");
			return;
	}
}



//client_cd
void client_cd(int fd_client)
{
	char buf[8] = "0";
	recv(fd_client, buf, sizeof(buf), 0);
	if(strncmp(buf, "have", 6) == 0)
		printf("have the top dir!\n");
	else if(strncmp(buf, "error",5) == 0)
		printf("the commind error!\n");
	else if(strncmp(buf, "ready", 5) == 0)
		return ;
}

//client_!cd
void do_cd(char *buf)
{
	int index, jndex;
	char path[128] = "0";
	for(jndex = 4; jndex != 128; ++jndex){
		if(buf[jndex] == ' ')
			continue;
		for(index = 0; index != 124; ++index){
			path[index] = buf[jndex]; 
			++jndex;
		}
		break;
	}
	path[strlen(path)-1] = '\0';				
	chdir(path);
}
