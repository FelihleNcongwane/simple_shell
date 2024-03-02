#include "shell.h"

/**
 * Frees a pointer and sets its address to NULL.
 * 
 * @param ptr: Address of the pointer to free.
 * @return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
