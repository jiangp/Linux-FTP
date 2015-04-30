/*************************************************************************
  > File Name:User_init.
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 27 Apr 2015 12:44:18 PM CST
 ************************************************************************/

#ifndef USER_INIT_H
#define YSER_INIT_H
#include<stdio.h>
#include<stdlib.h>
#include"FTP_server.h"
#include<mysql/mysql.h>
/*the account infor*
  typedef struct account
  {
  char m_name[128];
  char m_passwd[128];
  int m_role;
  struct account *m_next;
  }ACCOUNT, *pACCOUNT;

 *the user's information*
 typedef struct user_infor
 {
 char m_name[128];
 char m_passwd[128];
 char m_path[128];
 struct user_infor *m_next;
 }USER, *pUSER;*/



#endif
int User_init(MYSQL *my_connection, int fd_client)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
	char query[1024];

	int cnt = 0;
	char role[8] = "0";
	char user_name[128] = "0";
	char user_passwd[128] = "0";
	char path[128] = "0";
	recv(fd_client, role, sizeof(role), 0);

	if(strncmp(role, "login", 5) == 0){
		while(cnt < 3)
		{
			recv(fd_client, user_name, sizeof(user_name), 0);
			recv(fd_client, user_passwd, sizeof(user_passwd), 0);
//			printf("%s:%s\n", user_name, user_passwd);
			strcpy(query, "SELECT * from ACCOUNT where Name='");
			strcat(query, user_name);
			strcat(query, "';");
//			printf("%s\n",query);
			res = mysql_query(my_connection, query);
			if(!res)
			{

				result = mysql_store_result(my_connection);
				if(result)
				{
					sql_row = mysql_fetch_row(result);
					if(sql_row){
//						printf("%s\n", sql_row[2]);
						if(strcmp(sql_row[2], user_passwd) == 0){
							send(fd_client, "success", 8, 0);
							return sql_row[3];
						}else
						{
//							printf("passwd eror \n");
							send(fd_client, "fail", 8, 0);
							cnt++;	
						}
					}
					else{
//						printf("no name\n");
						send(fd_client, "fail", 8, 0);
						cnt++;
					}
				}
			}
		}
	}else if(strncmp(role, "enroll", 6) == 0)
	{
		while(1){
			recv(fd_client, user_name, sizeof(user_name), 0);
			recv(fd_client, user_passwd, sizeof(user_passwd), 0);
//			printf("%s:%s\n", user_name, user_passwd);

			strcpy(query, "SELECT * from ACCOUNT where Name='");
			strcat(query, user_name);
			strcat(query, "';");
//			printf("%s\n",query);
			res = mysql_query(my_connection, query);
			if(!res){
				result = mysql_store_result(my_connection);
				if(result)
				{
					sql_row = mysql_fetch_row(result);
					if(sql_row){
						printf("have named\n");
						send(fd_client, "named", 8, 0);
						continue;
					}
				}
			}
			memset(&query, 0, 1024);
			strcpy(path, "../file/");
			strcat(path, user_name);
//			printf("%s\n", path);
			sprintf(query, "%s%s%s%s%s%d%s%s%s", \
					"INSERT INTO ACCOUNT(Name, Passwd, Role, Path) VALUES ('",\
					user_name, \
					"', '",\
					user_passwd, \
					"', ",\
					2,\
					", '",\
					path,\
					"');");
//			printf("%s\n", query);

			if(mysql_query(my_connection, query)){
				send(fd_client, "fail", 8, 0);
//				printf("error\n");
				continue;
			}else{
				send(fd_client, "success", 8, 0);
//				printf("success\n");
				return 2;
			}
		}
	}
	return -1;
}
