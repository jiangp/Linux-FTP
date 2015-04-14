/*************************************************************************
  > File Name: main.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 2 mar 2015 09:41:29 AM CST
 ************************************************************************/
#include"FTP_server.h"
//main
int main(int argc ,  char *argv[])
{
	if(argc != 4){
		perror("EXE Ip Port Nchild! \n");
		exit(1);
	}

	/*set the fork pool*/
	int nchild = atoi(argv[3]);
	pchild_t parr = (pchild_t)calloc(nchild, sizeof(child_t));
	make_child(parr, nchild);


	/*socker accept*/
	int fd_listen, fd_client;
	MY_ASSERT((fd_listen = socket(AF_INET, SOCK_STREAM , 0)) != -1 , "listen socket init");//socket


	struct sockaddr_in seraddr, clientaddr;
	socklen_t sock_len = sizeof(clientaddr);
	memset(&seraddr, 0, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[2]) );
	seraddr.sin_addr.s_addr = inet_addr(argv[1]);
	MY_ASSERT(bind(fd_listen, (struct sockaddr*)&seraddr, sizeof(seraddr))==0, "bind");//bind
	MY_ASSERT(listen(fd_listen, 5) == 0, "listen");//listen



	int ep_fd;
	MY_ASSERT((ep_fd = epoll_create(2048)) != -1, "epoll1 create");//epoll_create 
	struct epoll_event my_event, my_events[1024];
	int ready_events, i = 0, index;

	my_event.events = EPOLLIN;
	my_event.data.fd = fd_listen;	
	MY_ASSERT(epoll_ctl(ep_fd, EPOLL_CTL_ADD, fd_listen, &my_event) == 0, "epoll1  client"); // epoll_ctl events
	
	/*for(i = 0; i < nchild; ++i)
    *	{
	*   	my_event.events = EPOLLIN;
	*	    my_event.data.fd = parr[i].child_fd;
	*	    MY_ASSERT(epoll_ctl(ep_fd, EPOLL_CTL_ADD, parr[i].child_fd, &my_event) == 0, "epoll1  client"); // epoll_ctl events
	*    }*/
	
	char ret[] = "0";
	/*Let the read form child is not jam*/
	for(index = 0; index < nchild; ++index)				
		fcntl(parr[index].child_fd, F_SETFL,FNDELAY);

	while(1)
	{	/*wait the accept mag*/
		memset(&my_events, 0 ,sizeof(my_events));
		ready_events = epoll_wait(ep_fd, my_events, 1024, -1);//epoll_wait
		if(ready_events == -1){
			perror("epoll_wait\n");
			continue;
		}
	

		for(i = 0; i < ready_events; ++i)
		{
			int fd = my_events[i].data.fd;
		
			if(fd == fd_listen){
				sock_len =sizeof(clientaddr);
				memset(&clientaddr, 0 ,sock_len);
				fd_client = accept(fd_listen , (struct sockaddr*)&clientaddr ,&sock_len );
				printf("client %s:%d connect!\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

				/* recv have free fork
				 * let the busy = 0 make it can use again 
				 */
				for(index = 0; index < nchild; ++index){				
					if(read( parr[index].child_fd, ret, sizeof(ret)) > 0){
						parr[index].child_busy = 0;
						printf("recv\n");
					
					}
				}

				/* search the child who is free
				 * if find the first one break
				 * */
				for(index = 0; index < nchild; ++index){
					if(parr[index].child_busy == 0)
						break;
				}
				/*if have no free fork  wait again*/
				if(index == nchild)
					continue;
				/*send mag to son fork 
				 * let the station is busy*/  
				send_fd(parr[index].child_fd, fd_client);
				parr[index].child_busy = 1;
			}
			


		}
	}
	
	close(ep_fd);

}


