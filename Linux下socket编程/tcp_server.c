/*
 * Purpose: This is a tcp_server test file for me to learn socket in Linux.
 * Author: 赵庶林
 * Date: 2014/07/11
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int server_sockfd; //服务器端的socket描述符
	int client_sockfd; //客户端的socket描述符
	int on;
	int send_len, recv_len; //定义2个变量，分别表示发送长度和接收长度
	struct sockaddr_in server_addr; //服务器端的地址结构体
	struct sockaddr_in client_addr; //客户端的地址结构体
	int sockaddr_in_size;
	char buf[BUFSIZ]; //数据传送所用的缓冲区，BUFSIZ = 8192 defined in stdio.h

	memset(&server_addr, 0x00, sizeof(server_addr)); //在设置地址结构体之前先清零可好
	server_addr.sin_family = AF_INET; //IP通信
	server_addr.sin_addr.s_addr = INADDR_ANY; //允许连接到所有的本地地址
	server_addr.sin_port = htons(8000); //服务器端口号是8000

	//开始创建服务器端的套接字，设置为：IPv4协议，有连接，TCP协议
	if((server_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error!");
		exit(EXIT_FAILURE);
	}
	printf("Server has build one socket successfully.\n");

	//下面的设置是为了防止我第二次运行时发生错误：Address already in use
	on = 1;
	if((setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
	{
		perror("setsockopt error!");
		exit(EXIT_FAILURE);
	}

	//把这个socket绑定到服务器的网络地址上面
	if((bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))) < 0)
	{
		perror("bind error!");
		exit(EXIT_FAILURE);
	}

	//开始监听，设置最多可以连接25个
	listen(server_sockfd, 25);
	printf("Server is listening...\n");

	//客户端来连接请求啦，accept吧。在accept的过程中，server把client的地址信息保存啦
	sockaddr_in_size = sizeof(struct sockaddr_in);
	if((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &sockaddr_in_size)) < 0)
	{
		perror("accept error!");
		exit(EXIT_FAILURE);
	}	
	printf("Server has accepted client, whose IP is %s. Now welcome it.\n", inet_ntoa(client_addr.sin_addr));
	send_len = send(client_sockfd, "Welcome to server, have fun.\n", 29, 0);

	//开始接收client传送来的数据
	printf("Server is waiting to recv data from client...\n");
	while((recv_len = recv(client_sockfd, buf, BUFSIZ, 0)) > 0)//接受到的数据存在buf里面啦，下面server爱怎么处理就怎么处理
	{
		buf[recv_len] = '\0'; // close this array!
		printf("client -> server: %s\n", buf);
		if((send(client_sockfd, buf, recv_len, 0)) < 0)//好吧，把这些数据原封不动传回去！^_^
		{
			perror("send error!");
			exit(EXIT_FAILURE);
		}
	}

	close(client_sockfd);
	close(server_sockfd);

	return 0;
}
