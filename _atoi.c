#include "shell.h"

/**
 * interactive - Returning true if it is interactive mode
 * @info: The address for struct
 *
 * Return: 1 for the interactive mode, 0 if not
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checking for delimeter character
 * @c: Character to be checked
 * @delim: Delim string
 * Return: 1 for T, 0 for F
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checking alphabetic characteracters
 * @c: Character to be inputed
 * Return: 1 if successful and 0 if not.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - change str to an int
 * @s: string to be changed
 * Return: 0 
 */

int _atoi(char *s)
{
	int x, sin = 1, flag = 0, outp;
	unsigned int results = 0;

	for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
			sin *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (s[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sin == -1)
		outp = -results;
	else
		outp = results;

	return (outp);
}
