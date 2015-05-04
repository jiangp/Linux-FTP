/*************************************************************************
  > File Name: handle.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 02 Mar 2015 04:49:19 PM CST
 ************************************************************************/
#include<mysql/mysql.h>
#include"FTP_server.h"
#include"User_init.h"

//fork  handle
void handle(int fd_client)
{
	chdir("../file/");
	MYSQL my_connection;

	/*init sql porint*/
	if(!mysql_init(&my_connection)){
		perror("mysql_init fail!\n");
		return ;
	
	}
	/*connect mysql*/
	if(!(mysql_real_connect(&my_connection, "localhost", \
					"root", "666", "FTP_SQL", 3306, NULL, \
					CLIENT_MULTI_STATEMENTS))){
		perror("mysql_connect fail!\n");
		mysql_close(&my_connection);
		return ;
	
	}
//	int l = User_init(&my_connection, fd_client);
	if(User_init(&my_connection, fd_client) < 0){
		printf("User_init\n"); 
		mysql_close(&my_connection);
		return ;
	}
		


/*	the file list login
 	pACCOUNT account_list = NULL;
	pUSER user_list = NULL;
	system_init("../conf/config", &account_list, &user_list);
	int l = User_init(&account_list, fd_client);
	if(l < 0){
		printf("User_init\n"); 
		return ;
	}*/

	while(1)
	{
		char buf[1024] = "0";
		memset(buf, 0 ,1024);
		if(recv(fd_client, buf, sizeof(buf), 0) == 0){
			printf("one client exit.\n");
			close(fd_client);
			mysql_close(&my_connection);
			break ;
		
		}else{	
			if(strncmp(buf, "ls", 2) == 0){
				do_ls(fd_client);
			}
			else if(strncmp(buf, "gets", 4) == 0){
				do_gets(fd_client);

			}
			else if(strncmp(buf, "puts", 4) == 0){
				do_puts(fd_client);
			
			}
			else if(strncmp(buf, "cd", 2) ==0 ){
				do_cd(fd_client,buf,strlen(buf));
			
			}
			else if(strncmp(buf,"pwd",3) == 0){
				do_pwd(fd_client);
			
			}
			else if(strncmp(buf, "remove", 6) == 0){
				do_remove(fd_client);
			
			}
			else{
				continue;
			
			}
		}
	}	
}

