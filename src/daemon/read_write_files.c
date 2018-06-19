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

// static t_ipfile *parse_line_ip_file(char *line, struct in_addr ip_to_add)
// {
// 	t_ipfile *line_ip;

// 	line_ip = malloc(sizeof(t_ipfile));
// 	char *first_part = strtok(line, " ");
// 	inet_pton(AF_INET, first_part, &(line_ip->ip));
// 	char *second_part = strtok(NULL, " ");
// 	line_ip->pack_num = atoi(second_part);
// 	if (strcmp(second_part, inet_ntoa(ip_to_add)) == 0)
// 	{
// 		line_ip->pack_num++;
// 		ip_found = true;
// 	}
// 	return (line_ip);
// }

t_ipfile *parse_ip_file(FILE *f, struct in_addr ip_to_add)
{
	t_ipfile *head;
	t_ipfile *current;
	bool	ip_found = false;

	head = current = 0;
	char *line = 0;
	size_t len = 0;
	while (getline(&line, &len, f) > 0)
	{
		t_ipfile *node = malloc(sizeof(t_ipfile));

		char *first_part = strtok(line, " ");
		inet_pton(AF_INET, first_part, &(node->ip));
		char *second_part = strtok(NULL, " ");
		node->pack_num = atoi(second_part);
		if (strcmp(first_part, inet_ntoa(ip_to_add)) == 0)
		{
			node->pack_num++;
			ip_found = true;
		}
		free(line);
		line = 0;
		len = 0;
		node->next = 0;
		if (head == 0)
			current = head = node;
		else
			current = current->next = node;
	}
	if (ip_found == false)
	{
		t_ipfile *node = malloc(sizeof(t_ipfile));
		inet_pton(AF_INET, inet_ntoa(ip_to_add), &(node->ip));
		node->pack_num = 1;
		node->next = 0;
		if (head == 0)
			current = head = node;
		else
			current = current->next = node;
	}
	// for(t_ipfile *ip_info_tmp = head; ip_info_tmp; ip_info_tmp = ip_info_tmp->next)
	// {
	// 	struct in_addr ip_addr;
	// 	ip_addr.s_addr = ip_info_tmp->ip;
	// 	fprintf(f, "%s %zu\n", inet_ntoa(ip_addr), ip_info_tmp->pack_num);
	// }
	// exit(0);
	return (head);
}

// t_ipfile *parse_ip_file(FILE *f, struct in_addr ip_to_add)
// {
// 	t_ipfile *ip = malloc(sizeof(t_ipfile));
// 	t_ipfile *ptr = ip;
// 	bool	ip_found = false;

// 	char *line = 0;
// 	size_t len = 0;
// 	while (getline(&line, &len, f) > 0)
// 	{
// 		char *first_part = strtok(line, " ");
// 		inet_pton(AF_INET, first_part, &(ptr->ip));
// 		char *second_part = strtok(NULL, " ");
// 		ptr->pack_num = atoi(second_part);
// 		if (strcmp(second_part, inet_ntoa(ip_to_add)) == 0)
// 		{
// 			ptr->pack_num++;
// 			ip_found = true;
// 		}
// 		ptr->next = malloc(sizeof(t_ipfile));
// 		ptr = ptr->next;
// 		ptr->next = 0;
// 		free(line);
// 		line = 0;
// 		len = 0;
// 	}
// 	if (ip_found == true)
// 	{
// 		inet_pton(AF_INET, inet_ntoa(ip_to_add), &(ptr->ip));
// 		ptr->pack_num = 1;
// 	}
// 	else
// 	{
// 		ptr->ip = 0;
// 		ptr->pack_num = 0;
// 		free(ptr);
// 		ptr = 0;
// 	}
// 	for(t_ipfile *ip_info_tmp = ip; ip_info_tmp; ip_info_tmp = ip_info_tmp->next)
// 	{
// 		struct in_addr ip_addr;
// 		ip_addr.s_addr = ip_info_tmp->ip;
// 		fprintf(f, "%s %zu\n", inet_ntoa(ip_addr), ip_info_tmp->pack_num);
// 	}
// 	exit(0);
// 	return (ip);
// }
