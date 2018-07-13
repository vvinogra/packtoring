#include "header.h"

static size_t	search(t_ipfile *ip_info, uint32_t ip)
{
	t_ipfile *tmp = ip_info;

	while (tmp)
	{
		if (tmp->ip == ip)
			return (tmp->pack_num);
		tmp = tmp->next;
	}
	return (0);
}

void	show_ip_info(char *ip)
{
	struct in_addr check_ip;

	if (inet_pton(AF_INET, ip, &(check_ip.s_addr)) == 0)
	{
		fprintf(stderr, "Incorrect ip\n");
		exit(1);
	}
	FILE *f  = fopen(LOG_FILE_IP, "r+");
	if (f == 0)
	{
		printf("0 packets were received from this ip: %s\n", ip);
		exit(1);
	}
	t_ipfile *ip_info = parse_ip_file(f);
	size_t pack_num = search(ip_info, check_ip.s_addr);
	printf("%zu packets were received from this ip: %s\n", pack_num, ip);
	clear_ip_parse_file(&ip_info);
	fclose(f);
}
