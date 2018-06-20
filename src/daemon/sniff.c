#include "header.h"

static char	*find_device(void)
{
	FILE *f;
	char *line_without_newline;

	f = fopen(LOG_FILE_CUR_INTERFACES, "r+");
	char *line = 0;
	size_t len = 0;
	getline(&line, &len, f);
	line_without_newline = malloc(sizeof(char) * (strlen(line) - 1));
	for (int i = 0; i < (int)strlen(line) - 1; i++)
		line_without_newline[i] = line[i];
	line_without_newline[strlen(line) - 1] = 0;
	free(line);
	return (line_without_newline);
}

static void clear_ip_parse_file(t_ipfile **ip_info)
{
	t_ipfile *tmp = *ip_info;

	while (*ip_info)
	{
		tmp = *ip_info;
		free(tmp);
		tmp = 0;
		*ip_info = (*ip_info)->next;
	}
	free(*ip_info);
	*ip_info = 0;
}

static void	add_ip(struct in_addr ip)
{
	FILE *f;

	f = fopen(LOG_FILE_IP, "r+");
	if (f == 0)
	{
		f = fopen(LOG_FILE_IP, "w+");
		fprintf(f, "%s 1\n", inet_ntoa(ip));
		fclose(f);
		return ;
	}
	t_ipfile *ip_info = parse_ip_file(f, ip);
	fclose(f);
	f = fopen(LOG_FILE_IP, "w+");
	sort_ip_info(ip_info);
	struct in_addr ip_addr;
	for(t_ipfile *ip_info_tmp = ip_info; ip_info_tmp; ip_info_tmp = ip_info_tmp->next)
	{
		ip_addr.s_addr = ip_info_tmp->ip;
		fprintf(f, "%s %zu\n", inet_ntoa(ip_addr), ip_info_tmp->pack_num);
	}
	clear_ip_parse_file(&ip_info);
	fclose(f);
}

static void callback(u_char *args, const struct pcap_pkthdr *pkthdr, const u_char 
	*packet)
{
	char *num_from_file = get_value_of_key_from_file((const char *)args, LOG_FILE_INTERFACES);
	size_t real_num = atoi(num_from_file);
	real_num++;
	char *str_num = ft_itoa(real_num);
	set_value_of_key_from_file((const char *)args, LOG_FILE_INTERFACES, str_num, num_from_file);
	struct ip *ip = (struct ip*)(packet + 14);
	if (ip->ip_p == 6 || ip->ip_p == 17)
		add_ip(ip->ip_dst);
	free(str_num);
	free(num_from_file);
}

void sniff(void)
{
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *descr;
	// const u_char *packet;
	// struct pcap_pkthdr hdr;
	// struct ether_header *eptr;
	// struct bpf_program fp;
	bpf_u_int32 maskp;
	bpf_u_int32 netp;

	dev = find_device();

	pcap_lookupnet(dev, &netp, &maskp, errbuf);
	descr = pcap_open_live(dev, BUFSIZ, 0, 1000, errbuf);
	if(descr == NULL)
	{
		printf("pcap_open_live(): %s\n", errbuf);
		exit(1);
	}

	// if(pcap_compile(descr, &fp, argv[1], 0, netp) == -1)
	// {
	// 	fprintf(stderr, "Error calling pcap_compile\n");
	// 	exit(1);
	// }

	// if(pcap_setfilter(descr, &fp) == -1) {
	// 	fprintf(stderr, "Error setting filter\n");
	// 	exit(1);
	// }
	// free(dev);
	pcap_loop(descr, 0, callback, (u_char *)dev);
}
