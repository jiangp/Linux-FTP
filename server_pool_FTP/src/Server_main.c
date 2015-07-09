/*************************************************************************
  > File Name: main.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 2 mar 2015 09:41:29 AM CST
 ************************************************************************/
#include"FTP_server.h"
#include"Socket.h"
#include"Epoll.h"
//main


int main(int argc ,  char *argv[])
{
	/*if input 4 func  IP PORT nchild*/
	if(argc != 4){
		perror("EXE IP PORT NCHILD!\n");
		exit(1);
	}
	int nchild = atoi(argv[3]);

	/*system_init*/
//	pACCOUNT account_list = NULL;
//	pUSER user_list = NULL;
//	system_init("../conf/config", &account_list, &user_list);

	/*calloc nchild space and add process init */
	pchild_t parr_list = NULL;
	pchild_t pcur ;
	make_child(&parr_list, nchild, 0);

	
	/* socket IP TCP */ 
	int fd_listen, fd_client;
	fd_listen = Socket(argv[1], argv[2]);	
	struct sockaddr_in clientaddr;
	socklen_t sock_len;

	/*epoll create to */
	int ep_fd;
	int ready_events;
	struct epoll_event my_events[1024];
	ep_fd = Epoll_init(fd_listen, 2048);

	int i, cnt;
	while(1)
	{
		/*消息队列 ， epoll_wait*/
		memset(&my_events, 0, sizeof(my_events));
		if((ready_events = epoll_wait(ep_fd, my_events, 1024, -1)) == -1){
			perror("epoll_wait\n");
			continue;
		}
			
		for(i = 0; i < ready_events; ++i)
		{
			int fd = my_events[i].data.fd;		
			if(fd == fd_listen){
				sock_len = sizeof(clientaddr);
				memset(&clientaddr, 0, sock_len);
				fd_client = accept(fd_listen , (struct sockaddr*)&clientaddr, &sock_len );
				printf("client %s:%d connect!\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

				/*find the list who child_busy is free
				 * if the free num small 3 create 5 process*/
				pcur = parr_list;
				cnt = 0;
				while(pcur != NULL){
					if((pcur->child_busy) == 0)
						++cnt;
					pcur = pcur->m_next;
				}
				if(cnt < 3){
	                make_child(&parr_list, nchild, (nchild - 5));
				}

				/*process communation to son process*/
				pcur = parr_list;	
				while(pcur != NULL){			
			    	if((pcur->child_busy) == 0)
						break;
					pcur = pcur->m_next;
				}
				if(pcur == NULL)
					continue;
				send_fd(pcur->child_fd, fd_client);
				pcur->child_busy = 1;
				
			}	
		}
	}
	close(ep_fd);
}
