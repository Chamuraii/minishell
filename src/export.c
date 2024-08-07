/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 13:26:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

t_varlist	*ft_create_node_exp(char *key, char *value)
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

void	ft_add_var_exp(char *key, char *value)
{
	t_varlist	*head;
	t_varlist	*head2;

	head = g_all.exported_list[0];
	if (!head)
	{
		g_all.exported_list[0] = ft_create_node_exp(key, value);
		ft_free_2(key, value);
		return ;
	}
	while (head)
	{
		if (!strcmp(key, head->key))
		{
			ft_free_2(head->value, key);
			head->value = value;
			return ;
		}
		head2 = head;
		head = head->next;
	}
	head2->next = ft_create_node(key, value);
	ft_free_2(key, value);
}

int	ft_var_declare_exp(char *str)
{
	int		i;
	char	*str2;
	char	*key;
	char	*value;

	str2 = ft_strdup(str);
	i = 0;
	while (str2[i] && str2[i] != '=')
		i++;
	if (str2[i] != '=')
	{
		free(str2);
		return (0);
	}
	if (!ft_isalpha(str[0]))
		return (free(str2), 0);
	str2[i] = 0;
	key = ft_strdup(str2);
	++i;
	value = ft_remove_quotes(str2 + i);
	ft_add_var_exp(key, value);
	free(str2);
	return (1);
}

char	*ft_get_var_exp(char *key)
{
	t_varlist	*head;
	int			key_len;

	key_len = 0;
	while (ft_isalnum(key[key_len]))
		key_len++;
	head = g_all.exported_list[0];
	if (!head)
		return (ft_strdup(""));
	while (head)
	{
		if (!strncmp(key, head->key, key_len))
			if (!head->key[key_len])
				return (ft_strdup(head->value));
		head = head->next;
	}
	return (ft_strdup(""));
}

int	ft_find_var_exp(char *key)
{
	t_varlist	*head;
	int			key_len;

	key_len = 0;
	while (ft_isalnum(key[key_len]))
		key_len++;
	head = g_all.exported_list[0];
	if (!head)
		return (0);
	while (head)
	{
		if (!strncmp(key, head->key, key_len))
			if (!head->key[key_len])
				return (1);
		head = head->next;
	}
	return (0);
}
