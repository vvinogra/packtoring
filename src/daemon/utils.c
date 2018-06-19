#include "header.h"

char *get_line_by_key(const char *key, char *filename)
{
	char *content;
	char *needed_line;
	char *ret;
	FILE *f = fopen(filename, "r+");

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

char	*get_file_content(const char *const filename)
{
	int			fd;
	size_t		len;
	char		*file_content;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		write(1, "Wrong filename\n", 15);
		exit(EXIT_FAILURE);
	}
	len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (!(file_content = (char *)malloc(sizeof(char) * (len + 1))))
		exit(EXIT_FAILURE);
	read(fd, file_content, len);
	file_content[len] = 0;
	close(fd);
	return (file_content);
}
