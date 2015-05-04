/*************************************************************************
  > File Name: ./src/Pool_child.c
  > Author: Arwen
  > Mail:745529725@qq.com 
  > Created Time: Mon 06 Apr 2015 01:34:56 PM CST
 ************************************************************************/

#include"FTP_server.h"

void make_child(pchild_t *phead_child, int nchild, int n)
{
	pchild_t parr;//, pcur, ppre;
	while(nchild > n)
	{
		parr = (pchild_t)calloc(1, sizeof(child_t));
		int fds[2];
		if(-1 == socketpair(AF_LOCAL, SOCK_STREAM, 0, fds))
		{
			perror("socketpair!\n");
			exit(1);
		}
		pid_t pid = fork();
		if(pid == 0)
		{
			close(fds[1]);
			child_main(fds[0]);
			memset(&parr, 0 ,sizeof(child_t));

			/*delete the note							
	    	pcur = parr->m_head;
			ppre = parr->m_next;		
			pcur->m_next = ppre;
			ppre->m_head = pcur;			
			printf("the exit process is :%d\n", parr->child_fd);
			printf("111\n");
			memset(&parr, 0 ,sizeof(child_t));*/
			
			exit(1);
		}
		close(fds[0]);
		/*status */
		parr->child_pid = pid;
		parr->child_fd = fds[1];
		parr->child_busy = 0;
		/*tail in struct */  
		printf("%d:%d:%d\n", parr->child_pid, parr->child_fd, parr->child_busy);	
		
		/*add in list*/
		if((*phead_child)==NULL)
		{
			(*phead_child)=parr;
			parr->m_next=NULL;
			parr->m_head=NULL;
		}else
		{
			parr->m_next = (*phead_child);
			(*phead_child)->m_head = parr;
			parr->m_head = NULL;
			(*phead_child) = parr;
		}
		++n;
	}
}
