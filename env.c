#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return 0;
}

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Environment variable name.
 * Return: The value of the variable.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return p;
		node = node->next;
	}
	return NULL;
}

/**
 * _mysetenv - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
	switch (info->argc)
	{
		case 3:
			if (_setenv(info, info->argv[1], info->argv[2]))
				return 0;
			break;
		default:
			_eputs("Incorrect number of arguments\n");
			return 1;
	}
	return 1;
}

/**
 * _myunsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int i = 1;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return 1;
	}

	for (; info->argv[i]; i++)
		_unsetenv(info, info->argv[i]);

	return 0;
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i = 0;

	while (environ[i])
	{
		add_node_end(&node, environ[i], 0);
		i++;
	}
	info->env = node;
	return 0;
}
