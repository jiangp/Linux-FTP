/*************************************************************************
	> File Name: ./src/send_recv.c
	> Author: Arwen
	> Mail:745529725@qq.com 
	> Created Time: Fri 03 Apr 2015 12:46:01 PM CST
 ************************************************************************/

#include"FTP_server.h"

// send_buf
int send_buf(int sfd, char* buf, int len)
{
	int send_sum = 0;
	int send_ret ;
	while(send_sum<len)
	{
		send_ret = send(sfd, buf + send_sum, len - send_sum, 0);
		send_sum += send_ret ;
	}
	return send_sum;
}
//recv_buf
int recv_buf(int sfd, char* buf, int len)
{
	int recv_sum = 0;
	int recv_ret ;
	while(recv_sum<len)
	{
		recv_ret = recv(sfd, buf + recv_sum, len - recv_sum, 0);
		recv_sum += recv_ret ;
	}
	return recv_sum;
}

