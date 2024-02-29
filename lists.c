#include "shell.h"

/**
 * Adds a new node to the start of the linked list.
 * 
 * @param head: The address of the pointer to the head node.
 * @param str: The string field of the new node.
 * @param num: The node index used by history.
 * @return: A pointer to the new head of the linked list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
    list_t *new_head;

    if (!head)
        return (NULL);

    // Allocate memory for the new node
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);

    // Initialize the new node
    _memset((void *)new_head, 0, sizeof(list_t));
    new_head->num = num;

    // Duplicate the string and assign it to the new node's str field
    if (str)
    {
        new_head->str = _strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }

    // Update pointers to include the new node at the start
    new_head->next = *head;
    *head = new_head;

    return (new_head);
}

/**
 * Adds a new node to the end of the linked list.
 * 
 * @param head: The address of the pointer to the head node.
 * @param str: The string field of the new node.
 * @param num: The node index used by history.
 * @return: A pointer to the new node added at the end.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node, *node;

    if (!head)
        return (NULL);

    // Allocate memory for the new node
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    // Initialize the new node
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;

    // Duplicate the string and assign it to the new node's str field
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }

    // If the linked list is not empty, traverse to the end and add the new node
    if (*head)
    {
        node = *head;
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;

    return (new_node);
}

/**
 * Prints only the str element of each node in the linked list.
 * 
 * @param h: The pointer to the first node.
 * @return: The size of the linked list.
 */
size_t print_list_str(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * Deletes the node at the given index in the linked list.
 * 
 * @param head: The address of the pointer to the first node.
 * @param index: The index of the node to delete.
 * @return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    // If the index is 0, update the head pointer
    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return (1);
    }

    // Traverse the linked list to find the node at the given index
    node = *head;
    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        i++;
        prev_node = node;
        node = node->next;
    }

    return (0);
}

/**
 * Frees all nodes of the linked list.
 * 
 * @param head_ptr: The address of the pointer to the head node.
 */
void free_list(list_t **head_ptr)
{
    list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;

    // Traverse the linked list and free each node
    head = *head_ptr;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }

    *head_ptr = NULL;
}
