#include "header.h"

static void	write_pid(void)
{
	FILE *f;
	pid_t pid = getpid();

	f = fopen(PID_FILE, "w+");
	fprintf(f, "%u\n", pid);
	fclose(f);
}

void	check_set_pid_file(void)
{
	FILE *f;

	f = fopen(PID_FILE, "r+");
	if (f == 0)
	{
		write_pid();
		return ;
	}
	char *line = 0;
	size_t len = 0;
	getline(&line, &len, f);
	pid_t file_pid = (pid_t)atoi(line);
	if (file_pid != getpid())
	{
		kill(file_pid, SIGKILL);
		write_pid();
	}
	fclose(f);
	free(line);
}

char	*get_value_of_key_from_file(const char *key, char *filename)
{
	char *needed_line;
	char *ret;

	needed_line = get_line_by_key(key, filename);
	ret = strdup(strstr(needed_line, " ") + 1);
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
	fclose(f);
}
