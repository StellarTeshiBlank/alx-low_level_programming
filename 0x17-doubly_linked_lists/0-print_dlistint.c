#include "lists.h"

/**
 * print_dlistint - prints all the elements of a
 * dlistint_t list
 *
 * @h: head of the list
 * Return: the number of nodes
 */
size_t print_dlistint(const dlistint_t *h)
{
    size_t count = 0;

    if (h == NULL)
        return (count);

    // Move to the start of the list if h is not the head
    while (h->prev != NULL)
        h = h->prev;

    // Print the elements and count the nodes
    while (h != NULL)
    {
        printf("%d\n", h->n);
        count++;
        h = h->next;
    }

    return (count);
}
