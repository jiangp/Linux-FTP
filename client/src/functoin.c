/*************************************************************************
  > File Name: function.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Fri 29 May 2015 06:01:53 PM CST
 ************************************************************************/

#include"FTP_client.h"

void do_init(int fd_client)
{
	char buf[1024]= "0";
	printf("please change login ,enroll ,vector or exit\n");
	fflush(stdin);
	fgets(buf, 10, stdin);
	buf[strlen(buf) - 1] = '\0';
	send(fd_client, buf, 8, 0);
	if(strncmp(buf, "exit", 4) == 0){
		printf("exit success!\n");
		return ;
	
	}else if(strncmp(buf, "vector", 5) == 0){
		printf("you are a vector user\n");
	    /*the cmd*/
		do_commind(fd_client, 3);
	}else{
		/*the login*/
		user_login(fd_client);
		/*the cmd*/
		do_commind(fd_client, 1);
	}
	
}

void do_commind(int fd_client, int role)
{
	char buf[1024] = "0";
	char line[1024] = "0";
	char name[128] = "0";
	unsigned long size;
	char stat;

	while(1){
		memset(buf , 0, 1024);
		memset(line, 0, 1024);
		fgets(buf, 1024, stdin);
		send(fd_client, buf, 1024, 0);

		if(strncmp(buf, "ls", 2) == 0){
			while(memset(buf,0 ,sizeof(buf)),recv(fd_client, buf, sizeof(buf),0)!=-1){
				if(strncmp(buf,"OK",2)!=0){
					sscanf(buf, "%s %c %lu",name,&stat,&size);
					if(stat & DT_DIR)
						printf("    \033[34m%-30s\033[0m -------- %lu b\n",name,size);
					else
						printf("    %-30s -------- %lu b\n",name,size);

				}else{
					break;
				}
			}
		}
		else if(strncmp(buf, "cd", 2) == 0){
			client_cd(fd_client);

		}
		else if(strncmp(buf, "pwd", 3) == 0){
			recv(fd_client, line, sizeof(line), 0);
			printf("%s\n",line);

		}
		else if(strncmp(buf, "gets", 4) == 0){
			client_gets(fd_client, role);

		}
		else if(strncmp(buf, "puts", 4) == 0){
			client_puts(fd_client, role);

		}
		else if(strncmp(buf, "remove", 6) == 0){
			client_remove(fd_client, role);

		}
		else if(strncmp(buf, "mkdir", 5) == 0){
			client_mkdir(fd_client, role);	

		}
		else if(strncmp(buf, "rmdir", 5) == 0){
			client_rmdir(fd_client, role);

		}
		else if(strncmp(buf, "clear", 5) == 0){
			system("clear");		

		}
		else if(strncmp(buf, "!ls", 3) == 0){
			system("ls");

		}
		else if(strncmp(buf, "!cd", 3) == 0){
			do_cd(buf);

		}
		else if(strncmp(buf, "!pwd", 4) == 0){
			printf("%s\n",getcwd(NULL, 0));

		}
		else if(strncmp(buf, "quit", 4) == 0){
			return ;

		}
		else if(strncmp(buf, "home", 4) == 0){
		
		}
		else if(strncmp(buf, "person", 6) == 0){
			client_person(role);
		}
		else{
			printf("error command!\n");
		}
	}
}



void user_login(int fd_client)
{
	char name[128] = "0";
	char passwd[128] = "0";
	char buf[16] = "0";
	int cnt = 0;
	while(cnt < 3){
		++cnt;
		/*put in name*/
		printf("name: ");
		fflush(stdin);
		memset(name, 0, 128);
		fgets(name, 128, stdin);
		name[strlen(name) - 1] = '\0';
		send(fd_client, name, 128, 0);

		/*put in passwd*/
		printf("passwd: ");
		fflush(stdin);
		memset(passwd, 0, 128);
		fgets(passwd, 128, stdin);
		passwd[strlen(passwd) - 1] = '\0';
		send(fd_client, passwd, 128, 0);	

		memset(buf, 0, 16);
		recv(fd_client, buf, 8, 0);	
		if(strncmp(buf, "success", 7) == 0){
			printf("put in success\n");
			return ;
		}else if(strncmp(buf, "fail", 4) == 0){
			printf("please input again!\n");
			continue;
		}else if(strncmp(buf, "named", 5) == 0){
			printf("have user! input again!\n");
			continue;
		}
	}	

}
