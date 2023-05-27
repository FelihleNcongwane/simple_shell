#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return NULL;

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return NULL;
		}
	}

	new_node->next = *head;
	*head = new_node;

	return new_node;
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *current_node;

	if (!head)
		return NULL;

	current_node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return NULL;
		}
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
		*head = new_node;

	return new_node;
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *head)
{
	size_t size = 0;

	for (; head; head = head->next)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		size++;
	}

	return size;
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current_node, *previous_node;
	unsigned int count = 0;

	if (!head || !*head)
		return 0;

	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->str);
		free(current_node);
		return 1;
	}

	previous_node = NULL;
	current_node = *head;

	for (; current_node; previous_node = current_node, current_node = current_node->next, count++)
	{
		if (count == index)
		{
			previous_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return 1;
		}
	}

	return 0;
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *current_node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	current_node = head;

	do {
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	} while (current_node);

	*head_ptr = NULL;
}
