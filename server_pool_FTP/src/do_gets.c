/*************************************************************************
  > File Name: ./src/do_gets.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Fri 03 Apr 2015 12:42:11 PM CST
 ************************************************************************/

#include"FTP_server.h"

void downDir(int fd_client, char *);
void downFile(int fd_client, char *);
//do_gets
void do_gets(int fd_client, int role)
{
	if(role == 3){
		return ;
	}
	else{
		struct stat mystat;
		int send_len;
		char file_name[256] = "0";

		memset(&file_name, 0 , 256);
		recv_buf(fd_client, (char*)&send_len, 4);
		recv_buf(fd_client, file_name, send_len);

		file_name[strlen(file_name) - 1] = '\0';

		lstat(file_name, &mystat);
		if(S_ISDIR(mystat.st_mode)){
			send(fd_client, "dir", 8, 0);
			downDir(fd_client, file_name);		
		}
		else{
			downFile(fd_client, file_name);
		}

		printf("send complient!\n");
	}
}


void downDir(int fd_client, char *dir_name)
{
	DIR *pdir = opendir(dir_name);
	if(pdir == NULL){
		perror("opedir!\n");
		send(fd_client, "over", 8, 0);
		return ;
	}
	chdir(dir_name);
	struct dirent* mydirent;
	struct stat mystat;
	while((mydirent = readdir(pdir)) != NULL){
		send(fd_client, "continue", 8, 0);
		stat(mydirent->d_name, &mystat);
		if(S_ISDIR(mystat.st_mode)){
			if(strncmp(mydirent->d_name, ".", 1) == 0){
				send(fd_client, "nodir", 8, 0);
				continue;
			}
			else{
				send(fd_client, "dir", 8, 0);
				send(fd_client, mydirent->d_name, sizeof(mydirent->d_name), 0);
				//printf("%s: %d\n", mydirent->d_name, sizeof(mydirent->d_name));
				downDir(fd_client, mydirent->d_name);	
			}
		}
		else{
			downFile(fd_client, (mydirent->d_name));
		}
	}
	send(fd_client, "over", 8, 0);
	chdir("..");
	closedir(pdir);
}


void downFile(int fd_client, char *name)
{
	send(fd_client, "file", 8, 0);
	send(fd_client, name, 256, 0);
	int send_len;
	char msg[1024];
	char file_name[256] = "0";
	char dir[256] = "0";
	getcwd(dir, sizeof(dir));
	sprintf(file_name,"%s/%s",dir, name);
	name[strlen(file_name) -1] = '\0';
	int fd_file = open(file_name, O_RDONLY);
	if(fd_file == -1){
		perror("fd_file fail!\n");
		exit(1);
	}
	while(memset(&msg, 0, 1024), (send_len = read(fd_file, msg, 1024) ) != 0){
		if(send_len == -1){
			perror("read\n");
			exit(1);
		}
		send_buf(fd_client, (char*)&send_len, 4);
		send_buf(fd_client, msg, send_len);
	}
	send_len = 0;
	send_buf(fd_client, (char*)&send_len, 4);
	close(fd_file);

}
