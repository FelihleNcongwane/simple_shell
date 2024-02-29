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
        free(*ptr);  // Free the memory pointed to by ptr
        *ptr = NULL;  // Set the pointer to NULL
        return (1);   // Return 1 indicating successful freeing
    }
    return (0);   // Return 0 if the pointer is already NULL or invalid
}
