/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:41:22 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/01 17:05:57 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;
void	split_pipe(void);
void	redirections(int i, int end);
void	args_fill(int i, int end, int j);

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

/* FT_STRJ : ft_strjoin with no free */

char	*ft_strj(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	s1 = ft_strdup("");
	if (!s2)
	s2 = ft_strdup("");
	str = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

/* PATH : tests if the argument recieved is already a valid path and calls
ft_return to print if error 127 */

int	path(void)
{
	if (access(g_all.commands[0], F_OK) == 0)
	{
		g_all.path = g_all.commands[0];
		return (0);
	}
	if (g_all.commands[0])
	{
		if (!is_builtins(g_all.commands))
			ft_return(127, g_all.commands[0]);
	}
	return (1);
}

/* WHERE : creates potential paths using env's PATH variable untils it finds 
an accessible one */

int	where(void)
{
	int		i;
	char	*temp;
	char	*split;

	i = 0;
	g_all.path = NULL;
	split = ft_get_var_exp("PATH");
	g_all.where = ft_split(split, ':');
	free(split);
	while (g_all.where[i])
	{
		temp = ft_strj(g_all.where[i], "/");
		free(g_all.where[i]);
		g_all.where[i] = ft_strj(temp, g_all.commands[0]);
		free(temp);
		if (access(g_all.where[i], F_OK) == 0 && g_all.commands[0])
		{
			g_all.path = g_all.where[i];
			return (0);
		}
		i ++;
	}
	path();
	return (127);
}

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

/* FREE_FD : deletes fd names for next pipe */

void	free_fd(void)
{
	g_all.infile = 0;
	g_all.is_infile = 0;
	g_all.outfile = 0;
	g_all.is_outfile = 0;
}

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

/* IS_EXECVE : determines if commands needs to be executed in child process or
could be executed right away (some builtins) */

void	is_execve(int j)
{
	int i = 0;
	where();
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
		ft_add_var(ft_strdup("?"), ft_strdup("0"));
	}
	if (((g_all.is_outfile == 0 && g_all.outfile == 0)
			|| (g_all.is_outfile == 1 && g_all.outfile > 0))
		&& ((g_all.is_infile == 0 && g_all.infile == 0)
			|| (g_all.is_infile == 1 && g_all.infile > 0)))
	{
		if (is_pipe() == 1)
			pipes(0);
		else if ((ft_strcmp(g_all.commands[0], "cd") != 0
			&& ft_strcmp(g_all.commands[0], "exit") != 0)) {
			if (((ft_strcmp(g_all.commands[0], "export")) == 0 && g_all.commands[1]))
				i ++;
//			else if ((ft_strcmp(g_all.commands[0], "export")) == 0 && !g_all.commands[1])
//				pipes(1);
			else
				pipes(1);
		}
	}
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
			ft_remove_quotes(g_all.commands[j]);
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
