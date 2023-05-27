#include "shell.h"

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return 0;

	switch (st.st_mode & S_IFMT)
	{
		case S_IFREG:
			return 1;
		default:
			return 0;
	}
}

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, k = 0;

	for (i = start; i < stop; i++)
	{
		switch (pathstr[i])
		{
			case ':':
				break;
			default:
				buf[k++] = pathstr[i];
				break;
		}
	}
	buf[k] = 0;
	return buf;
}

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i, curr_pos = 0;
	char *path;

	if (!pathstr)
		return NULL;
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return cmd;
	}

	i = 0;
	do
	{
		switch (pathstr[i])
		{
			case '\0':
			case ':':
				path = dup_chars(pathstr, curr_pos, i);
				if (!*path)
					_strcat(path, cmd);
				else
				{
					_strcat(path, "/");
					_strcat(path, cmd);
				}
				if (is_cmd(info, path))
					return path;
				if (pathstr[i] == '\0')
					break;
				curr_pos = i;
				break;
		}
		i++;
	} while (1);

	return NULL;
}
