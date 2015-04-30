/*************************************************************************
	> File Name: ./src/do_cd.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:37:56 PM CST
 ************************************************************************/

#include"FTP_server.h"

//do_cd
void do_cd(int fd_client, char* buf,int len)
{
	int index, i;
	char file[128] = "0";

	buf[strlen(buf) - 1 ] ='\0';
	if(strcmp(buf,"cd ..") == 0)
	{
		chdir("..");
		send(fd_client, "ready", 6, 0);
	
	}else if(strcmp(buf,"cd ..") != 0)
	{
		if(buf[2] == ' ')
		{
			for(index = 3; buf[index] != '\0'; ++index){

				file[index - 3]= buf[index];
			}
			i = chdir(file);
			if(i == 0){

				send(fd_client, "ready", 6, 0);	

			}else{

				strcpy(file,"commind error");
				send(fd_client, file, sizeof(file),0);
			}
		}else{
				strcpy(file,"commind error");
				send(fd_client, file, sizeof(file),0);
		}
	}
}
