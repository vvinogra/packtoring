#include "header.h"

static void	write_pid(void)
{
	FILE *f;
	pid_t pid = getpid();

	f = fopen(PID_FILE, "w+");
	fprintf(f, "%u\n", pid);
	fclose(f);
}

void	check_set_pid_file(void)
{
	FILE *f;

	f = fopen(PID_FILE, "r+");
	if (f == 0)
	{
		write_pid();
		return ;
	}
	if (kill_file_pid() == true)
		write_pid();
	fclose(f);
}

bool	kill_file_pid(void)
{
	FILE *f;

	f = fopen(PID_FILE, "r+");
	if (f == 0)
		return (true);
	char *line = 0;
	size_t len = 0;
	getline(&line, &len, f);
	fclose(f);
	pid_t file_pid = (pid_t)atoi(line);
	free(line);
	if (file_pid != getpid())
	{
		kill(file_pid, SIGKILL);
		unlink(PID_FILE);
		return (true);
	}
	return (false);
}
