#include "header.h"

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
	t_ipfile *ip_info = parse_ip_file(f);
	add_ip_to_file(&ip_info, ip);
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
	(void)pkthdr;
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
	bpf_u_int32 maskp;
	bpf_u_int32 netp;

	dev = find_cur_interface();
	pcap_lookupnet(dev, &netp, &maskp, errbuf);
	descr = pcap_open_live(dev, BUFSIZ, 0, 1000, errbuf);
	if(descr == NULL)
		exit(1);
	pcap_loop(descr, 0, callback, (u_char *)dev);
}
