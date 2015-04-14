/*************************************************************************
  > File Name: handle.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 02 Mar 2015 04:49:19 PM CST
 ************************************************************************/

#include"FTP_server.h"

//fork  handle
void handle(int fd_client)
{

	//	FILE* fp_config;
	//	char line[128] = "0"; 
	//    
	//	fp_config = fopen(ADDR, "r");
	//	if(fp_config == NULL)
	//	{
	//		printf("open addrfile fail!\n");
	//		exit(1);
	//	}
	//	memset(&line ,0, 128);
	//	fgets(line, 128, fp_config);
	//  line[strlen(line)-1] = '\0';

	chdir("../file/");
	/*
	 * int epoll_fd;
	 *  MY_ASSERT((epoll_fd = epoll_create(1024)) != -1, "epoll create");//epoll_create
	 *  struct epoll_event my_event, my_events[1024];
	 *  char buf[1024] = "0";
	 *  int ready_events, index=0;
	 *
	 *  my_event.events = EPOLLIN;
	 *  my_event.data.fd = fd_client;
	 *  MY_ASSERT(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd_client, &my_event) == 0, "epoll  client"); // epoll_ctl events
	 *  while(1)
	 *  {
	 *  memset(&my_events, 0 ,sizeof(my_events));
	 *  ready_events = epoll_wait(epoll_fd, my_events, 1024, -1);//epoll_wait
	 *  if(ready_events == -1)
	 *  {
	 *  perror("epoll_wait\n");
	 *  continue;
	 *  }
	 *
	 *  if(my_events[index].events & EPOLLIN)//  events
	 *  {
	 * * */
	while(1)
	{
		char buf[1024] = "0";
		memset(buf, 0 ,1024);
		if(recv(fd_client, buf, sizeof(buf), 0) == 0) //if recv over 
		{
			printf("one client exit.\n");
			close(fd_client);
			break ;
		}else
		{	
			if(strncmp(buf,"ls",2) == 0)
			{
				do_ls(fd_client);
			}
			else if(strncmp(buf,"gets",4) == 0)
			{

				do_gets(fd_client);

			}
			else if(strncmp(buf, "puts",4) == 0)
			{

				do_puts(fd_client);
			}
			else if(strncmp(buf,"cd",2) ==0 )
			{
				do_cd(fd_client,buf,strlen(buf));
			}
			else if(strncmp(buf,"pwd",3) == 0)
			{
				do_pwd(fd_client);
			}else if(strncmp(buf,"remove",6) == 0)			
			{

				do_remove(fd_client);
			}
			else
			{
				continue;
			}

		}
	}	
}


