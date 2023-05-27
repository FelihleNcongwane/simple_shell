#include "shell.h"

/**
 * _myenv - Display current env
 * @info: Contains potential args
 * Return: 0 All the time
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Fetch env val
 * @info: Contains potential args
 * @name: Environment
 *
 * Return: Answer
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - set new env
 * @info:Contains potential args
 *  Return: 0 All the time
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Get rid of env var
 * @info: Contains potential args
 * Return: 0 All the time
 */
int _myunsetenv(info_t *info)
{
	int z;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (z = 1; z <= info->argc; z++)
		_unsetenv(info, info->argv[z]);

	return (0);
}

/**
 * populate_env_list - linked list populated
 * @info: containing potential args
 * Return: 0 All the time.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t z;

	for (z = 0; environ[z]; z++)
		add_node_end(&node, environ[z], 0);
	info->env = node;
	return (0);
}
