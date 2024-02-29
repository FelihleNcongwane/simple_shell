#include "shell.h"

/**
 * get_len - Get the length of a string.
 *
 * @n: String to get the length of.
 *
 * Return:
 *   The length of the string.
 */
int get_len(int n)
{
	unsigned int n1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}
/**
 * aux_itoa - Convert an integer to a string.
 *
 * @n: Integer to convert.
 *
 * Return:
 *   The integer converted to a string.
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int lenght = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	}
	while (n1 > 0)
		;
	return (buffer);
}
/**
 * _atoi - Convert a string to an integer.
 *
 * @s: String to convert.
 *
 * Return:
 *   The integer value of the string.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
