#include "shell.h"

/**
 * cmp_env_name - Compare the name of an environment variable with a given string.
 *
 * @nenv: Name of the environment variable.
 * @name: String to compare with.
 *
 * Return:
 *   0 if the names are equal, -1 otherwise.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}
/**
 * _getenv - Get the value of an environment variable.
 *
 * @name:      Name of the environment variable.
 * @_environ:  Array of environment variables.
 *
 * Return:
 *   The value of the environment variable, or NULL if the variable is not set.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Init ptr_env val */
	ptr_env = NULL;
	mov = 0;
	/* */
	/*  */
	for (i = 0; _environ[i]; i++)
	{
		/* comments here */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}
/**
 * _env - Print the environment variables.
 *
 * @datash: Pointer to the data structure.
 *
 * Return:
 *   0 on success, -1 on failure.
 */
int _env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
