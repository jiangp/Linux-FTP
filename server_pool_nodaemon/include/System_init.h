/*************************************************************************
	> File Name: System_init.h
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Wed 22 Apr 2015 03:41:38 PM CST
 ************************************************************************/
#ifndef SYSTEM_H
#define SYSTEM_H

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include"FTP_server.h"
/*
*the account infor*
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
}USER, *pUSER;

*/
#endif
void system_init(char *config, pACCOUNT *phead_acc, pUSER *phead_user)
{
	FILE* fp_config, *fp_account, *fp_user;
	char line[1024];
	pACCOUNT pnew, pcur, ppre;
	pUSER pnew_user, pcur_user, ppre_user;

	fp_config = fopen(config, "r");
	if(fp_config == NULL)
	{
		perror("open config fail!\n");
		exit(1);
	}
	memset(line, 0 , sizeof(line));
	fflush(stdin);
	fgets(line, 1024, fp_config);
	line[strlen(line) - 1] = 0;
	fp_account = fopen(line, "r");
	if(fp_account == NULL)
	{
		perror("open account fail!\n");
		exit(1);
	}
	while(memset(line, 0,sizeof(line)), fgets(line, 1024, fp_account)!= NULL)
	{
		pnew = (pACCOUNT)calloc(1, sizeof(ACCOUNT));
		sscanf(line, "%s%s%d", pnew->m_name,pnew->m_passwd, &pnew->m_role);

//		puts(line);
		pcur = *phead_acc;
		ppre = NULL;
		while(pcur && strcmp(pcur->m_name, pnew->m_name) < 0)
		{
			ppre = pcur;
			pcur = pcur->m_next;
		}
		if(ppre == NULL)
		{
			pnew->m_next = *phead_acc;
			*phead_acc = pnew;
		}else{
			pnew->m_next = pcur;
			ppre->m_next = pnew;
		}
	}
	fclose(fp_account);


	/*read the user information*/
	memset(line, 0 , sizeof(line));
	fflush(stdin);
	fgets(line, 1024, fp_config);
	line[strlen(line) - 1] = 0;
	fp_user = fopen(line, "r");
	if(fp_user == NULL)
	{
		perror("open user fail!\n");
		exit(1);
	}
	while(memset(line, 0,sizeof(line)), fgets(line, 1024, fp_user)!= NULL)
	{
		pnew_user = (pUSER)calloc(1, sizeof(USER));
		sscanf(line, "%s%s%s", pnew_user->m_name,pnew_user->m_passwd, pnew_user->m_path);
//		puts(line);
		pcur_user = *phead_user;
		ppre_user = NULL;
		while(pcur_user && strcmp(pcur_user->m_name, pnew_user->m_name) < 0)
		{
			ppre_user = pcur_user;
			pcur_user = pcur_user->m_next;
		}
		if(ppre_user == NULL)
		{
			pnew_user->m_next = *phead_user;
			*phead_user = pnew_user;
		}else{
			pnew_user->m_next = pcur_user;
			ppre_user->m_next = pnew_user;
		}
	}
	fclose(fp_user);

}

