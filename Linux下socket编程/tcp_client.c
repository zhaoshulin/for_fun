/*
 * Purpose: A tcp_client test file for me to learn socket in Linux.
 * Author:赵庶林
 * Date: 2014/07/11
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char **argv)
{
	int client_sockfd;
	int recv_len, send_len;
	int on;
	struct sockaddr_in server_addr;
	char buf[BUFSIZ];

	memset(&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("10.17.11.49"); //服务器IP地址
	
	if((client_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error!");
		return -1;
	}
	
	on = 1;
	if((connect(client_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))) < 0)
	{
		perror("connect error!");
		return -1;
	}
	printf("Client connecting to server...\n");

	recv_len = recv(client_sockfd, buf, BUFSIZ, 0);
	buf[recv_len] = '\0'; //close this array!
	printf("Received welcome information from server: %s\n", buf);

	printf("Please enter something you want to sent do server:\n");
	while(1)
	{
		scanf("%s", buf);
		if(!strcmp(buf, "quit")) //中止的输入是:"quit"
			break;
	
		printf("ok, client -> server...\n");
		send_len = send(client_sockfd, buf, strlen(buf), 0);
		printf("now, server -> client...\n");
		recv_len = recv(client_sockfd, buf, BUFSIZ, 0);
		buf[recv_len] = '\0';
		printf("%s ", buf);	
	}

	close(client_sockfd);

	return 0;
}
