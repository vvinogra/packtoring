#include "header.h"

static char *get_line_by_key(const char *key, char *filename)
{
	char *content;
	char *needed_line;
	char *ret;
	FILE *f = fopen(filename, "r+");

	if (f == 0)
		initing_interfaces_file();
	content = get_file_content(filename);
	needed_line = strstr(content, key);
	int i;
	for(i = 0; needed_line[i] != '\n'; i++)
		;
	if (!(ret = malloc(sizeof(char) * (i + 1))))
		return (0);
	for(i = 0; needed_line[i] != '\n'; i++)
		ret[i] = needed_line[i];
	ret[i] = 0;
	free(content);
	fclose(f);
	return (ret);
}

char	*get_value_of_key_from_file(const char *key, char *filename)
{
	char *needed_line;
	char *ret;

	needed_line = get_line_by_key(key, filename);
	ret = strdup(strstr(needed_line, " ") + 1);
	free(needed_line);
	return (ret);
}

void	set_value_of_key_from_file(const char *key, char *filename, char *new_value, char *old_value)
{
	char *file_content = get_file_content(filename);
	FILE *f = fopen(filename, "w+");
	char line[strlen(key)];
	strcpy(line, key);
	for(int i = 0; file_content[i]; i++)
	{
		if (strlen(&file_content[i]) >= strlen(line) && strncmp(&file_content[i], line, strlen(line)) == 0)
		{
			fprintf(f, "%s %s", key, new_value);
			i += strlen(key) + strlen(old_value);
		}
		else
			fprintf(f, "%c", file_content[i]);
	}
	free(file_content);
	fclose(f);
}

void initing_interfaces_file(void)
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
		free(if_nidxs);
	}
	fclose(f);
}

char	*find_cur_interface(void)
{
	FILE *f;
	char *line_without_newline;

	f = fopen(LOG_FILE_CUR_INTERFACES, "r+");
	if (f == 0)
	{
		f = fopen(LOG_FILE_CUR_INTERFACES, "w+");
		fprintf(f, "eth0\n");
		fclose(f);
	}
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
