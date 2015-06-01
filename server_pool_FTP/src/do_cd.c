/*************************************************************************
	> File Name: ./src/do_cd.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:37:56 PM CST
 ************************************************************************/

#include"FTP_server.h"

//do_cd
void do_cd(int fd_client, char *buf)
{
	int buf_cnt, index;
	char filename[128] = "0";
	char path[128] = "0";
	char msg[128] = "0";
	for(buf_cnt = 3; buf_cnt < 128; ++buf_cnt){ //去命令后多与空格
		if(buf[buf_cnt] == ' ')
			continue;
		for(index = 0; index < 125; ++index){
			filename[index] = buf[buf_cnt];
			++buf_cnt;
		}
	}
	filename[strlen(filename) - 1] ='\0';

	if(strncmp(buf, "cd ", 3) == 0){
		if(strcmp(filename, "..") == 0){  //判断为cd ..
			getcwd(path, sizeof(path));
			for(index = 0; index < 4; ++index){
				msg[index] = path[strlen(path) - 4 + index];
			}
			if(strncmp(msg, "file", 4) == 0){ // 已经为最上层文件夹 命令无效
				send(fd_client, "have", 8, 0);
				return;
			}
			else{
				chdir("..");                      //执行cd ..
				send(fd_client, "ready", 8, 0);
			}
		}else 
			if(chdir(filename) == 0){               // 进入文件夹
				send(fd_client, "ready", 8, 0);	
			}
			else{                                   //文件夹名字错误进入失败
				send(fd_client, "error", 8, 0);	
			}
	}
	else{
		send(fd_client, "error", 8, 0);
	}
}
