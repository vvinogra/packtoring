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
int	processing(void);

// read_write_files
void	set_value_of_key_from_file(const char *key, char *filename, char *new_value, char *old_value);
char	*get_value_of_key_from_file(const char *key, char *filename);

// log_file.c
void	initing_log_file(void);
void initing_cur_log_file(void);

//  sniff.c
void	sniff(void);
void	clear_ip_parse_file(t_ipfile **ip_info);

// pid_file.c
void	check_set_pid_file(void);
bool	kill_file_pid(void);

// ip_file.c
t_ipfile *parse_ip_file(FILE *f);
size_t t_ipfile_getlen(t_ipfile **start);
void add_ip_to_file(t_ipfile **data, struct in_addr ip_to_add);

// utils.c
char	*get_line_by_key(const char *key, char *filename);
char	*get_file_content(const char *const filename);
void	blocking_signals(void);


// ft_itoa.c
char	*ft_itoa(int n);

// ip_file.c

//cli

// utils.c
void	blocking_signals(void);
void	sort_ip_info(t_ipfile *ip_info);

// validation.c
void	validation(int argc, char *argv[]);

// show_info.c
void	show_interface_info(char *interface);
void	show_ip_info(char *ip);
void	select_new_interface(char *interface);

// deletion.c
void	reset_info(char *reset);
void	uninstall(void);


#endif
