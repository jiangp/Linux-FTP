/*************************************************************************
	> File Name: ./src/do_remove.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:40:36 PM CST
 ************************************************************************/

#include"FTP_server.h"

//remove
void do_remove(int fd_client, char *buf)
{
	int buf_cnt, index;
	char filename[128] = "0";
	for(buf_cnt = 6; buf_cnt < 128; ++buf_cnt){
		if(buf[buf_cnt] == ' ')
			continue;
		for(index = 0; index < 123; ++index){
			filename[index] = buf[buf_cnt];
			++buf_cnt;
		}
	}
	filename[strlen(filename) - 1] ='\0';
	if(access(filename, 0) == 0){
		remove(filename);
		send(fd_client, "success", 8, 0);
	}
	else{
		send(fd_client, "no file", 8, 0);
	}
	
}


//mkdir
void do_mkdir(int fd_client, char *buf)
{
	int buf_cnt, index;
	char dirname[128] = "0";
	for(buf_cnt = 6; buf_cnt < 128; ++buf_cnt){
		if(buf[buf_cnt] == ' ')
			continue;
		for(index = 0; index < 123; ++index){
			dirname[index] = buf[buf_cnt];
			++buf_cnt;
		}
	}
	dirname[strlen(dirname) - 1] ='\0';
	if(access(dirname, 0) == -1){
		if(mkdir(dirname, 0777) == 0){
			send(fd_client, "sucess", 8, 0);
		}else{
			send(fd_client, "fail", 8, 0);
		}
	}else{
		send(fd_client, "have", 8, 0);
	}
}
//rmdir
void do_rmdir(int fd_client, char *buf)
{
	int buf_cnt, index;
	char dirname[128] = "0";
	char rmdir_cmd[128] = "0";
	for(buf_cnt = 6; buf_cnt < 128; ++buf_cnt){
		if(buf[buf_cnt] == ' ')
			continue;
		for(index = 0; index < 123; ++index){
			dirname[index] = buf[buf_cnt];
			++buf_cnt;
		}
	}
	dirname[strlen(dirname) - 1] ='\0';
	if(access(dirname, 0) == 0){
		sprintf(rmdir_cmd, "%s %s", "rm -rf", dirname);
		system(rmdir_cmd);
		send(fd_client, "success", 8, 0);
	}else{
		send(fd_client, "no dir", 8, 0);
	}
}

