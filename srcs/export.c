#include "../includes/minishell.h"

extern t_all g_all;

void	ft_var_init()
{
	g_all.str = 0;
	g_all.i = 0;
	g_all.env = 0;
	g_all.array = 0;
	g_all.list_size = 0;
	g_all.commands = 0;
	g_all.path = 0;
	g_all.varlist = (t_varlist **)malloc(sizeof(t_varlist *));
	if (!g_all.varlist)
	{
		printf("ERROR, not enough memory\n");
		exit(0);
	}
	g_all.varlist[0] = 0;
}

t_varlist	*ft_create_node(char *key, char *value)
{
	t_varlist	*varlist;

	varlist = (t_varlist *)malloc(sizeof(t_varlist));
	if (!varlist)
		return (0);
	varlist->next = 0;
	varlist->key = ft_strdup(key);
	varlist->value = ft_strdup(value);
	return (varlist);
}

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

void ft_add_var(char *key, char *value)
{
	t_varlist	*head;
	t_varlist	*head2;

	head = *g_all.varlist;
	if (!head)
	{
		*g_all.varlist = ft_create_node(key, value);
		free(key);
		free(value);
		return ;
	}
	while (head)
	{
		if (!strcmp(key, head->key))
		{
			free(head->value);
			free(key);
			head->value = value;
			return ;
		}
		head2 = head;
		head = head->next;
	}
	head2->next = ft_create_node(key, value);
	free(key);
	free(value);
}

int ft_var_declare(char *str)
{
	int i;
	int ward;
	char	*key;
	char 	*value;
	char 	aux;

	i = 0;
	while (str[i]&& str[i] != '=')
		i++;
	if (str[i] != '=')
		return (0);
	aux = str[i];
	str[i] = 0;
	key = strdup(str);
	str[i] = aux;
	ward = ++i;
	while (str[i])
		i++;
	aux = str[i];
	str[i] = 0;
	value = ft_strdup(str + ward);
	str[i] = aux;
	ft_add_var(key, value);
	return (1);
}
