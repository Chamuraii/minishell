#include "../includes/minishell.h"

extern t_all	g_all;

void	ft_del_var_1(char *key)
{
	t_varlist	*head;
	t_varlist	*head2;

	head = g_all.var_list[0];
	head2 = g_all.var_list[0];
	if (!head)
	{
		free(key);
		return ;
	}
	while (head && strcmp(key, head->key))
	{
		head2 = head;
		head = head->next;
	}
	if (!head)
		return (free(key));
	ft_free_2(head->value, head->key);
	if (head2 == head)
		g_all.var_list[0] = head->next;
	else
		head2->next = head->next;
	ft_free_2(head, key);
}

void	ft_del_var_2(char *key)
{
	t_varlist	*head;
	t_varlist	*head2;

	head = g_all.exported_list[0];
	head2 = g_all.exported_list[0];
	if (!head)
	{
		free(key);
		return ;
	}
	while (head && strcmp(key, head->key))
	{
		head2 = head;
		head = head->next;
	}
	if (!head)
		return (free(key));
	ft_free_2(head->value, head->key);
	if (head2 == head)
		g_all.exported_list[0] = head->next;
	else
		head2->next = head->next;
	ft_free_2(head, key);
}

void	ft_del_var(char *key)
{
	char	*key_2;

	key_2 = ft_strdup(key);
	ft_del_var_1(key);
	ft_del_var_2(key_2);
}
