/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:24:19 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/01 19:25:53 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;

/* PIPE_CHILD : child process where is called execve and some builtins */

void	pipe_child(int last)
{
	int	i;

	i = 0;
	close(g_all.p[0]);
	if (g_all.infile > 0)
		dup2(g_all.infile, 0);
	if (last == 0)
		dup2(g_all.p[1], 1);
	if (g_all.outfile > 0)
		dup2(g_all.outfile, 1);
	i = ft_builtins(g_all.commands, g_all.array_pos);
	if (i == 0)
		execve(g_all.path, (char *const *) g_all.commands, g_all.env);
	dup2(0, 1);
	if (errno == 13)
		ft_exit(126);
	else if (i == 1)
		exit (0);
	else
		exit(127);
}

/* PIPES : contains the parent process, retrieves the child's exit code used
in $? */

void	pipes(int last)
{
	int		j;
	int		exit_status;
	char	*exit_code;

	pipe(g_all.p);
	ft_add_var(ft_strdup("?"), ft_strdup("0"));
	j = fork();
	if (j == -1)
		ft_return(errno, NULL);
	else if (j == 0)
		pipe_child(last);
	else
	{
		close(g_all.p[1]);
		dup2(g_all.p[0], 0);
		waitpid(j, &exit_status, 0);
		exit_code = ft_itoa(WEXITSTATUS(exit_status));
		ft_add_var(ft_strdup("?"), ft_strdup(exit_code));
		free(exit_code);
	}
	free_fd();
	if (last == 1)
		dup2(1, 0);
}

/* BUILTIN_NOW : executes the builtins exchanging with env */

void	builtin_now(int j)
{
	if (((ft_strcmp(g_all.commands[0], "exit") == 0)
			|| ((ft_strcmp(g_all.commands[0], "export")) == 0
				&& g_all.outfile == 0
				&& g_all.commands[1]
				&& ft_strcmp(g_all.array[j], "|") != 0))
		|| (ft_strcmp(g_all.commands[0], "cd") == 0)
		|| ((ft_strcmp(g_all.commands[0], "unset") == 0)
			&& g_all.commands[1]))
	{
		ft_builtins(g_all.commands, g_all.array_pos);
		ft_add_var(ft_strdup("?"), ft_itoa(g_all.error));
	}
}

/* IS_EXECVE : determines if commands needs to be executed in child process or
could be executed right away (builtin_now) */

void	is_execve(int j)
{
	where();
	builtin_now(j);
	if (((g_all.is_outfile == 0 && g_all.outfile == 0)
			|| (g_all.is_outfile == 1 && g_all.outfile > 0))
		&& ((g_all.is_infile == 0 && g_all.infile == 0)
			|| (g_all.is_infile == 1 && g_all.infile > 0)))
	{
		if (is_pipe() == 1)
			pipes(0);
		else if ((ft_strcmp(g_all.commands[0], "cd") != 0
				&& ft_strcmp(g_all.commands[0], "exit") != 0))
		{
			if (!((ft_strcmp(g_all.commands[0], "export")) == 0
					&& g_all.commands[1]))
				pipes(1);
		}
	}
}
