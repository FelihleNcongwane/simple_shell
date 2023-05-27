#include "shell.h"

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	switch (buf[j])
	{
	case '|':
		if (buf[j + 1] == '|')
		{
			buf[j] = 0;
			j++;
			info->cmd_buf_type = CMD_OR;
		}
		break;
	case '&':
		if (buf[j + 1] == '&')
		{
			buf[j] = 0;
			j++;
			info->cmd_buf_type = CMD_AND;
		}
		break;
	case ';':
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
		break;
	default:
		return 0;
	}

	*p = j;
	return 1;
}

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	switch (info->cmd_buf_type)
	{
	case CMD_AND:
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
		break;
	case CMD_OR:
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
		break;
	}

	*p = j;
}

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return 0;
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return 0;
		p = _strdup(p + 1);
		if (!p)
			return 0;
		info->argv[0] = p;
	}
	return 1;
}

int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	while (info->argv[i])
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			i++;
			continue;
		}

		switch (info->argv[i][1])
		{
		case '?':
			replace_string(&(info->argv[i]),
			               _strdup(convert_number(info->status, 10, 0)));
			break;
		case '$':
			replace_string(&(info->argv[i]),
			               _strdup(convert_number(getpid(), 10, 0)));
			break;
		default:
			node = node_starts_with(info->env, &info->argv[i][1], '=');
			if (node)
			{
				replace_string(&(info->argv[i]),
				               _strdup(_strchr(node->str, '=') + 1));
			}
			else
			{
				replace_string(&info->argv[i], _strdup(""));
			}
		}

		i++;
	}

	return 0;
}

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return 1;
}
