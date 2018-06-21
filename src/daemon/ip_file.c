#include "header.h"

size_t t_ipfile_getlen(t_ipfile **start)
{
	t_ipfile *lst = *start;
	size_t count = 0;

	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return(count);
}

void clear_ip_parse_file(t_ipfile **ip_info)
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

static void t_ipfile_push_back(t_ipfile **start, struct in_addr ip_to_add)
{
	t_ipfile *lst = *start;
	t_ipfile *new;

	new = malloc(sizeof(t_ipfile));
	inet_pton(AF_INET, inet_ntoa(ip_to_add), &(new->ip));
	new->pack_num = 1;
	new->next = 0;
	if (*start == 0)
		*start = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

void add_ip_to_file(t_ipfile **data, struct in_addr ip_to_add)
{
	t_ipfile *ptr = *data;
	bool	ip_found = false;

	if (*data == 0)
	{
		t_ipfile_push_back(data, ip_to_add);
		return ;
	}
	else
	{
		while (ptr)
		{
			if (ptr->ip == ip_to_add.s_addr)
			{
				ptr->pack_num++;
				ip_found = true;
			}
			ptr = ptr->next;
		}
	}
	if (ip_found == false)
		t_ipfile_push_back(data, ip_to_add);
}

t_ipfile *parse_ip_file(FILE *f)
{
	t_ipfile *head;
	t_ipfile *current;

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
		free(line);
		line = 0;
		len = 0;
		node->next = 0;
		if (head == 0)
			current = head = node;
		else
			current = current->next = node;
	}
	free(line);
	return (head);
}

static void	swap_data_t_ipfile(t_ipfile *a, t_ipfile *b)
{
	uint32_t		ip = a->ip;
	size_t		pack_num = a->pack_num;

	a->ip = b->ip;
	a->pack_num = b->pack_num;

	b->ip = ip;
	b->pack_num = pack_num;
}

void	sort_ip_info(t_ipfile *ip_info)
{
	for(t_ipfile *ptr1 = ip_info; ptr1; ptr1 = ptr1->next)
	{
		for(t_ipfile *ptr2 = ptr1; ptr2; ptr2 = ptr2->next)
		{
			if (ptr1->ip > ptr2->ip)
				swap_data_t_ipfile(ptr1, ptr2);
		}
	}
}
