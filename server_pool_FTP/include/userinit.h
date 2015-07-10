/*************************************************************************
  > File Name:User_init.h
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 27 Apr 2015 12:44:18 PM CST
 ************************************************************************/

#ifndef _USER_INIT_H
#define _YSER_INIT_H

#include<stdio.h>
#include<stdlib.h>
#include"FTP_server.h"
#include<mysql/mysql.h>


#endif  /*_USER_INIT_H*/

/*
 * use to the user login and enroll and vector
 * when vector stcect return 
 * when login find from mysql
 * when enroll first find from ACCOUNT tables 
 * of haven't insert a new user and create a dir name user_name
 * */
char *User_init(MYSQL *my_connection, int fd_client)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	
	int res, cnt = 0;
	char role[8] = "0";
	char user_name[128] = "0";
	char user_passwd[128] = "0";
	char path[128] = "0";
	char query[1024] = "0";
	
	recv(fd_client, role, sizeof(role), 0);

	if(strncmp(role, "vector", 6) == 0){
		return "vector";
	
	}else if(strncmp(role, "login", 5) == 0){

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
							return user_name;
						
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
			strcpy(path, "./.user_file/.");
			strcat(path, user_name);
			int flag0  = mkdir(path, 0700);

			if(flag0 != 0){
				perror("the dir create error\n");
			
			}
//			printf("%s\n", path);

			sprintf(query, "%s%s%s%s%s%d%s%s%s", \
					"INSERT INTO ACCOUNT(Name, Passwd, Role, Path) VALUES ('",\
					user_name, "', '",\
					user_passwd, "', ",\
					2, ", '",\
					path, "');");
//			printf("%s\n", query);

			if(mysql_query(my_connection, query)){
				send(fd_client, "fail", 8, 0);
//				printf("error\n");
				continue;
			
			}else{
				send(fd_client, "success", 8, 0);
				printf("success\n");
				return user_name;
			
			}
		}
	}
	return NULL;
}
