#include "header.h"

static void	usage(void)
{
	printf("Usage: sudo ./packtoring [start] [--help] [show [ip] count]\n"
		"                         [stop] [select iface [iface]]\n"
		"                         [stat [iface]] [reset [ip,iface]]\n"
		"                         [uninstall] [show current iface]\n");
	exit(0);
}

static void	valid_two_argc(char *argv[])
{
	if (strcmp(argv[1], "start") == 0)
		execl("./daemon", "daemon", (char *)0);
	else if (strcmp(argv[1], "stop") == 0)
		kill_file_pid();
	else if (strcmp(argv[1], "--help") == 0)
		usage();
	else if (strcmp(argv[1], "stat") == 0)
		show_interface_info(NULL);
	else if (strcmp(argv[1], "reset") == 0)
		reset_info("all");
	else if (strcmp(argv[1], "uninstall") == 0)
		uninstall();
	else
		usage();
}

static void	valid_three_argc(char *argv[])
{
	if (strcmp(argv[1], "stat") == 0)
		show_interface_info(argv[2]);
	else if (strcmp(argv[1], "reset") == 0 && strcmp(argv[2], "ip") == 0)
		reset_info("ip");
	else if (strcmp(argv[1], "reset") == 0 && strcmp(argv[2], "iface") == 0)
		reset_info("iface");
	else
		usage();
}

static void	valid_four_argc(char *argv[])
{
	if (strcmp(argv[1], "show") == 0 && strcmp(argv[3], "count") == 0)
		show_ip_info(argv[2]);
	else if (strcmp(argv[1], "select") == 0 && strcmp(argv[2], "iface") == 0)
		select_new_interface(argv[3]);
	else if (strcmp(argv[1], "show") == 0 && strcmp(argv[2], "current") == 0 && strcmp(argv[3], "iface") == 0)
		show_current_iface();
	else
		usage();
}

void	validation(int argc, char *argv[])
{
	if (getuid() != 0)
		usage();
	if (argc == 2)
		valid_two_argc(argv);
	else if (argc == 3)
		valid_three_argc(argv);
	else if (argc == 4)
		valid_four_argc(argv);
	else
		usage();
}
