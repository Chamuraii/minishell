/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:41:22 by jchamak           #+#    #+#             */
/*   Updated: 2023/07/31 16:38:27 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;
void	split_pipe(void);
void	redirections(int i, int end);
void	args_fill(int i, int end);

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

int	ft_return(int status, char *str)
{
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
	char *exit_code = ft_itoa(g_all.error);
	ft_add_var(ft_strdup("?"), ft_strdup(exit_code));
	free(exit_code);
	return (status);
}

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
	//free(g_all.where[i]);
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
	return (127);
}

void	del_arg(int i, int j)
{
	while (g_all.array[i])
	{
		if (j != 0)
			free(g_all.array[i]);
		g_all.array[i] = g_all.array[i + 2];
		i ++;
	}
	g_all.size -= 2;
}

void	ptp_infile(int i)
{
	g_all.is_infile = 1;
	g_all.infile = open (g_all.array[i + 1], O_RDONLY, 0644);
	if (g_all.infile <= 0)
	{
		g_all.infile = 0;
		ft_return(errno, NULL);
		del_arg(i, 0);
	}
	else
		del_arg(i, 1);
}

void	ptp_outfile(int i)
{
	g_all.is_outfile = 1;
	g_all.outfile = open (g_all.array[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (g_all.outfile <= 0)
	{
		g_all.outfile = 0;
		ft_return(errno, NULL);
		del_arg(i, 0);
	}
	else
		del_arg(i, 1);
}

void	ptp_append(int i)
{
	g_all.is_outfile = 1;
	g_all.outfile = open (g_all.array[i + 1],
			O_RDWR | O_APPEND | O_CREAT, 0644);
	if (g_all.outfile <= 0)
	{
		ft_return(errno, NULL);
		del_arg(i, 0);
	}
	else
		del_arg(i, 1);
}

int	heredoc(void)
{
	int		j;
	char	*his;

	j = 0;
	pipe(g_all.p);
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
		if (strcmp (his, g_all.eof_heredoc) == 0 && his)
		{
			dup2(g_all.p[0], 0);
			//close(g_all.p[1]);
			j ++;
		}
		else if (his)
		{
			if (g_all.outfile)
			{
				write(g_all.outfile, his, ft_strlen(his));
				write(g_all.outfile, "\n", 1);
			}
			else
			{
				write(g_all.p[1], his, ft_strlen(his));
				write(g_all.p[1], "\n", 1);
			}
		}
		free(his);
	}
	close(g_all.p[1]);
	return (0);
}

void	ptp_heredoc(int i)
{
	g_all.eof_heredoc = g_all.array[i + 1];
	heredoc();
	del_arg(i, 1);
}

void	free_pipe(void)
{
	int	i;

	i = 0;
	g_all.infile = 0;
	g_all.is_infile = 0;
	g_all.outfile = 0;
	g_all.is_outfile = 0;
/* 	if (g_all.commands)
	{
		while(g_all.commands[i])
		{
			free(g_all.commands[i]);
			i ++;
		}
		free(g_all.commands);
	} */
/* 	if (g_all.path)
		free(g_all.path); */
//	g_all.commands = NULL;
}

void	pipes(int last)
{
	int	i;
	int	j;
	int	exit_status;

	pipe(g_all.p);
	ft_add_var(ft_strdup("?"), ft_strdup("0"));
	j = fork();
	if (j == -1)
		ft_return(errno, NULL);
	else if (j == 0)
	{
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
	else
	{
		close(g_all.p[1]);
		dup2(g_all.p[0], 0);
		waitpid(j, &exit_status, 0);
		int h = 0;
		while (g_all.where[h])
		{
			free(g_all.where[h]);
			h ++;
		}
		free(g_all.where);
		char *exit_code = ft_itoa(WEXITSTATUS(exit_status));
		ft_add_var(ft_strdup("?"), ft_strdup(exit_code));
		free(exit_code);
	}
	free_pipe();
//	close(g_all.p[0]);
	if (last == 1)
		dup2(1, 0);
}

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

void	args_fill(int i, int end)
{
	int	j;

	j = 0;
	g_all.array_pos = i;
	//system("leaks minishell");
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
	g_all.commands[j] = 0; // ?
	//system("leaks minishell");
	where();
	if (((ft_strcmp(g_all.commands[0], "exit") == 0)
			|| ((ft_strcmp(g_all.commands[0], "export") == 0
					&& g_all.outfile == 0
					&& ft_strcmp(g_all.array[j], "|") != 0))
			|| (ft_strcmp(g_all.commands[0], "cd") == 0)
			|| (ft_strcmp(g_all.commands[0], "unset") == 0)))
	{
		ft_builtins(g_all.commands, g_all.array_pos);
		ft_add_var(ft_strdup("?"), ft_strdup("0"));
	}
	//system("leaks minishell");
	if (((g_all.is_outfile == 0 && g_all.outfile == 0)
			|| (g_all.is_outfile == 1 && g_all.outfile > 0))
		&& ((g_all.is_infile == 0 && g_all.infile == 0)
			|| (g_all.is_infile == 1 && g_all.infile > 0)))
	{
		if (is_pipe() == 1)
			pipes(0);
		else if (ft_strcmp(g_all.commands[0], "cd") != 0
			&& ft_strcmp(g_all.commands[0], "exit") != 0)
			pipes(1);
	}
	int h = 0;
	while (g_all.commands[h])
	{
		free(g_all.commands[h]);
		h ++;
	}
	free(g_all.commands);
	free_pipe();
	g_all.size ++;
	if (g_all.array[g_all.size])
		split_pipe();
//	system("leaks minishell");
}

void	redirections(int i, int end)
{
	g_all.size = end;
	//free_pipe();
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
//	system("leaks minishell");
	if (g_all.array[g_all.size + 1])
		args_fill(g_all.start_i, g_all.size);
	else if (g_all.array[0])
		args_fill(g_all.start_i, g_all.size + 1);
//	system("leaks minishell");
}

void	split_pipe(void)
{
	g_all.start_i = g_all.size;
	while (ft_strncmp(g_all.array[g_all.size], "|", 1) != 0
		&& g_all.array[g_all.size + 1])
	g_all.size ++;
	g_all.size ++;
	redirections(g_all.start_i, g_all.size - 1);
}

int execute(void)
{
	//system("leaks minishell");
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
	//system("leaks minishell");
	//free(g_all.commands);
	return (1);
}
