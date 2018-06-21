#include "header.h"

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

void	show_current_iface(void)
{
	char *interface = find_cur_interface();

	printf("%s selected for sniffing\n", interface);
	free(interface);
}
