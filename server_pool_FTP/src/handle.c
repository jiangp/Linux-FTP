/*************************************************************************
  > File Name: handle.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 02 Mar 2015 04:49:19 PM CST
 ************************************************************************/
#include<mysql/mysql.h>
#include"FTP_server.h"

#define HomePath "/home/arwen/project/Project_FTP/server_pool_FTP/file"



static int User_init(MYSQL *my_connection, int fd_client);
static void ServerCmd(int fd_client, char *path, int role);




static char user_name[128] = "0";
static int user_role = 0;
static char user_passwd[128] = "0";
static char user_path[128] = "0";


//fork  handle
void handle(int fd_client)
{
	chdir(HomePath);
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
	int uinit = User_init(&my_connection, fd_client);
	if(uinit == -1){
		printf("User_init\n"); 
		mysql_close(&my_connection);
		return ;
	}
	else if(uinit == 3){
		printf("Is a vector!\n");
		ServerCmd(fd_client, user_path, user_role);
	}
	else if(uinit == 2){
		printf("Is a user\n");
		ServerCmd(fd_client, user_path, user_role);
	}
	else if(uinit == 1){
		printf("Is a admin\n");
		ServerCmd(fd_client, user_path, user_role);	
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



/*
 * use to the user login and enroll and vector
 * when vector stcect return 
 * when login find from mysql
 * when enroll first find from ACCOUNT tables 
 * of haven't insert a new user and create a dir name user_name
 * */
int User_init(MYSQL *my_connection, int fd_client)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	
	int res, cnt = 0;
	char role[8] = "0";
	char query[1024] = "0";
	
	recv(fd_client, role, sizeof(role), 0);

	if(strncmp(role, "vector", 6) == 0){
		return 3;
	}
	else if(strncmp(role, "login", 5) == 0){

		while(cnt < 3){
			recv(fd_client, user_name, sizeof(user_name), 0);
			recv(fd_client, user_passwd, sizeof(user_passwd), 0);
			strcpy(query, "SELECT * from ACCOUNT where Name='");
			strcat(query, user_name);
			strcat(query, "';");
			res = mysql_query(my_connection, query);

			if(!res){
				result = mysql_store_result(my_connection);
				if(result){
					sql_row = mysql_fetch_row(result);
					if(sql_row){
						if(strcmp(sql_row[2], user_passwd) == 0){
							send(fd_client, "success", 8, 0);
							strcpy(user_path, sql_row[4]);
							user_role =atoi(sql_row[3]);
							return user_role;
						
						}
						else{
							send(fd_client, "fail", 8, 0);
							cnt++;	
						}
					}
					else{
						send(fd_client, "fail", 8, 0);
						cnt++;
					}
				}
			}
		}

	}else if(strncmp(role, "enroll", 6) == 0){

		while(1){
			memset(&user_name, 0 ,128);
			memset(&user_passwd, 0, 128);
			recv(fd_client, user_name, sizeof(user_name), 0);
			recv(fd_client, user_passwd, sizeof(user_passwd), 0);

			strcpy(query, "SELECT * from ACCOUNT where Name='");
			strcat(query, user_name);
			strcat(query, "';");
			res = mysql_query(my_connection, query);

			if(!res){
				result = mysql_store_result(my_connection);
				if(result){
					sql_row = mysql_fetch_row(result);
					if(sql_row){
						printf("have named\n");
						send(fd_client, "named", 8, 0);
						continue;
					
					}
				}
			}

			memset(&query, 0, 1024);
			strcpy(user_path, "./.user_file/.");
			strcat(user_path, user_name);
			int flag0  = mkdir(user_path, 0700);

			if(flag0 != 0){
				perror("the dir create error\n");
			
			}

			sprintf(query, "%s%s%s%s%s%d%s%s%s", \
					"INSERT INTO ACCOUNT(Name, Passwd, Role, Path) VALUES ('",\
					user_name, "', '",\
					user_passwd, "', ",\
					2, ", '",\
					user_path, "');");


			if(mysql_query(my_connection, query)){
				send(fd_client, "fail", 8, 0);
//				printf("error\n");
				continue;
			
			}else{
				send(fd_client, "success", 8, 0);
				user_role = 2;
//				printf("enroll success\n");
				return 2;
			}
		}
	}
	return -1;
}
