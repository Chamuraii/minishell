/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:01:56 by jchamak           #+#    #+#             */
/*   Updated: 2023/07/05 19:52:55 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline(const char *prompt);
int		remain(t_all *all, int argc, char **argv, char **envp);

/* FT_EXIT : used to exit, manages errors */

int	ft_exit(int status)
{
	write(2, strerror(status), strlen(strerror(status)));
	write(2, "\n", 1);
	exit(status);
}

/* WHERE : finds and tests possible paths, keeps the good one in all->path */

int	where(char **envp, t_all *all)
{
	int		i;
	char	*temp;

	i = 0;
	while (ft_strncmp("PATH", *envp, 4))
		envp ++;
	if (all->where)
		free (all->where);
	all->where = ft_split(envp[0] + 5, ':');
	while (all->where[i])
	{
		temp = ft_strjoin(all->where[i], "/");
		free(all->where[i]);
		all->where[i] = ft_strjoin(temp, all->commands[0]);
		if (access(all->where[i], F_OK) == 0)
		{
			all->path = all->where[i];
			return (0);
		}
		i ++;
	}
	return (127);
}

/* ARG_FILL : at each iteration, finds the next command to execute */

void	arg_fill(char *const *argv, char	**envp, t_all *all)
{
	int	i;

	i = 0;
	if (all->commands)
		free (all->commands);
	if (all->recep[all->i])
	{
		all->commands = ft_split(all->recep[all->i], ' ');
		where(envp, all);
		all->i ++;
	}
}

void	pipes(char *const *argv, char **envp, t_all *all)
{
	int	j;

	arg_fill(argv, envp, all);
	pipe(all->p);
	j = fork();
	if (j == -1)
		ft_exit(errno);
	else if (j == 0)
	{
		close(all->p[0]);
		dup2(all->p[1], 1);
		if (all->path)
			execve(all->path, (char *const *) all->commands, envp);
		ft_exit(127);
	}
	else
	{
		close(all->p[1]);
		dup2(all->p[0], 0);
	//	free(all->path);
		waitpid(j, NULL, 0);
	}
}
void	final_pipe(char *const *argv, char **envp, t_all *all)
{
	int	j;

	arg_fill(argv, envp, all);
	pipe(all->p);
	j = fork();
	if (j == -1)
		ft_exit(errno);
	else if (j == 0)
	{
		close(all->p[0]);
		if (all->path)
			execve(all->path, (char *const *) all->commands, envp);
		ft_exit(127);
	}
	else
	{
		close(all->p[1]);
		free(all->path);
		waitpid(j, NULL, 0);
	}
}

void	prompt(t_all *all, int argc, char **argv, char **envp)
{
	int			i;
	int			j;
	char		*his;

	i = 0;
	dup2(1, 0);
	his = readline("minishell > ");
	if (his == NULL)
		exit(0);
	if (his[0])
		add_history(his);
	all->recep = ft_split(his, '|');
	remain(all, argc, argv, envp);
	free(his);
}

void heretype(t_all *all, char *end)
{
	int		i;
	int		j;
	char	*his;

	i = 0;
	j = 0;
	pipe(all->p);
	while (j == 0)
	{
	//	dup2(all->p[0], 1);
	//	dup2(all->p[1], 0);
		dup2(0, all->p[1]);
		his = readline("heredoc> ");
		if (strcmp (his, end) == 0)
		{
			j ++;
			dup2(all->p[0], 0);
		}
		else
		{
			//dup2(all->p[0], 0);
			//all->herebuf[i] = his; //
		//	printf("%s\n", his);
		}
		i ++;
	}
//	dup2(all->p[0], 0); //
}

int	remain(t_all *all, int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	all->i = 0;
	char *end = "eof";
/* 	if (strcmp(argv[1], "/dev/urandom") == 0)
		ft_exit(0); */
	all->where = NULL;
//	if (all->heredoc > 0)
	//	heretype(all, end);
//	all->infile = open ("file", O_RDONLY, 0666);
//	all->infile = open (argv[1], O_RDONLY, 0666);
//	all->outfile = open (argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
/* 	if (all->outfile <= 0 || all->infile <= 0)
		ft_exit(127); */
//	dup2(all->infile, 0);
//	dup2(all->outfile, 1);
	while (all->recep[i + 1])
	{
		pipes(argv, envp, all);
		i ++;
	}
	final_pipe(argv, envp, all);
	return (0);
}

void ft_leaks()
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;

//	atexit(ft_leaks);
	all.commands = NULL;
	while (1)
		prompt(&all, argc, argv, envp);
	return (0);
}
