#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>

int daemonize()
{
	int fd;

	switch(fork())
	{
		case -1: exit(-1);
		case 0: 
			 printf("child id is: %d\n",getpid());
			 break;
		default: 
			 printf("parent id is: %d\n",getpid());
			 exit(0);
	}

	setsid();

	switch(fork())
	{
		case -1: exit(-1);
		case 0: break;
		default: exit(0);
	}

	umask(0);

	chdir("/");

	for(fd = 0; fd < NOFILE; ++ fd)
		close(fd);

	close(STDIN_FILENO);
	fd = open("/dev/null", O_RDWR);
	if(fd != STDIN_FILENO)
		return -1;

	if(dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
		return -1;

	if(dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
		return -1;

	signal(SIGCHLD, SIG_IGN);

	return 0;
}

