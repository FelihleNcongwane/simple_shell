#include "shell.h"

/**
 * get_list_length - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t get_list_length(const list_t *head)
{
    size_t length = 0;

    for (; head; head = head->next)
    {
        length++;
    }
    return length;
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t length = get_list_length(head);
    char **strings;
    char *str;
    size_t i, j;

    if (!head || !length)
        return NULL;

    strings = malloc(sizeof(char *) * (length + 1));
    if (!strings)
        return NULL;

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        str = _strcpy(str, node->str);
        strings[i] = str;
    }
    strings[i] = NULL;
    return strings;
}


/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
    size_t length = 0;

    for (; head; head = head->next)
    {
        _puts(convert_number(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        length++;
    }
    return length;
}

/**
 * find_node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char c)
{
    char *p = NULL;

    for (; head; head = head->next)
    {
        p = starts_with(head->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return head;
    }
    return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t index = 0;

    for (; head; head = head->next, index++)
    {
        if (head == node)
            return index;
    }
    return -1;
}
