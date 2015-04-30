/*************************************************************************
	> File Name: do_ls.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:33:35 PM CST
 ************************************************************************/

#include"FTP_server.h"

//do_ls
void do_ls(int fd_client)
{
	char dir[128] = "0";
	DIR *pdir = opendir(getcwd(dir,sizeof(dir)));
	char name[128] = "0";
	char buf[1024] = "0";
	if(pdir == NULL)
	{
		perror("opendir\n");
		exit(1);
	}
	struct dirent* pent;
	struct stat mystat;
	while((pent = readdir(pdir)) != NULL)
	{
    	if(strcmp(".",pent->d_name) == 0||strcmp("..",pent->d_name) == 0)
    	{
			continue;
		}
		memset(name, 0, 128);
		sprintf(name, "%s/%s", dir, pent->d_name);
	    memset(&mystat, 0, sizeof(mystat));

    	if(lstat(name, &mystat) == -1)
		{
	    	perror("error");
			break;
		}
		else
		{		
			memset(&buf, 0 ,sizeof(buf));
			sprintf(buf, "%s %c %lu",pent->d_name,pent->d_type,mystat.st_size);
	    	send(fd_client, buf, strlen(buf),0);
			sleep(1);
     	

		}
	}
	memset(&buf,0 ,strlen(buf));
	strcpy(buf,"OK");
	send(fd_client,buf,strlen(buf),0);
	closedir(pdir);
									
}

