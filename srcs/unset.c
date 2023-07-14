#include "../includes/minishell.h"

extern t_all g_all;

void	ft_del_var(char *key)
{
	t_varlist	*head;
	t_varlist	*head2;

	head = *g_all.varlist;
	head2 = *g_all.varlist;
	if (!head)
	{
		free(key);
		return ;
	}
	while (head)
	{
		if (!strcmp(key, head->key))
		{
			free(head->value);
			free(head->key);
			if (head2 == head)
				*g_all.varlist = head->next;
			else
				head2->next = head->next;
			free(head);
			free(key);
			return ;
		}
		head2 = head;
		head = head->next;
	}
	free(key);
}