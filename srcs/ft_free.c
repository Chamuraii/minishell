#include "../includes/minishell.h"

extern t_all g_all;

void	ft_free()
{
	t_varlist	*head;
	t_varlist	*aux;

	head = *g_all.varlist;
	while (head)
	{
		free(head->key);
		free(head->value);
		aux = head;
		head = head->next;
		free(aux);
	}
	free(g_all.varlist);
}

void	ft_error_messages()
{
	printf("Error message\n");
	exit(0);
}