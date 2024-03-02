#include "shell.h"

/**
 * Fills a block of memory with a constant byte.
 * 
 * @param s: Pointer to the memory area.
 * @param b: The byte to fill *s with.
 * @param n: The amount of bytes to be filled.
 * @return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * Frees a dynamically allocated array of strings.
 * 
 * @param pp: The array of strings to be freed.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * Reallocates a block of memory, adjusting its size.
 * 
 * @param ptr: Pointer to the previous block of memory.
 * @param old_size: Byte size of the previous block.
 * @param new_size: Byte size of the new block.
 * @return: Pointer to the resized block of memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
