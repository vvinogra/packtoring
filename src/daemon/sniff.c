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

static void callback(u_char *args, const struct pcap_pkthdr *pkthdr, const u_char 
	*packet)
{
	char *num_from_file = get_value_of_key_from_file((const char *)args, LOG_FILE_INTERFACES);
	size_t real_num = atoi(num_from_file);
	real_num++;
	char *str_num = ft_itoa(real_num);
	set_value_of_key_from_file((const char *)args, LOG_FILE_INTERFACES, str_num, num_from_file);
	// size_t num_to_file = set_value_of_key_from_file((const char *)args, LOG_FILE_INTERFACES, num_from_file);
	// printf("%s\n", num_from_file);
	// fprintf(stdout, "%3d, ", count);
	// fflush(stdout);
	// printf("%s\n", str);
	free(str_num);
	free(num_from_file);
}

void sniff(void)
{
	// int i;
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
