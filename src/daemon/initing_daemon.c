#include "header.h"

int	initing_deamon()
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Error: Start Daemon failed (%s)\n", strerror(errno));
		return -1;
	}
	else if (!pid)
	{
		// umask(0);
		// setsid();
		// chdir("/");
		// close(STDIN_FILENO);
		// close(STDOUT_FILENO);
		// close(STDERR_FILENO);
		processing();
	}
	return (1);
}


int	processing()
{
	initing_log_file();
	initing_cur_log_file();
	check_set_pid_file();
	sniff();
	return 0;
}
