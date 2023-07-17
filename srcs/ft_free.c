#include "../includes/minishell.h"

extern t_all	g_all;

void	ft_free(void)
{
	t_varlist	*head;
	t_varlist	*aux;

	head = g_all.var_list[0];
	while (head)
	{
		free(head->key);
		free(head->value);
		aux = head;
		head = head->next;
		free(aux);
	}
	free(g_all.var_list);
	head = g_all.exported_list[0];
	while (head)
	{
		free(head->key);
		free(head->value);
		aux = head;
		head = head->next;
		free(aux);
	}
	free(g_all.exported_list);
}

void	ft_free_2(void *var1, void *var2)
{
	free(var1);
	free(var2);
}

void	ft_error_messages(void)
{
	printf("Error message\n");
	exit(0);
}
