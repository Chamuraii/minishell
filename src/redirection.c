/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:17:36 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/01 19:20:57 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

/* PTP_INFILE : stores infile name and opens the fd in question, returns if
infile nonexistent */

void	ptp_infile(int i)
{
	int	h;

	h = 0;
	g_all.is_infile = 1;
	g_all.infile = open (g_all.array[i + 1], O_RDONLY, 0644);
	if (g_all.infile <= 0)
	{
		g_all.infile = 0;
		ft_return(errno, NULL);
	}
	while (g_all.array[h])
		h ++;
	del_arg(i, h, 0, h - 1);
}

/* PTP_OUTFILE : stores outfile name and opens the fd in question, creates it
necessary */

void	ptp_outfile(int i)
{
	int	h;

	h = 0;
	g_all.is_outfile = 1;
	g_all.outfile = open (g_all.array[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (g_all.outfile <= 0)
	{
		g_all.outfile = 0;
		ft_return(errno, NULL);
	}
	while (g_all.array[h])
		h ++;
	del_arg(i, h, 0, h - 1);
}

/* PTP_APPEND : stores outfile name and opens in append mode the fd in question,
creates it if necessary */

void	ptp_append(int i)
{
	int	h;

	h = 0;
	g_all.is_outfile = 1;
	g_all.outfile = open (g_all.array[i + 1],
			O_RDWR | O_APPEND | O_CREAT, 0644);
	if (g_all.outfile <= 0)
		ft_return(errno, NULL);
	while (g_all.array[h])
		h ++;
	del_arg(i, h, 0, h - 1);
}

/* REDIRECTIONS : checks if redirections in ongoing pipe */

void	redirections(int i, int end)
{
	g_all.size = end;
	while (i < g_all.size)
	{
		if (ft_strncmp(g_all.array[i], "<<", 2) == 0)
			ptp_heredoc(i);
		else if (ft_strncmp(g_all.array[i], ">>", 2) == 0)
			ptp_append(i);
		else if (ft_strncmp(g_all.array[i], "<", 1) == 0)
			ptp_infile(i);
		else if (ft_strncmp(g_all.array[i], ">", 1) == 0)
			ptp_outfile(i);
		else
			i ++;
	}
	if (g_all.array[g_all.size + 1])
		args_fill(g_all.start_i, g_all.size, 0);
	else if (g_all.array[0])
		args_fill(g_all.start_i, g_all.size + 1, 0);
}
