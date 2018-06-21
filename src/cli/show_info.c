#include "header.h"

size_t	binarysearch(t_ipfile *ip_info, size_t len, uint32_t ip)
{
	t_ipfile arr[len];
	t_ipfile *fill_arr = ip_info;

	for (size_t i = 0; i < len; ++i)
	{
		arr[i].ip = fill_arr->ip;
		arr[i].pack_num = fill_arr->pack_num;
		fill_arr = fill_arr->next;
	}
	if (len == 0)
		return (0);
	else if (arr[0].ip > ip)
		return (0);
	else if (arr[len - 1].ip < ip)
		return (0);

	size_t i = 0;
	while (i < len)
	{
		size_t mid = i + (len - i) / 2;

		if (ip <= arr[mid].ip)
			len = mid;
		else
			i = mid + 1;
	}
	if (arr[len].ip == ip)
		return (arr[len].pack_num);
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
	size_t pack_num = binarysearch(ip_info, t_ipfile_getlen(&ip_info), check_ip.s_addr);
	printf("%zu packets were received from this ip: %s\n", pack_num, ip);
	clear_ip_parse_file(&ip_info);
	fclose(f);
}

void	show_interface_info(char *interface)
{
	struct if_nameindex *if_nidxs = if_nameindex();
	if (if_nidxs != NULL)
	{
		if (interface == 0)
			for (struct if_nameindex *intf = if_nidxs;
				intf->if_index != 0 || intf->if_name != NULL; intf++)
			{
				char *value = get_value_of_key_from_file(intf->if_name, LOG_FILE_INTERFACES);
				printf("%s collected %s packets\n", intf->if_name, value);
				free(value);
			}
		else
		{
			for (struct if_nameindex *intf = if_nidxs;
				intf->if_index != 0 || intf->if_name != NULL; intf++)
			{
				if (strcmp(interface, intf->if_name) == 0)
				{
					char *value = get_value_of_key_from_file(intf->if_name, LOG_FILE_INTERFACES);
					printf("%s collected %s packets\n", intf->if_name, value);
					free(value);
					free(if_nidxs);
					exit(0);
				}
			}
			printf("There is no interface with name \"%s\"\n"
				"Type ifconfig -l to see all possible interfaces\n", interface);
		}
		free(if_nidxs);
	}
}

void	select_new_interface(char *interface)
{
	struct if_nameindex *if_nidxs = if_nameindex();

	if (if_nidxs != NULL)
	{
		for (struct if_nameindex *intf = if_nidxs;
				intf->if_index != 0 || intf->if_name != NULL; intf++)
			{
				if (strcmp(interface, intf->if_name) == 0)
				{
					FILE *f = fopen(LOG_FILE_CUR_INTERFACES, "w+");
					fprintf(f, "%s\n", interface);
					fclose(f);
					free(if_nidxs);
					exit(0);
				}
			}
		printf("There is no interface with name \"%s\"\n"
				"Type ifconfig -l to see all possible interfaces\n", interface);
		free(if_nidxs);
	}
}