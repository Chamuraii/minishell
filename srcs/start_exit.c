/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:19:19 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/01 19:20:47 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;

/* FT_EXIT : closes the child process if not closed by execve */

int	ft_exit(int status)
{
	if (status == 126 && (ft_strcmp(g_all.commands[0], "") == 0
			|| ft_strcmp(g_all.commands[0], "..") == 0))
	{
		write(2, "command not found", 17);
		status = 127;
	}
	else if (status == 126 && ft_strcmp(g_all.commands[0], ".") != 0)
		write(2, "is a directory", 15);
	else if (status == 126)
	{
		write(2, "filename argument required", 26);
		status = 2;
	}
	else
		write(2, "error 127", 9);
	write(2, "\n", 1);
	g_all.error = status;
	exit (status);
}

/* FT_RETURN : prints ("execution") errors when needed */

int	ft_return(int status, char *str)
{
	char	*exit_code;

	if (status == 2)
	{
		write(2, "No such file or directory", 25);
		status = 1;
	}
	else if (status != 127)
		write(2, strerror(status), strlen(strerror(status)));
	else
	{
		if (ft_strrchr(str, '/'))
			write(2, "No such file or directory", 25);
		else
			write(2, "command not found", 17);
	}
	write(2, "\n", 1);
	g_all.error = status;
	exit_code = ft_itoa(g_all.error);
	ft_add_var(ft_strdup("?"), ft_strdup(exit_code));
	free(exit_code);
	return (status);
}

/* FREE_FD : deletes fd names for next pipe */

void	free_fd(void)
{
	g_all.infile = 0;
	g_all.is_infile = 0;
	g_all.outfile = 0;
	g_all.is_outfile = 0;
}

/* EXECUTE : initializes and checks if there is a command to execute */

int	execute(void)
{
	if (!g_all.array[0])
		return (0);
	g_all.i = 0;
	g_all.j = 0;
	g_all.error = 0;
	g_all.start_i = 0;
	g_all.end_i = 0;
	g_all.size = 0;
	dup2(0, 1);
	split_pipe();
	return (1);
}
