/*************************************************************************
  > File Name: handle.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 02 Mar 2015 04:49:19 PM CST
 ************************************************************************/
#include<mysql/mysql.h>
#include"FTP_server.h"
#include"userinit.h"
#define HomePath "/home/arwen/program/Project_FTP/server_pool_FTP/file"

//fork  handle
void handle(int fd_client)
{
	chdir(HomePath);
	MYSQL my_connection;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
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
	char query[128] = "0";
	int res;
	char *UserName = User_init(&my_connection, fd_client);
	if(UserName == NULL){
		printf("User_init\n"); 
		mysql_close(&my_connection);
		return ;
	}
	else if(strncmp(UserName, "vector", 6) == 0){
		printf("Is a vector!\n");
		ServerCmd(fd_client, "path", 3);
	}
	else{
		sprintf(query, "%s%s%s", "SELECT * from ACCOUNT where Name='", UserName, "';");
//		printf("%s\n", query);
		res = mysql_query(&my_connection, query);
		if(!res){
			result = mysql_store_result(&my_connection);
			if(result){
				sql_row = mysql_fetch_row(result);
				ServerCmd(fd_client, sql_row[4], atoi(sql_row[3]));
			}
		}
	}
	mysql_close(&my_connection);	
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
void ServerCmd(int fd_client, char *path, int role)
{
	char buf[1024] = "0";
	while(1)
	{
		memset(buf, 0 ,1024);
		if(recv(fd_client, buf, sizeof(buf), 0) == 0){
			printf("one client exit.\n");
			close(fd_client);
			break ;
		
		}else{	
			if(strncmp(buf, "ls", 2) == 0){
				do_ls(fd_client);
			
			}
			else if(strncmp(buf, "gets", 4) == 0){
				 do_gets(fd_client, role);
				
			}
			else if(strncmp(buf, "puts", 4) == 0){
				do_puts(fd_client, role);
			
			}
			else if(strncmp(buf, "cd", 2) == 0 ){
				do_cd(fd_client, buf);
			
			}
			else if(strncmp(buf, "pwd", 3) == 0){
				do_pwd(fd_client);
			
			}
			else if(strncmp(buf, "remove", 6) == 0){
				do_remove(fd_client, buf, role);
			
			}
			else if(strncmp(buf, "mkdir", 5) == 0){
				do_mkdir(fd_client, buf, role);
			
			}
			else if(strncmp(buf, "rmdir", 5) == 0){
				do_rmdir(fd_client, buf, role);

			}
			else if(strncmp(buf, "home", 4) == 0){
				chdir(HomePath);
			
			}
			else if(strncmp(buf, "person", 6) == 0){
				do_person(role, path);
			
			}
		}
	}	
}

