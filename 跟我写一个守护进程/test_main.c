#include <unistd.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

int daemonize(void);

int main(void)
{
	int fd;
	time_t t;
	char* buf;

	printf("here we go, start to daemonize...\n");
	if(daemonize() == 0)
		printf("succeed.\n");
	else{
		printf("error, exit!\n");
		return -1;
	}
	
	while(1)
	{
		sleep(5);
		fd = open("./daemon_test.log", O_WRONLY|O_CREAT|O_APPEND, 0644);
		if(fd == -1)
			return -1;
		
		t = time(0);
		buf = asctime(localtime(&t));
		write(fd, buf, strlen(buf));
		close(fd);
	}
	
	return 0;
}

