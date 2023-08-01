/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:15:35 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/01 19:21:19 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;

/* WRITE_HEREDOC : writes in the right fd when inside a heredoc */

void	write_heredoc(char *his)
{
	if (g_all.outfile)
		write(g_all.outfile, his, ft_strlen(his));
	else
		write(g_all.p[1], his, ft_strlen(his));
	write(g_all.p[1], "\n", 1);
}

/* HEREDOC : recreates bash's heredoc, reads until eof string */

int	heredoc(int j)
{
	char	*his;

	while (j == 0)
	{
		dup2(1, 0);
		his = readline("> ");
		if (!his)
		{
			dup2(g_all.p[0], 0);
			close(g_all.p[1]);
			return (-1);
		}
		if (ft_strcmp (his, g_all.eof_heredoc) == 0 && his)
		{
			dup2(g_all.p[0], 0);
			j ++;
		}
		else if (his)
			write_heredoc(his);
		free(his);
	}
	return (0);
}

/* PTP_HEREDOC : stores heredocs's eof string */

void	ptp_heredoc(int i)
{
	int	h;

	h = 0;
	g_all.eof_heredoc = g_all.array[i + 1];
	pipe(g_all.p);
	heredoc(0);
	close(g_all.p[1]);
	while (g_all.array[h])
		h ++;
	del_arg(i, h, 0, h - 1);
}
