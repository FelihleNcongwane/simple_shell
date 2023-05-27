#include "shell.h"

/**
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i;
	int sign = 1;
        int flag = 0;
       	int output;
	unsigned int results = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -results;
	else
		output = results;

	return (output);
}
