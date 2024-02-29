#include "shell.h"

/**
 * Determines the length of a linked list.
 * 
 * @param h: Pointer to the first node.
 * @return: Size of the list.
 */
size_t list_len(const list_t *h)
{
    size_t i = 0;

    // Traverse the linked list and count the nodes
    while (h)
    {
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * Converts a linked list to an array of strings containing the list->str values.
 * 
 * @param head: Pointer to the first node.
 * @return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t i = list_len(head), j;
    char **strs;
    char *str;

    // Check for empty list or invalid head
    if (!head || !i)
        return (NULL);

    // Allocate memory for the array of strings
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);

    // Traverse the linked list and copy each str value to the array
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            // Free memory in case of allocation failure
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        str = _strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;  // Set the last element of the array to NULL
    return (strs);
}

/**
 * Prints all elements of a list_t linked list.
 * 
 * @param h: Pointer to the first node.
 * @return: Size of the list.
 */
size_t print_list(const list_t *h)
{
    size_t i = 0;

    // Traverse the linked list and print each node's information
    while (h)
    {
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * Returns the node whose string starts with a given prefix.
 * 
 * @param node: Pointer to the list head.
 * @param prefix: String to match.
 * @param c: The next character after the prefix to match.
 * @return: Matched node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    // Traverse the linked list and find the first node with a matching prefix
    while (node)
    {
        p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * Gets the index of a node in the linked list.
 * 
 * @param head: Pointer to the list head.
 * @param node: Pointer to the node.
 * @return: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t i = 0;

    // Traverse the linked list and find the index of the given node
    while (head)
    {
        if (head == node)
            return (i);
        head = head->next;
        i++;
    }
    return (-1);  // Return -1 if the node is not found
}
