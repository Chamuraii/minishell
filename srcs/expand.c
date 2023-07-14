#include "../includes/minishell.h"

extern t_all g_all;

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

char	*ft_get_var(char *key)
{
	t_varlist	*head;
	int 		key_len;

	key_len = 0;
	while (ft_isalnum(key[key_len]))
		key_len++;
	head = g_all.varlist[0];
	if (!head)
		return (strdup(""));
	while (head)
	{
		if (!strncmp(key, head->key, key_len))
			if (!head->key[key_len])
				return (ft_strdup(head->value));
		head = head->next;
	}
	return (strdup(""));
}