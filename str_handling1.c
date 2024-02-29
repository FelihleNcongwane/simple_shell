#include "shell.h"

/**
 * _strcat - Concatenate two strings.
 *
 * @dest: Destination string.
 * @src:  Source string.
 *
 * Return:
 *   A pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copy a string.
 *
 * @dest: Destination string.
 * @src:  Source string.
 *
 * Return:
 *   A pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}
/**
 * _strcmp - Compare two strings.
 *
 * @s1: First string.
 * @s2: Second string.
 *
 * Return:
 *   0 if the strings are equal, a positive number if the first string is greater than the second, and a negative number if the first string is less than the second.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - Find the first occurrence of a character in a string.
 *
 * @s: String to search.
 * @c: Character to find.
 *
 * Return:
 *   A pointer to the first occurrence of the character in the string, or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - Get the length of the initial segment of a string consisting of characters from a given set.
 *
 * @s:      String to search.
 * @accept: String containing the characters to match.
 *
 * Return:
 *   The length of the initial segment of the string consisting of characters from the given set.
 */
int _strspn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
