#include "shell.h"

/**
 * interactive - Returns true if the shell is in interactive mode.
 * @info: Struct address.
 *
 * Return: 1 if interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *delim)
{
	for (; *delim; delim++)
	{
		if (*delim == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - Checks for an alphabetic character.
 * @c: The character to check.
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	switch (c)
	{
		case 'a':
		case 'A':
		case 'b':
		case 'B':
		case 'c':
		case 'C':
		case 'd':
		case 'D':
		case 'e':
		case 'E':
		case 'f':
		case 'F':
		case 'g':
		case 'G':
		case 'h':
		case 'H':
		case 'i':
		case 'I':
		case 'j':
		case 'J':
		case 'k':
		case 'K':
		case 'l':
		case 'L':
		case 'm':
		case 'M':
		case 'n':
		case 'N':
		case 'o':
		case 'O':
		case 'p':
		case 'P':
		case 'q':
		case 'Q':
		case 'r':
		case 'R':
		case 's':
		case 'S':
		case 't':
		case 'T':
		case 'u':
		case 'U':
		case 'v':
		case 'V':
		case 'w':
		case 'W':
		case 'x':
		case 'X':
		case 'y':
		case 'Y':
		case 'z':
		case 'Z':
			return (1);
		default:
			return (0);
	}
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in the string, converted number otherwise.
 */
int _atoi(char *s)
{
	int sign = 1, output;
	unsigned int result = 0;

	for (int i = 0, flag = 0; s[i] != '\0' && flag != 2; i++)
	{
		switch (s[i])
		{
			case '-':
				sign *= -1;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				flag = 1;
				result *= 10;
				result += (s[i] - '0');
				break;
			default:
				if (flag == 1)
					flag = 2;
		}
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
