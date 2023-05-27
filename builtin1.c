#include "shell.h"

/**
 * _myhistory - History display
 * @info: Contains potential arg
 *  Return: 0 All the time
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Alias set
 * @info: Structure param
 * @str: Alias str
 *
 * Return: 0 if successful and 1 if not
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int r;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (r);
}

/**
 * set_alias - Setting Alias
 * @info: Structure Parameter
 * @str: Alias str
 *
 * Return: 0 if successful and 1 if not
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Alias String Printed
 * @node: Node for alias
 *
 * Return: 0 if successful and 1 if not
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimicing alias
 * @info: Struct for pot args
 *  Return: 0 All the time
 */
int _myalias(info_t *info)
{
	int m = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (m = 1; info->argv[m]; m++)
	{
		p = _strchr(info->argv[m], '=');
		if (p)
			set_alias(info, info->argv[m]);
		else
			print_alias(node_starts_with(info->alias, info->argv[m], '='));
	}

	return (0);
}
