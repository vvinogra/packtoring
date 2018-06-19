#include "header.h"

void initing_log_file(void)
{
	FILE *f;

	f = fopen(LOG_FILE_INTERFACES, "r+");
	if (f != 0)
	{
		fclose(f);
		return ;
	}
	f = fopen(LOG_FILE_INTERFACES, "w+");
	struct if_nameindex *if_nidxs = if_nameindex();
	if (if_nidxs != NULL)
	{
		for (struct if_nameindex *intf = if_nidxs;
			intf->if_index != 0 || intf->if_name != NULL; intf++)
		{
			fprintf(f, "%s 0\n", intf->if_name);
		}
	}
	fclose(f);
}

void initing_cur_log_file(void)
{
	FILE *f;

	f = fopen(LOG_FILE_CUR_INTERFACES, "r+");
	if (f != 0)
	{
		fclose(f);
		return ;
	}
	f = fopen(LOG_FILE_CUR_INTERFACES, "w+");
	fprintf(f, "eth0\n");
	fclose(f);
}
