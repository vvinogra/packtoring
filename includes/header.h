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


//deamon
// initing_daemon.c
int	initing_deamon(void);
int	processing(void);

// read_write_files
void	check_set_pid_file(void);
void	set_value_of_key_from_file(const char *key, char *filename, char *new_value, char *old_value);
char	*get_value_of_key_from_file(const char *key, char *filename);

// log_file.c
void	initing_log_file(void);

//  sniff.c
void	sniff(void);

// utils.c
char	*get_line_by_key(const char *key, char *filename);
char	*get_file_content(const char *const filename);

// ft_itoa.c
char	*ft_itoa(int n);

//cli

// utils.c
void	blocking_signals(void);




// validation.c
void	valid_interface_arg(const char *interface);

#endif
