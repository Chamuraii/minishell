/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:38:22 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/01 19:38:26 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;

/* DEL_ARG : removes redirection signs and names from g_all.array */

void	del_arg(int i, int h, int g, int k)
{
	char	**temp;

	temp = ft_calloc(k, sizeof(char *));
	while (g < i)
	{
		temp[g] = ft_strdup(g_all.array[g]);
		g ++;
	}
	h = g;
	g = h + 2;
	while (g_all.array[g])
		temp[h ++] = ft_strdup(g_all.array[g ++]);
	g = 0;
	while (g_all.array[g])
		free(g_all.array[g ++]);
	free(g_all.array);
	g_all.array = ft_calloc(k, sizeof(char *));
	g = 0;
	while (temp[g])
	{
		g_all.array[g] = ft_strdup(temp[g]);
		free(temp[g ++]);
	}
	free(temp);
	g_all.size -= 2;
}

/* IS_PIPE : returns one if the actual pipe isn't the last one, used to know
which dup2 use in the fork (pipe side or stdout/outfile) */

int	is_pipe(void)
{
	int	i;

	i = g_all.size;
	while (g_all.array[i])
	{
		if (ft_strncmp(g_all.array[i], "|", 1) != 0)
			i ++;
		else
			return (1);
	}
	i = 0;
	return (0);
}

/* ARGS_FILL : fills commands array with only the ongoing pipe, frees
afterwards */

void	args_fill(int i, int end, int j)
{
	g_all.array_pos = i;
	g_all.commands = ft_calloc(end - i + 1, sizeof(char *));
	while (i < end)
	{
		g_all.commands[j] = ft_strdup(g_all.array[i]);
		if (ft_is_p_or_r_between_quotes(g_all.commands[j])
			|| ft_quotes_jess(g_all.commands[j]))
			g_all.commands[j] = ft_remove_quotes_2(&g_all.commands[j]);
		i ++;
		j ++;
	}
	g_all.commands[j] = 0;
	is_execve(j);
	j = 0;
	while (g_all.where[j])
		free(g_all.where[j ++]);
	free(g_all.where);
	j = 0;
	while (g_all.commands[j])
		free(g_all.commands[j ++]);
	free(g_all.commands);
	free_fd();
	g_all.size ++;
	if (g_all.array[g_all.size])
		split_pipe();
}

/* SPLIT_PIPE : finds the end position of each pipe */

void	split_pipe(void)
{
	g_all.start_i = g_all.size;
	while (ft_strncmp(g_all.array[g_all.size], "|", 1) != 0
		&& g_all.array[g_all.size + 1])
	g_all.size ++;
	g_all.size ++;
	redirections(g_all.start_i, g_all.size - 1);
}
