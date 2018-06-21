#include "header.h"

char	*get_file_content(const char *const filename)
{
	int			fd;
	size_t		len;
	char		*file_content;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (!(file_content = (char *)malloc(sizeof(char) * (len + 1))))
		exit(EXIT_FAILURE);
	read(fd, file_content, len);
	file_content[len] = 0;
	close(fd);
	return (file_content);
}

void	blocking_signals(void)
{
	sigset_t sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGQUIT);
	sigaddset(&sigset, SIGINT);
	sigaddset(&sigset, SIGTERM);
	sigaddset(&sigset, SIGCHLD); 
	sigaddset(&sigset, SIGUSR1); 
	sigprocmask(SIG_BLOCK, &sigset, NULL);
}

