#include "header.h"

void	reset_info(char *reset)
{
	if (strcmp(reset, "all") == 0)
	{
		unlink(LOG_FILE_INTERFACES);
		unlink(LOG_FILE_IP);
	} else if (strcmp(reset, "ip") == 0)
		unlink(LOG_FILE_IP);
	else if (strcmp(reset, "iface") == 0)
		unlink(LOG_FILE_INTERFACES);
}

void	uninstall(void)
{
	kill_file_pid();
	unlink(LOG_FILE_IP);
	unlink(LOG_FILE_INTERFACES);
	unlink(LOG_FILE_CUR_INTERFACES);
}

