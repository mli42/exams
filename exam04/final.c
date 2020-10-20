/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:35:00 by mli               #+#    #+#             */
/*   Updated: 2020/10/20 15:00:59 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

enum e_type
{
	EMPTY, PIPE, SEMI
};

typedef struct	s_cmd
{
	int				argc;
	char			**argv;
	int				fds[2];
	enum e_type		type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

int		ft_strlen(const char *const str)
{
	const char *tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

void	ft_putendl(const char *const str, const int newline)
{
	write(2, str, ft_strlen(str));
	if (newline)
		write(2, "\n", 1);
}

void	fatal_error(void)
{
	ft_putendl("error: fatal", 1);
	exit(1);
}

void	ft_fork(pid_t *pid)
{
	if ((*pid = fork()) == -1)
		fatal_error();
}

int		ft_gettype(const t_cmd *const cmd)
{
	if (cmd == NULL)
		return (-1);
	return (cmd->type);
}

void	ft_clean(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

int		ft_binary(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;
	int		ret = 0;

	if (ft_gettype(cmd) == PIPE && pipe(cmd->fds) == -1)
		fatal_error();
	ft_fork(&pid);

	if (pid == 0)
	{
		if (ft_gettype(cmd) == PIPE && dup2(cmd->fds[1], 1) == -1)
			fatal_error();
		if (ft_gettype(cmd->prev) == PIPE && dup2(cmd->prev->fds[0], 0) == -1)
			fatal_error();
		execve(cmd->argv[0], cmd->argv, env);
		ft_putendl("error: cannot execute ", 0);
		ft_putendl(cmd->argv[0], 1);
		exit(-1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		if (ft_gettype(cmd) == PIPE)
			close(cmd->fds[1]);
		if (ft_gettype(cmd->prev) == PIPE)
			close(cmd->prev->fds[0]);
	}
	return (ret);
}

int		ft_cd(t_cmd *cmd)
{
	if (cmd->argc != 2)
		ft_putendl("error: cd: bad arguments", 1);
	else if (chdir(cmd->argv[1]) == -1)
	{
		ft_putendl("error: cd: cannot change directory to ", 0);
		ft_putendl(cmd->argv[1], 1);
	}
	else
		return (0);
	return (1);
}

int		exec(t_cmd *cmd, char **env)
{
	int ret = 0;

	while (cmd)
	{
		ret = (!strcmp(cmd->argv[0], "cd") ? ft_cd(cmd) : ft_binary(cmd, env));
		cmd = cmd->next;
	}
	return (ret);
}

t_cmd	*newCmd(char **argv, int argc, t_cmd *prev, const int type)
{
	t_cmd	*new;

	if (!(new = malloc(sizeof(t_cmd))))
		fatal_error();
	new->argc = argc;
	new->argv = argv;
	new->type = type;
	new->next = NULL;
	if ((new->prev = prev))
		prev->next = new;
	new->argv[argc] = NULL;
	return (new);
}

int		main(int argc, char **argv, char **env)
{
	int		type;
	t_cmd	*cmd = NULL;
	t_cmd	*tmp = NULL;
	int		begin = 1;
	int		NextOpe = 0;

	while (++NextOpe <= argc)
	{
		type = -1;
		if (!argv[NextOpe])
			type = EMPTY;
		else if (!strcmp(argv[NextOpe], "|"))
			type = PIPE;
		else if (!strcmp(argv[NextOpe], ";"))
			type = SEMI;

		if (type != -1)
		{
			int len = 0;
			if ((len = NextOpe - begin) > 0)
			{
				tmp = newCmd(&argv[begin], len, tmp, type);
				if (cmd == NULL)
					cmd = tmp;
			}
			begin = NextOpe + 1;
		}
	}
	const int ret = exec(cmd, env);
	ft_clean(cmd);
	return (ret);
}
