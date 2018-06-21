#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <pcap/pcap.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <stdbool.h>

#define PID_FILE "/tmp/packtoring.pid"
#define LOG_FILE_INTERFACES "/tmp/packtoring_interfaces.log"
#define LOG_FILE_CUR_INTERFACES "/tmp/packtoring_cur_interfaces.log"
#define LOG_FILE_IP "/tmp/packtoring_ip.log"


typedef struct	s_ipfile
{
	uint32_t		ip;
	size_t		pack_num;
	struct s_ipfile *next;
}				t_ipfile;

//deamon

// initing_daemon.c
pid_t	initing_deamon(void);

// interfaces_file.c
char	*find_cur_interface(void);
void	initing_interfaces_file(void);
char	*get_value_of_key_from_file(const char *key, char *filename);
void	set_value_of_key_from_file(const char *key, char *filename, char *new_value, char *old_value);

//  sniff.c
void	sniff(void);

// pid_file.c
void	check_set_pid_file(void);
bool	kill_file_pid(void);

// ip_file.c
t_ipfile	*parse_ip_file(FILE *f);
size_t	t_ipfile_getlen(t_ipfile **start);
void	clear_ip_parse_file(t_ipfile **ip_info);
void	add_ip_to_file(t_ipfile **data, struct in_addr ip_to_add);
void	sort_ip_info(t_ipfile *ip_info);

// utils.c
char	*get_file_content(const char *const filename);
void	blocking_signals(void);

// ft_itoa.c
char	*ft_itoa(int n);

//cli

// validation.c
void	validation(int argc, char *argv[]);

// ip.c
void	show_ip_info(char *ip);

// interfaces.c
void	show_interface_info(char *interface);
void	select_new_interface(char *interface);
void	show_current_iface(void);

// deletion.c
void	reset_info(char *reset);
void	uninstall(void);


#endif
