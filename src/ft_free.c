/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 13:26:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

void	ft_free_exit(void)
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
	clear_history();
}

void	ft_free(char *type)
{
	int			i;

	if (!ft_strcmp(type, "exit"))
		ft_free_exit();
	free(g_all.str);
	i = 0;
	while (g_all.array[i])
		free(g_all.array[i++]);
	free(g_all.array);
}

void	ft_free_2(void *var1, void *var2)
{
	free(var1);
	free(var2);
}

void	ft_put_error_message(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
